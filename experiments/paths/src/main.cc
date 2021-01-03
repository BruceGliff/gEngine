#include <filesystem>
#include <iostream>
#include <unordered_map>

namespace std {

    template <>
    struct hash<std::filesystem::path>
    {
        std::size_t operator()(std::filesystem::path const& k) const
        {
            return std::filesystem::hash_value(k);
        }
    };
}

int main(int argc, char * argv[])
{
    std::cout << argv[0] << std::endl;

    std::filesystem::path path{argv[0]};
    path.remove_filename();

    std::filesystem::path np{path / "a\\b\\c.txt"};

    std::cout << np.lexically_normal();

    std::unordered_map  <std::filesystem::path, std::string> map;



    
}