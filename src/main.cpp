#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <filesystem>
#include <string>

// Include JSON.cpp
#include <nlohmann/json.hpp>

struct TensorInfo
{
    std::string name;
    std::vector<int64_t> shape;
    uint64_t begin, end; // byte offsets into the blob
};

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

    if (!file)
    {
        std::cerr << "Error: Failed to open JSON header\n";
        return "";
    }

    // Read the first 200 char
    std::cout << json.substr(0, 200) << '\n';

    // weightsSize = total file size - 8 - JSON header size
    uint64_t fileSize = std::filesystem::file_size(path);
    uint64_t weightsSize = fileSize - 8 - n;

    std::cout << "Weights blob size: "
              << weightsSize
              << " bytes\n";

    return json;
}

std::vector<TensorInfo> parseTensors(const std::string &jsonString)
{
    std::vector<TensorInfo> tensors;
    auto j = nlohmann::json::parse(jsonString);

    for (auto &[key, val] : j.items())
    {
        // Skip metadata
        if (key == "__metadata__")
        {
            continue;
        }

        if (!val.contains("shape") || !val.contains("data_offsets"))
        {
            std::cerr << "Skipping invalid tensor: " << key << '\n';
            continue;
        }

        TensorInfo tensor;

        tensor.name = key;
        tensor.shape = 
            val["shape"].get<std::vector<int64_t>>();

        auto offsets = 
            val["data_offsets"].get<std::vector<uint64_t>>();

        if (offsets.size() != 2)
        {
            std::cerr << "Invalid data_offsets for tensor: "
                      << key
                      << " (expected 2 values, got "
                      << offsets.size() << ")\n";

            continue;
        }

        tensor.begin = offsets[0];
        tensor.end = offsets[1];

        tensors.push_back(tensor);
    }

    return tensors;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: gpt2 <model_path>\n";
        return 1;
    }

    std::string json = parseHeader(argv[1]);

    if (json.empty())
    {
        return 1;
    }

    std::vector<TensorInfo> tensors = parseTensors(json);
    std::cout << "\nTensors:\n";

    uint64_t maxEnd = 0;

    for (const auto &tensor : tensors)
    {
        std::cout << tensor.name << " ";
        std::cout << "[";

        for (size_t i = 0; i < tensor.shape.size(); ++i)
        {
            if (i > 0)
            {
                std::cout << ", ";
            }
            std::cout << tensor.shape[i];
        }

        std::cout << "] ";

        uint64_t bytes = tensor.end - tensor.begin;

        std::cout << bytes << " bytes\n";

        if (tensor.end > maxEnd)
        {
            maxEnd = tensor.end;
        }
    }

    std::cout << "\nTensor count: " << tensors.size() << '\n';
    std::cout << "Max tensor end: " << maxEnd << " bytes\n";

    return 0;
}