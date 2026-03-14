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

enum class PlayerState {
	NORMAL, WALK, JUMP, ATTACK, BLOCK, DASH
};

enum PlayerState { NORMAL, WALK, JUMP, ATTACK, BLOCK, DASH };

class Player : public Entity {
private:
  float pJump = -600.f;
  float pGravity = 1600.f;
  bool isGrounded = false;
  bool isFacingRight = true;

  int pCurrentFrame = 0;
  float pAnimationTimer = 0.f;
  float pFrameDuration = 0.15f;
  const int NUM_FRAMES = 4;

  Vector2 pVelocity = {0 ,0};
	Asset *playerAsset = nullptr;
  int framesPerSecond = 0;
  Rectangle* rects;
  int rectLength = 0;
  Texture2D atlas;

public:
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
	PlayerState getPlayerState() { return state; }
	void setPlayerState(PlayerState s) { state = s; }
};

#endif
