#ifndef PLAYER_H
#define PLAYER_H

#include "entity.hpp"
#include "asset_manager.hpp"

class Player : public Entity {
private:
	Asset *playerAsset = nullptr;
public:
	Asset *getPlayerAsset() { return playerAsset; }
	void setPlayerAsset(Asset *a) { playerAsset = a; }
	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pos) { position = pos; }
	void update(float dt) override;
	void render() override;
};

#endif
