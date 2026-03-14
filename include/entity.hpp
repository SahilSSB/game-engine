#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

#include "asset_manager.hpp"

class Entity {
protected:
	Asset *asset;
	Vector2 position;

public:
	Asset *getAsset() { return asset; }
	void setAsset(Asset *a) { asset = a; }
	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pos) { position = pos; }
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual ~Entity() {};
};

#endif
