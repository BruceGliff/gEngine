#include <filesystem>
#include <iostream>


int main(int argc, char * argv[])
{
    std::cout << argv[0] << std::endl;

    std::filesystem::path path{argv[0]};
    path.remove_filename();

    std::filesystem::path np{path / "a\\b\\c.txt"};

    std::cout << np.lexically_normal();



    
}