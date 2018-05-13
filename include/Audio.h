#ifndef AUDIO_H
#define AUDIO_H
#include <utility>
#include <string>



template <class T> //, class A = std::allocator<T> >
class Audio {
private:
class iterator {
private:

public:
iterator(){}
// iterator(const iterator&);
~iterator(){}
int size(){}
iterator& operator=(const iterator&);
bool operator==(const iterator&) const;
bool operator!=(const iterator&) const;
bool operator<(const iterator&) const;         //optional
bool operator>(const iterator&) const;         //optional
bool operator<=(const iterator&) const;         //optional
bool operator>=(const iterator&) const;         //optional

iterator& operator++();
iterator operator++(int);         //optional
iterator& operator--();         //optional
iterator operator--(int);         //optional

T operator*() const;
T& operator[](int) const;         //optional
};

int channels;
int size;
int sample_rate;
int bits;
iterator audio_iterator;
std::vector<T> data;

public:
Audio(std::vector<int8_t> values, int s_rate):channels(1),size(values.size()),bits(8),sample_rate(s_rate){
    
}
Audio(std::vector<int16_t> values, int s_rate) : channels(1), size(values.size()), bits(16), sample_rate(s_rate)
{
}
Audio(std::vector<std::pair<int8_t, int8_t>> values, int s_rate) : channels(2), size(values.size()), bits(8), sample_rate(s_rate)
{
}
Audio(std::vector<std::pair<int16_t, int16_t>> values, int s_rate) : channels(2), size(values.size()), bits(16), sample_rate(s_rate)
{
}
Audio(){

}
Audio(const Audio &);
Audio(Audio&&);
~Audio(){

}

Audio& operator=(const Audio&);
Audio&& operator=(Audio&&);
bool operator==(const Audio&) const;
bool operator!=(const Audio&) const;
Audio operator|(const Audio&);
Audio operator+(const Audio&);
Audio& operator^(const std::pair<float,float>);
Audio& operator*(const std::pair<float,float>);
iterator begin();
iterator end();
std::string toString(){
    return "N: "+channels+std::string(" Bit depth:") + std::to_string(bits)+std::string(" Samples: ")+std::to_string(size)+ std::string("Sample rate: ")+std::to_string(sample_rate);
}
};
#endif
