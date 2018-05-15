#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

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
    void reverse();
    float computeRMS();
    std::pair<float,float> computeStereoRMS();
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
void Audio<T>::reverse()
{
    std::reverse(data.begin(),data.end());
}


template <>
std::pair<float, float> Audio<std::pair<int8_t, int8_t>>::computeStereoRMS()
{
    std::vector<int8_t> left_data;
    std::vector<int8_t> right_data;
    for(std::pair<int8_t,int8_t> p : data){
        // std::cout<<p.first<<"\n";
        left_data.push_back(std::get<0>(p));
        right_data.push_back(std::get<1>(p));
        }
    int8_t left_sum = std::accumulate(left_data.begin(), left_data.end(), 0.0f, [](int8_t total, int8_t i) { return total += pow(i, 2); });
    int8_t right_sum = std::accumulate(right_data.begin(), right_data.end(), 0.0f, [](int8_t total, int8_t i) { return total += pow(i, 2); });
    // std::cout << left_sum << std::endl;
    // std::cout << right_sum << std::endl;
    return std::make_pair((float)left_sum / (float)size,(float)right_sum / (float)size);
}

template<>
std::pair<float, float> Audio<std::pair<int16_t,int16_t>>::computeStereoRMS()
{
    // int8_t left_sum = std::accumulate(data.begin(), data.end(), 0.0f, [](int16_t total, int16_t i) { return total += pow(i, 2); });//[](int16_t total, std::pair<int16_t, int16_t> i) { return total += pow(std::get<0>(i), 2); });
    // int8_t right_sum = std::accumulate(data.begin(), data.end(), 0.0f, [](int16_t total, std::pair<int16_t, int16_t> i) { return total += pow(std::get<1>(i), 2); });
    // return std::make_pair((float)left_sum / size, (float)right_sum / size);

    std::vector<int16_t> left_data;
    std::vector<int16_t> right_data;
    for (std::pair<int16_t, int16_t> p : data)
    {
        left_data.push_back(std::get<0>(p));
        right_data.push_back(std::get<1>(p));
    }
    int16_t left_sum = std::accumulate(left_data.begin(), left_data.end(), 0.0f, [](int16_t total, int16_t i) { return total += pow(i, 2); });
    int16_t right_sum = std::accumulate(right_data.begin(), right_data.end(), 0.0f, [](int16_t total, int16_t i) { return total += pow(i, 2); });

    return std::make_pair((float)left_sum / (float)size, (float)right_sum / (float)size);
}

template <>
float Audio<int8_t>::computeRMS()
{
    int8_t sum = std::accumulate(data.begin(), data.end(), 0.0f, [](int8_t total, int8_t i) { return total += pow(i, 2); });
    return (float)sum/size;
}
template <>
float Audio<int16_t>::computeRMS()
{
    int16_t sum = std::accumulate(data.begin(), data.end(), 0.0f, [](int16_t total, int16_t i) { return total += pow(i, 2); });
    return (float)sum / size;
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