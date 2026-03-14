#ifndef CORPSE_H
#define CORPSE_H

#include "entity.hpp"

class Corpse : public Entity {
public:
	Corpse();
	void updateHitbox() override;
	void update(float dt) override;
	void render() override;
};

#endif
