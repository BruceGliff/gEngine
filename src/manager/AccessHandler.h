#pragma once

#include <string>
#include <filesystem>

// Not used yet
namespace Resources {
    class EntityIdentifier
    {
        std::string             name;
        std::filesystem::path   path;

    public:
        EntityIdentifier()                                      = delete;
        EntityIdentifier(EntityIdentifier const&)               = delete;
        EntityIdentifier(EntityIdentifier&&)                    = delete;
        EntityIdentifier& operator =(EntityIdentifier const&)   = delete;
        EntityIdentifier& operator =(EntityIdentifier&&)        = delete;

        EntityIdentifier(std::string uniqName, std::filesystem::path absPath);

        bool operator==(EntityIdentifier const& other) const noexcept;

        std::string const& getName() const noexcept;
        std::filesystem::path const& getPath() const noexcept;

    };
}
namespace std {

    template <>
    struct hash<Resources::EntityIdentifier>
    {
        std::size_t operator()(Resources::EntityIdentifier const& k) const;
    };
}