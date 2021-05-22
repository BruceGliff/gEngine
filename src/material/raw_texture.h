// class represent raw array of pixels

#pragma once

#include <filesystem>

namespace Material {

class raw_texture {
    // flag if data cant be deleted (if errors occures or it has been already deleted)
    bool isNoNeedToDelete = true;
    // if errors occure white texture loads
    unsigned char whiteErrorTexture[6] = { 255, 255, 255, 0, 0, 0};
    void generateErrorTexture() noexcept;
protected:
    unsigned char* data = 0;
    int channels = 0;
    int width = 0;
    int height = 0;
public:
    raw_texture() noexcept;
    raw_texture(raw_texture const&)             = delete;
    raw_texture(raw_texture&&)                  = delete;
    raw_texture& operator=(raw_texture const&)  = delete;
    raw_texture& operator=(raw_texture&&)       = delete;

    raw_texture(std::filesystem::path const& relevantPath) noexcept;

    // free stored data
    void Release() noexcept;
    virtual ~raw_texture();

    // Out texture in .ppm format. Without alpha. with name: out[dumpIDX].ppm
    void DumpTexture() const;
};

} // namespace Material

