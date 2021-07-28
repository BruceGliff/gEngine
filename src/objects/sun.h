#include "../actor/actor.h"

class ALSun final : public NSActor::actor {
public:
  ALSun();
  void Process(NSGeometry::Transformation const &) override;
};