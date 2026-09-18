#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <filesystem>

int parseHeader()
{
    char buf[8];
    std::ifstream file("../../models/model.safetensors", std::ios::binary);

    if(!file.is_open())
    {
        std::cerr << "Failed to open model.safetensors\n";
        return 1;
    }

    // Read first 8 bytes
    file.read(buf, 8); 

    // Copy to uint64_t DataType
    uint64_t n;
    memcpy(&n, buf,8);

    std::cout << "Model file opened successfully!\n";

    std::cout << n;

    file.close();

    return 0;
}

int main()
{

    parseHeader();
    return 0;
}