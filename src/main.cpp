#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

int main(int argc, char* argv[])
{
    if(argc  < 2)
    {
        std::cerr << "Usage: gpt2 <model.safetensors>\n";
        return 1;
    }

    const std::string path = argv[1];

    // Opening in binary mode, read raw bytes and no text conversion
    std::ifstream file(path, std::ios::binary);

    if(!file)
    {
        std::cerr << "Cannot open " << path << "\n";
        return 1;
    }

    // First 8 bytes = header length (little-endian uint64_t)
    char lenBytes[8];

    if (!file.read(lenBytes, 8))
    {
        std::cerr <<  "File too short\n";
        return 1;
    }

    uint64_t headerLen = 0;
    std::memcpy(&headerLen, lenBytes, 8); // raw bytes -> integer
    std::cout << "Header length: " <<  headerLen << " bytes\n";

    std::string headerText(headerLen, '\0');

    if(!file.read(headerText.data(), static_cast<std::streamsize>(headerLen)))
    {
        std::cerr << "Failed to read header\n";
        return 1;
    }

    // Parse JSON
    nlohmann::json header;

    try 
    {
        header = nlohmann::json::parse(headerText);
    }
    catch(const nlohmann::json::exception& e)
    {
        std::cerr << "Bad JSON: " << e.what() <<  "\n";
        return 1;
    }

    // Print each tensor: Name, Dtype, Shape, Byte Size
    int count = 0;
    for (const auto& [name, info] : header.items())
    {
        if (name == "__metadata__")
            continue;
        
        const auto shape = info["shape"].get<std::vector<int64_t>>();
        const auto offsets = info["data_offsets"].get<std::vector<uint64_t>>();

        std::cout << name <<  " " << info["dtype"].get<std::string>() << " [";
        for (size_t i = 0; i < shape.size(); i++)
        {
            std::cout << (i ? ", " : "") << shape[i];
        }
        std::cout << "] " <<  (offsets[1] - offsets[0]) << " bytes\n";

        ++count;
    }

    std::cout << "Tensor count: " << count << "\n";
    return 0;
}