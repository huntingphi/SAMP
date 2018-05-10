# SAMP

## Brief

Write app to process audio sound clips.
Should be possible to perform simple editing operations on audio such as cut and paste, and transforming the sound clips. Example transformations include fade in/out and [normalisation](#normalisation).
The soundclips will be 1-channel (mono) or 2-channel (stereo) and will be provided as simple raw byte data which needs to be correctly interpreted.
A raw sound file/clip is a sequence of [samples](#samples) (usually 8-, 16- or 24-bit) of an audio signal that can be sent to an audio speaker to produce sound. The audio also has a [sample rate.](#sample-rate) The higher the sample rate the better the quality of the sound produced. The number of bits per sample also affects audio quality. Higher bitrate results in better audio quality but also larger files. To balance this out compression is used, but is not neccessary in this prac. Simple raw (byte stream) audio will be used throughout.

## Playing sound files

Sound files on Ubuntu can be played with the following command (provided sox package is installed):

```
play -r 44100 -e signed -b 16 -c 2 Run_44100_16bit_stereo.raw
```

```-c``` speciefies the number of channels (ie 1 for mono, 2 for stereo)

```-r``` is the sampling rate in Hz (44.1 kHz in the command above)

```-e``` specifies signed data

```-b``` specifies the bitrate

The last argument is the file name.

From assignment spec
>"A worked example loading and manipulating these [PCM](#pcm) [RAW](#raw) audio files is given as an
ipython notebook. Several audio files will be made available to you (you can use Audacity to
convert your favorite songs into RAW files if necessary)."

# Requirements

## Arguments and program invocation

```
samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>]
soundFile1 [soundFile2]
```

```-c``` speciefies the number of channels (either 1 for mono, 2 for stereo)

```-r``` is the sampling rate in Hz, usually 44100 (44.1 kHz)

```-b``` specifies the bitrate. Program only needs to support 8- and 16-bit

`outFileName` is the name of the newly created sound clip (should default to “out”).

`<ops>` is ONE of the following:

  * `-add`: add soundFile1 and soundFile2
  * `-cut r1 r2`: remove samples over range [r1,r2] (inclusive) (assumes one sound file)
  * `-radd r1 r2 s1 s2` : add soundFile1 and soundFile2 over sub-ranges indicated (in seconds). The ranges must be equal in length.
  * `-cat`: concatenate soundFile1 and soundFile2
  * `-v r1 r2`: volume factor for left/right audio (def=1.0/1.0) (assumes one sound file)
  * `-rms`: Prints out the RMS of the sound file (assumes one sound file only).
  * `-norm r1 r2`: normalize file for left/right audio (assumes one sound file only and that r1 and r2 are floating point RMS values)
  * `-fadein n`: n is the number of seconds (floating point number) to slowly increase the volume (from 0) at the start of soundFile1 (assumes one sound file). **[extra credit]**
  * `-fadeout n`: n is the number of seconds (floating point number) to slowly decrease the volume (from 1.0 to 0) at the end of soundFile1 (assumes one sound file). **[extra credit]**

The sample rate, bit count and no. channels should be used for both the input files and resulting output file.

## Input

The format of the input .raw audio is a stream of samples (a binary file). By using the size of each element (8- or 16-bit and number of channels), and the size of the file using `seekg` and `tellg` you can determine how many samples are in the file.

Only **8-bit** (signed int) and **16-bit** (signed int) sound clips will be used. These can be represented as `int8_t` and `int16_t` (must include `<cstdint>`).
Clips are either 1- or 2-channel. 2-channel (stereo) files have pairs of ints per sample where the first int is for the left ear and second is for the right. This data can be packaged into a `std::pair<intN_t,intN_t>` where N is the number of bits (8 or 16).

Using the resize method of vector a large enough buffer can be allocated. Vector should contain int samples for 1-channel audio, `std::pair<intN_t,intN_t>` for 2-channel. The address of the start of the buffer is given by `&(data_vector[0])`.

The following formula can be used when reading in audio files:
  ```NumberOfSamples = fileSizeInBytes / (sizeof(intN_t) * channels)```
  Where Length of the audio clip in seconds = `NumberOfSamples / (float) samplingRate`

## Output

When modifying sound files the output must be saved as a raw audio file (.raw). The filename should have the following format:
  Filename_samplingrate_samplesize_monoORstereo.raw

> "For example, a mono output file saved with the name “spooky”, with 16-bit samples, a sampling rate of 8000 Hz would have the final name: “spooky_8000_16_mono.raw”"

## Templating

The Audio class should be templated to handle audio signals which use different bit sizes for samples depending on the audio clip provided. To handle stereo, the template must be specialised to manipulate data that consists of a pair of samples per time step (for left and right audio). Therefore instead of an array of ints the class will have an array of pairs. Each sequence of L/R data can be handled differently.

## Functionality required

The following operators will be overloaded to achieve basic editing.

  * `A | B` **Concatenate** audio file A and B (A and B must have the same sampling, sample size and mono/stereo settings)
  * `A * F` **Volume factor** A with F where a is a `std::pair<float,float>` with each float in range [0.0,1.0] The pair allows us to pack a separate volume scale for left and right channels. To apply the operation, each sample is multiplied by the volume factor. For mono, only the the first number will be used. This will allow one channel to be made louder or softer than another.
  * `A + B` **Add amplitudes of audio file A and B** (A and B must have the same sampling, sample size and mono/stereo settings). Each resulting amplitude must be clamped to the maximum value of the sample type, where the maximum value for an N bit integer is **2<sup>N-1</sup>-1 **
  * Adding two very loud files may result in [saturation](#saturation)
  * `A^F` **Cut** from an audio file A, a region from a start to end given by F where F is a  `std::pair<int,int>`
  * **The big 6 must be overloaded**

  *These operators should be demonstrated to work by simple unit tests.*
    >"It may be helpful to create a initializer list constructor to your Audio class to read in a small custom buffer in order to test these operators. Your unit tests should be compiled as separate executables."

## Audio transformations

STL algorithms must be used with custom [Functors](#functors) or [Lambdas](#lamdas). When ranges are required, an iterator should be used. The iterator will be a simple pointer to the internal audio data buffer.
  ### Transformations
  * **Reverse:** reverse all samples. This can be done very quickly with the STL.
  * **Ranged add:** select two same length samples from two signals and add them together. This is different from the `+ operator` which adds entire audio clips together. This should be achieved by using `std::copy` and the previously defined `+operator`
  * **Compute RMS:** use `std::accumulate` in `<numeric>` along with a custom [lambda](#lambda) to compute the RMS (per channel) according to the following formula:
    <!-- % RMS= \sqrt{(\frac{1}{M}   \sum_{i=0}^{M-1} x^{2}_i )} % -->
    <!-- http://www.sciweavers.org/tex2img.php?eq=RMS%3D%20%5Csqrt%7B%28%5Cfrac%7B1%7D%7BM%7D%20%20%20%5Csum_%7Bi%3D0%7D%5E%7BM-1%7D%20x%5E%7B2%7D_i%20%29%7D&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0 -->
      <img src="http://www.sciweavers.org/tex2img.php?eq=RMS%3D%20%5Csqrt%7B%28%5Cfrac%7B1%7D%7BM%7D%20%20%20%5Csum_%7Bi%3D0%7D%5E%7BM-1%7D%20x%5E%7B2%7D_i%20%29%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="RMS= \sqrt{(\frac{1}{M}   \sum_{i=0}^{M-1} x^{2}_i )} " width="165" height="68" />

      This can be seen as the average volume of the sound clip
  * **Sound normalisation** Use  `std::transform` with a custom functor to normalise the sound files to a specified RMS value per channel. This will require the current RMS to be computed before the normalisation. The functor should work with both mono and stereo files.

  Normalisation can be done according to the following formula:
<!-- outputAmp = inputAmp \multiply  \frac{RMS_d_e_s_i_r_e_d}{RMS_c_u_r_r_e_n_t}  -->
  <img src="http://www.sciweavers.org/tex2img.php?eq=outputAmp%20%3D%20inputAmp%20%5Cmultiply%20%20%5Cfrac%7BRMS_d_e_s_i_r_e_d%7D%7BRMS_c_u_r_r_e_n_t%7D%20&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="outputAmp = inputAmp \multiply  \frac{RMS_d_e_s_i_r_e_d}{RMS_c_u_r_r_e_n_t} " width="300" height="46" />

  This effectively increases the overall volume of a sound clip to the desired level and can be used to normalise between audio clips. The output amplitudes must be clamped to the maximum values of the sample type, where the maximum value for an N bit integer is **2<sup>N-1</sup>-1 **.

## Fading in and out

**Fade-in/Fade-out**: use a custom lamda with a simple linear function, [ramp](#ramp), applied to a single audio clip, over a specified range of samples. This can be implemented using `std::for_each`.
  Fade-in:
  ```
  OutputAmp = (FadeSampleNo / (float) rampLength) * inputAmp
  ```

  Fade-out:
  ```
  OutputAmp = (1.0 - FadeSampleNo / (float) rampLength) * inputAmp
  ```

  Where `rampLength` is the number of samples to apply:
  ```
  rampLength =
numSeconds * sampleRate
  ```


## Definitions

### Normalisation<a name="normalisation"></a>:

>"Audio normalization is the application of a constant amount of gain to an audio recording to bring the average or peak amplitude to a target level (the norm)."
>-[Wikipedia](https://en.wikipedia.org/wiki/Audio_normalization)

### Gain<a name="gain"></a>:

>"Both gain and levels refer to the loudness of the audio. However, gain is the input level of the clips and volume is the output.
>In recording audio, gain is the first control that the microphone signal goes through in a mixer while levels are adjusted after that."
>-[AdobePress.com](www.adobepress.com/articles/article.asp?p=2171314&seqNum=2)

### Samples<a name="samples"></a>:

>A sample is a value or set of values at a point in time and/or space
>-[Wikipedia](https://en.wikipedia.org/wiki/Sampling_(signal_processing))

### Sample rate<a name="sample-rate"></a>:

>Sample rate is the number of samples of audio carried per second, measured in Hz or kHz (one kHz being 1 000 Hz).
>For example, 44 100 samples per second can be expressed as either 44 100 Hz, or 44.1 kHz.
> -[Audacity Wiki](https://wiki.audacityteam.org/wiki/Sample_Rates)


### RAW<a name="raw"></a>

>"RAW Audio format or just RAW Audio is an audio file format for storing uncompressed audio in raw form.
>Comparable to WAV or AIFF in size, RAW Audio file does not include any header information (sampling rate, bit depth, endian, or number of channels).
>Data can be written in [PCM](#pcm), IEEE 754 or ASCII."
>-[Wikipedia](https://en.wikipedia.org/wiki/Raw_audio_format)

### PCM<a name="pcm"></a>

>"Pulse-code modulation (PCM) is a method used to digitally represent sampled analog signals.
>It is the standard form of digital audio in computers, compact discs, digital telephony and other digital audio applications."
>-[Wikipedia](https://en.wikipedia.org/wiki/Pulse-code_modulation)

### Saturation<a name="saturation"></a>

>"Saturation is the addition of complex harmonics and distortion to an audio signal, the styles/sounds of different kinds of saturation are numerous and they can all achieve different things."
>-[Quora](https://www.quora.com/What-is-saturation-with-regard-to-audio-engineering-What-applications-is-saturation-commonly-employed-to-achieve)

### Functors <a name="functors"></a>

>"A functor acts just like a function, but it has the advantages that it is stateful, meaning it can keep data reflecting its state between calls."
>Here is a simple functor example :
```cpp
struct Accumulator
{
    int counter = 0;
    int operator()(int i) { return counter += i; }
}
...
Accumulator acc;
cout << acc(10) << endl; //prints "10"
cout << acc(20) << endl; //prints "30"
```
>"Functors are heavily used with generic programming. Many STL algorithms are written in a very general way, so that you can plug-in your own function/functor into the algorithm. For example, the algorithm std::for_each allows you to apply an operation on each element of a range. It could be implemented something like that :"
```cpp
template <typename InputIterator, typename Functor>
void for_each(InputIterator first, InputIterator last, Functor f)
{
    while (first != last)
    f(\*first++)
}
```

>"You see that this algorithm is very generic since it is parametrized by a function.
By using the operator(), this function lets you use either a functor or a function pointer.
Here's an example showing both possibilities :"
```cpp
void print(int i) {
 std::cout << i << std::endl;
}
...    
std::vector<int> vec;
// Fill vec

// Using a functor
Accumulator acc;
std::for_each(vec.begin(), vec.end(), acc);
// acc.counter contains the sum of all elements of the vector

// Using a function pointer
std::for_each(vec.begin(), vec.end(), print); // prints all elements
```

>-[StackOverflow](https://stackoverflow.com/questions/317450/why-override-operator#317528)

### Lamdas <a name="lamdas"></a>

>"In C++11, a lambda expression—often called a lambda—is a convenient way of defining an anonymous function object right at the location where it is invoked or passed as an argument to a function.
>Typically lambdas are used to encapsulate a few lines of code that are passed to algorithms or asynchronous methods."

>-[MSDN - Microsoft](https://msdn.microsoft.com/en-us/library/dd293608.aspx)

> Example:
```cpp
int main()
{
    auto func = [] () { cout << "Hello world"; };
    func(); // now call the function
}
```



>Also see [StackOverflow](https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11)

### Ramp <a name="ramp"></a>
>"The ramp function is a unary real function, easily computable as the mean of the independent variable and its absolute value."
>-[IPFS](https://ipfs.io/ipfs/.../wiki/Ramp_function.html)
