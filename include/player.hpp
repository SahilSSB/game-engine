#ifndef PLAYER_H
#define PLAYER_H

#include "asset_manager.hpp"
#include "entity.hpp"
#include "raylib.h"
#include <vector>

struct Animation {
	Texture2D atlas;
	int framesPerSecond;
	std::vector<Rectangle> rects;
};

enum class PlayerState { NORMAL, WALK, JUMP, ATTACK, BLOCK, DASH };

class Player : public Entity {
private:
	float pJump = -600.f;
	float pGravity = 1600.f;
	float pSpeed = 200.0f;
	bool isGrounded = false;
	bool isFacingRight = true;

	int pCurrentFrame = 0;
	float pAnimationTimer = 0.f;
	float pFrameDuration = 0.15f;
	const int NUM_FRAMES = 4;

	Vector2 pVelocity = {0, 0};
	Asset *playerAsset = nullptr;
	int framesPerSecond = 0;
	Rectangle *rects;
	Texture2D atlas;

public:
	Player();
	PlayerState pState;
	Animation currAnim;
	Asset *getPlayerAsset() { return playerAsset; }
	void setPlayerAsset(Asset *a) { playerAsset = a; }
	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pos) { position = pos; }
	void updateHitbox() override;
	void update(float dt) override;
	void render() override;
	Animation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, std::vector<Rectangle> rect);
	void DrawSpriteAnimation(Animation anim, Rectangle rect, Vector2 origin, float rotation, Color tint);
	void handleInput(float dt);
	PlayerState getPlayerState() { return pState; }
	void setPlayerState(PlayerState s) { pState = s; }

	Rectangle getHitbox() { return hitbox; }
	Vector2 getVelocity() { return pVelocity; }
	void setVelocityY(float y) { pVelocity.y = y; }
	void setPositionY(float y) { position.y = y; }
	void setGrounded(bool g) { isGrounded = g; }
};

#endif
