#pragma once

// Place all color components here and reserve memory and define methods fot them in ColorComponent.cc

#ifdef COLOR_COMPONENT_INCLUDE

#define COLOR_COMPONENT(name, id)                       \
struct name : IMaterialComponentTy {                    \
    int getID() const noexcept override { return ID; }  \
    void process() override {}                          \
private:                                                \
    int const ID {id};                                  \
};


// Base class for all color's component to implement
struct IMaterialComponentTy {
    virtual void process() {}
    virtual int getID() const noexcept { return -1; }
};
COLOR_COMPONENT(Diffuse, 0);
COLOR_COMPONENT(Ambient, 1);
COLOR_COMPONENT(Specular, 2);


#undef COLOR_COMPONENT
#endif //COLOR_COMPONENT_INCLUDE