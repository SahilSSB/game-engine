#ifndef PLAYER_H
#define PLAYER_H

#include "entity.hpp"

enum PlayerState {
	NORMAL, WALK, JUMP, ATTACK, BLOCK, DASH
};

class Player : public Entity {
private:
	Vector2 velocity;
	PlayerState playerState;
public:
	Vector2 getVelocity() { return velocity; }
	void setVelocity(Vector2 v) { velocity = v; }
	PlayerState getPlayerState() { return playerState; }
	void setPlayerState(PlayerState s) { playerState = s; }
	void update(float dt) override;
	void render() override;
};

#endif
