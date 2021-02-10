#include <string>
#include <iostream>
#include <vector>



class comp_base
{

public:
    virtual void out() = 0;
    virtual ~comp_base() {}
};

class camera : public comp_base
{
    int x;
    char * b;

public:
void out() override
{
    std::cout << "Camera x: " << x << std::endl; 
}
    camera(int a1, char * a2)
    {
        x = a1;
        b = a2;
    }

};

class mesh : public comp_base
{
    
    std::string a;
    int x;

public:
void out() override
{
    std::cout << "Mesh: " << a << std::endl; 
}
    mesh(std::string const & a1, int a2) : a{a1}, x{a2} {}
};


class scene
{
    std::vector<comp_base *> comps;
    
public:
    template <typename T, typename ... Args>
    void attach(Args && ... args)
    {
        comps.emplace_back(new T{std::forward<Args>(args) ...});
    }

    void dump()
    {
        for (auto && x : comps)
            x->out();
    }
};

int main()
{
    scene s;
    char a;
    s.attach<camera>(5, &a);
    s.attach<mesh>("asd", 3);

    s.dump();
}

  

