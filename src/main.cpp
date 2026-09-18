#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <filesystem>

std::string parseHeader(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        std::cerr << "Failed to open model file:"
                  << path << '\n';
        return "";
    }

    // Read the first 8 bytes
    char buf[8];
    file.read(buf, 8);

    if (!file)
    {
        std::cerr << "Error: Failed to read 8-Byte header from model file!\n";
        return "";
    }

    // Convert the 8 bytes into uint64_t
    uint64_t n;
    memcpy(&n, buf, 8);

    std::cout << "Header size: " << n << " bytes\n";

    // Read the JSON header
    std::string json(n, '\0');

    file.read(json.data(), n);

    // Read the first 200 char
    std::cout << json.substr(0,200) << '\n';

    if (!file)
    {
        std::cerr << "Error: Failed to open JSON header\n";
        return "";
    }

    // weightsSize = total file size - 8 - JSON header size
    uint64_t fileSize = std::filesystem::file_size(path);
    uint64_t weightsSize = fileSize - 8 - n;

    std::cout << "Weights blob size: "
              << weightsSize
              << " bytes\n";


    return json;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: gpt2 <model_path>\n";
        return 1;
    }

    std::string json = parseHeader(argv[1]);

    if(json.empty())
    {
        return 1;
    }
    // std::cout << "JSON header:\n";
    // std::cout << json << '\n';

    return 0;
}