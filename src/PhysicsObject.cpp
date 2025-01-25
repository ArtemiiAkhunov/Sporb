#include "bn_fixed_point_fwd.h"
class PhysicsObject {
public:
  virtual bn::fixed_point getPos() const;
  virtual void setPos(bn::fixed_point pos);
  virtual bool canInteract(PhysicsObject obj) const;
};
