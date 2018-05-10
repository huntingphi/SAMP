#ifndef AUDIO_H
#define AUDIO_H
#include <utility>


template <class T> //, class A = std::allocator<T> >
class Audio {
public:
class iterator {
public:

iterator();
iterator(const iterator&);
~iterator();

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

Audio();
Audio(const Audio &);
Audio(Audio&&);
~Audio();

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
};
#endif
