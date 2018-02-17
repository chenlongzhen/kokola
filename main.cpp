#include <iostream>
#include "kokola/io/reader.h"
#include "kokola/utils/log.h"

int main() {

    std::string files = "./data/test.data";

    Reader<float> Read(files,10,10,2,5,true);

    std::cout << "Hello, World!" << std::endl;

    return 0;

}