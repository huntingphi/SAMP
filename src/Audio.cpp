#include "../include/Audio.h"

// template<class T>std::string Audio<T>::toString(){
//     return "N: "+channels+std::string(" Bit depth:") + std::to_string(bits)+std::string(" Samples: ")+std::to_string(size)+ std::string("Sample rate: ")+std::to_string(sample_rate);
// }

// template <class T>
// Audio<T>::Audio(std::vector<int8_t> values, int s_rate) : channels(1), size(values.size()), bits(8), sample_rate(s_rate) {}
// template <class T>
// Audio<T>::Audio(std::vector<int16_t> values, int s_rate) : channels(1), size(values.size()), bits(16), sample_rate(s_rate){};
// template <class T>
// Audio<T>::Audio(std::vector<std::pair<int8_t, int8_t>> values, int s_rate) : channels(2), size(values.size()), bits(8), sample_rate(s_rate){};
// template <class T>
// Audio<T>::Audio(std::vector<std::pair<int16_t, int16_t>> values, int s_rate) : channels(2), size(values.size()), bits(16), sample_rate(s_rate){};