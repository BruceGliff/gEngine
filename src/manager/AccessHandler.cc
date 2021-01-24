#include "AccessHandler.h"

Resources::EntityIdentifier::EntityIdentifier(std::string uniqName, std::filesystem::path absPath) :
	name {uniqName},
	path {absPath}
{
}

bool Resources::EntityIdentifier::operator==(EntityIdentifier const& other) const noexcept
{
    return (name == other.name
        && path == other.path);
}

std::string const& Resources::EntityIdentifier::getName() const noexcept
{
	return name;
}

std::filesystem::path const& Resources::EntityIdentifier::getPath() const noexcept
{
	return path;
}

std::size_t std::hash<Resources::EntityIdentifier>::operator()(Resources::EntityIdentifier const& k) const
{
    return ((hash<string>()(k.getName())
        ^ (std::filesystem::hash_value(k.getPath()) << 1)) >> 1);
}