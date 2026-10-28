#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

// Metadata for one tensor, from the JSON header
struct TensorInfo
{
    std::string name;
    std::vector<int64_t> shape;
    uint64_t begin = 0;
    uint64_t end = 0;

    int64_t numel() const
    {
        int64_t n = 1;
        for (int64_t d : shape)
            n *= d;
        return n;
    }
};

class SafeTensors
{
public:
    bool load(const std::string& path);
    const TensorInfo* find(const std::string& name) const;
    const float* data(const TensorInfo& t) const;

    const std::vector<TensorInfo>& tensors() const {return tensors_;}
    uint64_t bloblSize() const { return blob_.size(); }

private:
    bool parseHeader (const std::string& join);
    std::vector<TensorInfo> tensors_;
    std::unordered_map<std::string, size_t> index_; // index of tensors
    std::vector<uint8_t> blob_; // weight bytes
};