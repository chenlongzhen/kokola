//
// Created by clz on 2018/2/17.
//

#ifndef KOKOLA_READER_H
#define KOKOLA_READER_H

#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "kokola/utils/common.h"
#include "io.h"


template  <typename T>
class Reader{

public:
    Reader(
            const std::string&files,
            size_t row_size,
            int output_size,
            size_t update_per_sample,  // = minibatch_size * sync_frequency
            int max_row_buffer_count,
            bool init
    );
    void ParseLine(const std::string&line, int idx);
    void Main();

    virtual ~Reader();

protected:
    using TextReader = kokola::TextReader;
    using URI = kokola::URI;

    Sample<T>** buffer_;
    bool eof_;
    int reading_file_;
    std::vector<std::string> files_;

    std::thread* thread_;
    int start_;
    int length_;
    int end_;
    int read_length_;

    size_t row_size_;
    int output_size_;
    int buffer_size_;
    int rowsize;
    size_t sample_batch_size_;
    size_t sample_count_;

    std::mutex mutex_;
    std::condition_variable cv_;

    TextReader *reader_;

};


#endif //KOKOLA_READER_H
