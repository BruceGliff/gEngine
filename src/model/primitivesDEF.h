#ifdef PRIMITIVE_DEF

#define PRIMITIVE(PRIM_NAME)                          \
class PRIM_NAME                                       \
  : public Primitive {                                \
  Model3D m_model;                                    \
public:                                               \
  PRIM_NAME()                                         \
    : m_model{getFolderPath() + #PRIM_NAME".obj"} {}  \
  void Draw() const override { m_model.Draw(); };     \
};

PRIMITIVE(Cube);
PRIMITIVE(Plane);
PRIMITIVE(Sphere);

#undef PRIMITIVE
#endif //PRIMITIVE_DEF
