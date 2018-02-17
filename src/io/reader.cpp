//
// Created by clz on 2018/2/17.
//  1. read files to buffer(samples)
//  2. get size lines to samples
//  3. parseLine
//
#include <sstream>
#include <iostream>
#include "kokola/io/reader.h"

inline int round(int cur, int size) {
    return (cur >= size) ? (cur - size) : cur;
}

template <typename T>
Reader<T>::Reader(
        const std::string&files,
        size_t row_size,
        int output_size,
        size_t update_per_sample,  // = minibatch_size * sync_frequency
        int max_row_buffer_count,
        bool init):

         eof_(true),
         reading_file_(0),
         thread_(nullptr),
         row_size_(row_size),
         output_size_(output_size),
         // use 2x size buffer
         buffer_size_(max_row_buffer_count * 3),
         sample_batch_size_(update_per_sample),
         sample_count_(0)

{

    // read files to vector
    size_t p = files.find(';');
    size_t prev = 0;
    while (p != -1){
        files_.push_back(files.substr(prev, p - prev));
        prev = p + 1;
        p = files.find(';', prev);
    }

    files_.push_back(files.substr(prev));

    buffer_ = CreateSamples<T>(buffer_size_, row_size);


    if (init){
        thread_ = new std::thread(&Reader<T>::Main, this);
    }

}


template <typename T>
void Reader<T>::ParseLine(const std::string&line, int idx){
    Sample<T>* data = this->buffer_[idx];
    data->values.clear();
    std::stringstream iss(line);
    iss >> data->label;

    size_t index;
    T value;

    data->keys.clear();
    char c;
    while(iss >> index >> c >> value){
        data->keys.push_back(index);
        data->values.push_back(value);
    }

    //for bias;
    data->keys.push_back(rowsize - 1);

}

template <typename T>
void Reader<T>::Main(){
   std::string line;
  //Log::Write(Debug, "Start reader thread\n");
  while (true) {
    while (eof_) {
      if (!buffer_size_)  return;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    //Log::Write(Debug, "SampleReader begin read file %s\n",
    std::cout << files_[reading_file_].c_str() << std::endl;
    std::unique_lock<std::mutex> lock(mutex_);
    // timer_.Start();
    while (reader_->GetLine(line)) {
      /* if (length_ == buffer_size_) {
        Log::Write(Debug, "reader read sample average time %f\n", \
          timer_.ElapseMilliSeconds() / buffer_size_ * 2);
      } */
      while (length_ == buffer_size_) {
        cv_.wait(lock);
        //当 std::condition_variable 对象的某个 wait 函数被调用的时候，
        // 它使用 std::unique_lock(通过 std::mutex) 来锁住当前线程。当前线程会一直被阻塞，直到另外一个线程在相同的
      }
      ParseLine(line, end_);
      ++length_;
      end_ = round(++end_, buffer_size_);
    }
    //Log::Write(Debug, "SampleReader end of file %s\n",
    //  files_[reading_file_++].c_str());
    if (reading_file_ < files_.size()) {
      delete reader_;
      reader_ = new TextReader(URI(files_[reading_file_]), 1024);
      continue;
    }
//    if (cur_keys_->size() != 0) {
//      keys_.Push(cur_keys_);
//      cur_keys_ = new SparseBlock<bool>(); ////cccc
//    }
    eof_ = true;
  }
  //Log::Write(Debug, "End reader th){


}
