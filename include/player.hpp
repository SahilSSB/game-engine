#ifndef PLAYER_H
#define PLAYER_H

#include "animation.hpp"
#include "entity.hpp"
#include "raylib.h"

enum class PlayerState { NORMAL, WALK, JUMP, ATTACK, BLOCK, DASH };

class Player : public Entity {
private:
	float pJump = -600.f;
	float pGravity = 1600.f;
	float pSpeed = 200.0f;
	Vector2 pVelocity = {0, 0};
	bool isGrounded = false;
	bool isFacingRight = true;

	Animation curAnim;
	float pAttackTimer = 0.f;

	PlayerState pState;

	void handleInput(float dt);
	void handlePhysics(float dt);

public:
	Player();
	void updateHitbox() override;
	void update(float dt) override;
	void render() override;

	PlayerState getPlayerState() { return pState; }
	void setPlayerState(PlayerState s) { pState = s; }
	Rectangle getHitbox() { return hitbox; }
	void setHitbox(Rectangle newh) { hitbox = newh; }
	Vector2 getVelocity() { return pVelocity; }
	void setPositionX(float x) { position.x = x; }
	void setPositionY(float y) { position.y = y; }
	void setVelocityX(float x) { pVelocity.x = x; }
	void setVelocityY(float y) { pVelocity.y = y; }
	void setGrounded(bool g) { isGrounded = g; }
};

#endif
