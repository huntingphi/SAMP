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
    std::vector<T> getData() const;
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
Audio<T>::Audio()
    : data()
{
}

template <typename T>
Audio<T>::Audio(T t)
    : data(t)
{
}

template <typename T>
std::vector<T> Audio<T>::getData() const
{
    return data;
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