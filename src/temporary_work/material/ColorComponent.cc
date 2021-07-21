#include "material.h"

namespace Material {

#define PLACE_COMPONENT(name) \
  name m_##name{};

#define GET_COMPONENT_PTR(name) \
  template <> name * getComponentTy<name>() { return &ColorTypesHolder.m_##name; };

struct _ColorTypesHolder {
    PLACE_COMPONENT(Diffuse);
    PLACE_COMPONENT(Ambient);
    PLACE_COMPONENT(Specular);

    _ColorTypesHolder() {
      static int NumberOfCpy {0};
      if (NumberOfCpy++) {
        //gError(attemt to create _ColorTypesHolder on stack)
      }
    }
} ColorTypesHolder;

GET_COMPONENT_PTR(Diffuse);
GET_COMPONENT_PTR(Ambient);
GET_COMPONENT_PTR(Specular);

#undef GET_COMPONENT_PTR
#undef PLACE_COMPONENT

} // namespace Material
