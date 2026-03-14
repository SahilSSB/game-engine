#include "../include/player.hpp"
#include "raylib.h"
#include <vector>

void Player::update(float dt) {
	handleInput(dt);
	pVelocity.y += pGravity * dt;
	position.x += pVelocity.x * dt;
	position.y += pVelocity.y * dt;

	if (position.y >= 200) {
		position.y = 200;
		pVelocity.y = 0;
		isGrounded = true;
	}
	if (pVelocity.x != 0) {
		pAnimationTimer += dt;
		if (pAnimationTimer >= 0.1f) {
			pCurrentFrame = (pCurrentFrame + 1) % 4;
			pAnimationTimer = 0.0f;
		}
	} else {
		pCurrentFrame = 0;
	}
}

void Player::render() {
	if (asset != nullptr) {
		float scale = 1.f;
		Texture t = (*asset).getTexture();
		int frameIndex = 0;
		if (pVelocity.x != 0) {
			frameIndex = (int)(GetTime() * currAnim.framesPerSecond) % currAnim.rects.size();
		} else
			frameIndex = 0;
		Rectangle src = currAnim.rects[frameIndex];
		if (!isFacingRight) {
			src.width += -1;
		}
		Rectangle dest = {position.x, position.y, 128, 128};
		DrawTexturePro(t, src, dest, (Vector2){64, 64}, 0.0f, WHITE);
	}
}

Animation Player::CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, std::vector<Rectangle> rects) {
	Animation anim;
	anim.atlas = atlas;
	anim.framesPerSecond = framesPerSecond;
	anim.rects = rects;
	return anim;
}

void Player::DrawSpriteAnimation(Animation anim, Rectangle rect, Vector2 origin, float rotation, Color tint) {
	if (anim.rects.empty() || anim.framesPerSecond == 0)
		return;
	int index = int(GetTime() * anim.framesPerSecond) % anim.rects.size();
	Rectangle source = anim.rects[index];
	DrawTexturePro(anim.atlas, source, rect, origin, rotation, tint);
}

void Player::handleInput(float dt) {
	pVelocity.x = 0;
	if (IsKeyDown(KEY_A)) {
		pVelocity.x = -pSpeed;
		isFacingRight = false;
	}
	if (IsKeyDown(KEY_D)) {
		pVelocity.x = pSpeed;
		isFacingRight = true;
	}
	if (IsKeyPressed(KEY_SPACE)) {
		pVelocity.y = pJump;
		isGrounded = false;
	}
}
