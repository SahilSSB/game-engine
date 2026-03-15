#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

#include "asset_manager.hpp"

class Entity {
protected:
	bool collidable = true;
	Asset *asset = nullptr;
	Vector2 position;
	Rectangle hitbox;

public:
	Entity(int w, int h) { hitbox = {position.x, position.y, (float)w, (float)h}; }
	Asset *getAsset() { return asset; }
	void setAsset(Asset *a) { asset = a; }
	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pos) { position = pos; }
  Rectangle getHitbox() { return hitbox; }
	virtual void updateHitbox() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual ~Entity() {};
};

#endif
