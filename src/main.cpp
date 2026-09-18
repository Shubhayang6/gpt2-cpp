#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <filesystem>

int parseHeader(const char *modelPath)
{
    std::ifstream file(modelPath, std::ios::binary);

    if (!file)
    {
        std::cerr << "Failed to open model file:"
                  << modelPath << '\n';
        return 1;
    }

    char buf[8];
    file.read(buf, 8);

    if (!file)
    {
        std::cerr << "Error: Failed to read 8-Byte header from model file!\n";
        return 1;
    }

    // Copy to uint64_t DataType
    uint64_t n;
    memcpy(&n, buf, 8);

    std::cout << "Header size: "<< n << " bytes\n";

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Usage: gpt2 <model_path>\n";
        return 1;
    }

    return parseHeader(argv[1]);
}