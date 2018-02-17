//
// Created by clz on 2018/2/17.
//

#ifndef KOKOLA_COMMON_H
#define KOKOLA_COMMON_H

#include <string>
#include <vector>

template <typename T>
struct Sample {
    int label;
    std::vector<size_t> keys;
    std::vector<T> values;

    Sample(size_t data_size) {
        values.reserve(data_size);
    }
};

template <typename T>
Sample<T>** CreateSamples(int num, size_t size) {
    Sample<T>**samples = new Sample<T>*[num];
    for (int i = 0; i < num; ++i) {
        samples[i] = new Sample<T>(size);
    }
    return samples;
}





#endif //KOKOLA_COMMON_H
