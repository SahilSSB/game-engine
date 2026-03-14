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
	int rectLength;
};

enum PlayerState { NORMAL, WALK, JUMP, ATTACK, BLOCK, DASH };

class Player : public Entity {
private:
	float pSpeed = 200.f;
	float pJump = -500.f;
	float pGravity = 1600.f;
	bool isGrounded = false;
	bool isFacingRight = true;

	int pCurrentFrame = 0;
	float pAnimationTimer = 0.f;
	float pFrameDuration = 0.15f;
	const int NUM_FRAMES = 4;

	Vector2 pVelocity = {0, 0};
	int framesPerSecond = 0;
	Rectangle *rects;
	int rectLength = 0;
	Texture2D atlas;

	PlayerState state;

public:
	Animation currAnim;
	Vector2 getPosition() { return position; }
	void setPosition(Vector2 pos) { position = pos; }
	void update(float dt) override;
	void render() override;
	Animation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, std::vector<Rectangle> rect);
	void DrawSpriteAnimation(Animation anim, Rectangle rect, Vector2 origin, float rotation, Color tint);
	void handleInput(float dt);
	PlayerState getPlayerState() { return state; }
	void setPlayerState(PlayerState s) { state = s; }
};

#endif
