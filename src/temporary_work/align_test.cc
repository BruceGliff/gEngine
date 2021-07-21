#include <iostream>

struct Color {
    float a,b,c,d;
};

struct alignas(sizeof(Color)) Texture
{
    Color * pTexture;
};

int main() {
    std::cout << sizeof(Color) << ' ' << alignof(Color) << '\n' << sizeof(Texture) << ' ' << alignof(Texture) << std::endl;
    return 0;
}
