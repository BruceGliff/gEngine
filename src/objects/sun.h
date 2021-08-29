#include "../actor/actor.h"

class ALSun final : public NSActor::actor {
public:
  ALSun();
  // Overrides actor's function
  void Process(NSGeometry::Transformation const &) override;
};