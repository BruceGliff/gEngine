// class represents raw array of pixels

#pragma once

namespace std {
    namespace filesystem {
        class path;
    } // namespace filesystem
} // namespace std

namespace Material {

class raw_texture {
    // flag if data cant be deleted (if errors occures or it has been already deleted)
    bool m_IsNoNeedToDelete = true;
    // if errors occure white texture loads
    unsigned char m_WhiteErrorTexture[6] = { 255, 255, 255, 0, 0, 0};
    void generateErrorTexture() noexcept;

    unsigned char* m_Data = 0;
    int m_Channels = 0;
    int m_Width = 0;
    int m_Height = 0;

public:
    // structure for returning texture data
    struct ret_data {
        unsigned char * const& Data;
        int const & Channels;
        int const & Width;
        int const & Height;
    };
private:
    ret_data const m_Return{m_Data, m_Channels, m_Width, m_Height};

public:
    raw_texture() noexcept;
    raw_texture(raw_texture const&)             = delete;
    raw_texture(raw_texture&&)                  = delete;
    raw_texture& operator=(raw_texture const&)  = delete;
    raw_texture& operator=(raw_texture&&)       = delete;

    raw_texture(std::filesystem::path const& AbsolutePath) noexcept;

    // Treate raw_texture as collection of data and texture properties
    ret_data const & operator()() const noexcept;

    // free stored data
    void Release() noexcept;
    virtual ~raw_texture();

    // Out texture in .ppm format. Without alpha. with name: out[dumpIDX].ppm
    void DumpTexture() const;
};

} // namespace Material

