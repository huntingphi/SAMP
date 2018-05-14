#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Audio
{
  private:
    std::vector<T> data;

  public:
    Audio(std::vector<int8_t> values, int s_rate);
    Audio(std::vector<int16_t> values, int s_rate);
    Audio(std::vector<std::pair<int8_t, int8_t>> values, int s_rate);
    Audio(std::vector<std::pair<int16_t, int16_t>> values, int s_rate);
    Audio();
    Audio(const Audio&);
    Audio(Audio&&);
    Audio(T t);
    Audio& operator=(const Audio&);
    Audio& operator=(Audio&&);
    bool operator==(const Audio&) const;
    std::vector<T> getData() const;
    Audio operator|(const Audio &);
    Audio operator+(const Audio &);
    Audio &operator^(const std::pair<float, float>);
    Audio &operator*(const std::pair<float, float>);
    std::string toString() const;

    static int MAX_INT8;
    static int MAX_INT16;
    int channels;
    int bits;
    int size;
    int sample_rate;
};
template <typename T>
Audio<T>::Audio(std::vector<int8_t> values, int s_rate) : channels(1), size(values.size()), bits(8), sample_rate(s_rate), data(values) {}
template <typename T>
Audio<T>::Audio(std::vector<int16_t> values, int s_rate) : channels(1), size(values.size()), bits(16), sample_rate(s_rate), data(values){};
template <typename T>
Audio<T>::Audio(std::vector<std::pair<int8_t, int8_t>> values, int s_rate) : channels(2), size(values.size()), bits(8), sample_rate(s_rate), data(values){};
template <typename T>
Audio<T>::Audio(std::vector<std::pair<int16_t, int16_t>> values, int s_rate) : channels(2), size(values.size()), bits(16), sample_rate(s_rate), data(values){};
template <typename T>
Audio<T>::Audio() : channels(0), size(0),bits(0),sample_rate(0), data(std::vector<T>{}){}
template <typename T>
Audio<T>::Audio(const Audio& other) : channels(other.channels),size(other.size),bits(other.bits),sample_rate(other.sample_rate),data(other.data){
}
template <typename T>
Audio<T>::Audio(Audio && other) : channels(0), size(0), bits(0), sample_rate(0), data(std::vector<T>{}) {
    channels = other.channels;
    size = other.size;
    bits = other.bits;
    sample_rate = other.sample_rate;
    data = std::move(other.data);
    other.channels = 0;
    other.bits = 0;
    other.size = 0;
    other.sample_rate = 0;
    other.data = std::vector<T>{};
}
// template <typename T>
// Audio<T>::Audio(T t) : data(t) {}
template <typename T>
Audio<T>& Audio<T>::operator=(const Audio& other) {
    channels = other.channels;
    size = other.size;
    bits = other.bits;
    sample_rate = other.sample_rate;
    data = other.data;
}
template <typename T>
Audio<T>& Audio<T>::operator=(Audio && other){
    channels = 0;
    bits = 0;
    size = 0;
    sample_rate=0;
    data = std::vector<T>{};
    channels = other.channels;
    size = other.size;
    bits = other.bits;
    sample_rate = other.sample_rate;
    data = std::move(other.data);
    other.channels = 0;
    other.bits = 0;
    other.size = 0;
    other.sample_rate = 0;
    other.data = std::vector<T>{};
}
template <typename T>
bool Audio<T>::operator==(const Audio& other) const{
    return 
    channels == other.channels &&
    size == other.size &&
    bits == other.bits &&
    sample_rate == other.sample_rate &&
    data == other.data;
}

template <typename T>
std::vector<T> Audio<T>::getData() const
{
    return data;
}

template <typename T>
Audio<T> Audio<T>::operator|(const Audio &){

}
template <typename T>
Audio<T> Audio<T>::operator+(const Audio &){

}
template <typename T>
Audio<T>& Audio<T>::operator^(const std::pair<float, float>){
    
}
template <typename T>
Audio<T>& Audio<T>::operator*(const std::pair<float, float>){
    
}

template <typename T>
std::string Audio<T>::toString() const
{
        return "N: "+std::to_string(channels)+std::string(" Bit depth: ") + std::to_string(bits)+std::string(" Samples: ")+std::to_string(size)+ std::string(" Sample rate: ")+std::to_string(sample_rate);
}

template <typename T>
int Audio<T>::MAX_INT8 = 127;
template <typename T>
int Audio<T>::MAX_INT16 = 65535;

#endif