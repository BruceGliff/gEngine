#ifdef PRIMITIVE_DEF

#define PRIMITIVE(PRIM)                             \
class PRIM                                          \
  : public Primitive {                              \
  Model3D m_model;                                  \
public:                                             \
  PRIM()                                            \
    : m_model{getFolderPath() + #PRIM".obj"} {}           \
  void Draw() const override { m_model.Draw(); };   \
};

PRIMITIVE(Cube);
PRIMITIVE(Plane);
PRIMITIVE(Sphere);

#undef PRIMITIVE
#endif //PRIMITIVE_DEF

