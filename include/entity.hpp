#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

class Entity {
protected:
	Vector2 position;

public:
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual ~Entity() {};
};

#endif
