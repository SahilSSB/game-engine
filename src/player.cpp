#include "../include/player.hpp"
#include "../include/animation.hpp"

#include "raylib.h"

#include <cstdlib>

Player::Player() : Entity(60,100) {}

void Player::updateHitbox() {
	hitbox.x = position.x - hitbox.width / 2;
	hitbox.y = position.y - hitbox.height / 2 + 10;
}

void Player::update(float dt) {
  if (isDead || health <= 0) {
        pState = PlayerState::DEATH;
        pVelocity = {0, 0};
        return;
  }
	handleInput(dt);
	handlePhysics(dt);
	updateHitbox();
  updateAttackHitbox();
	if (pState == PlayerState::ATTACK) {
		pAttackTimer += dt;
		if (pAttackTimer >= 0.70f) {
			pState = PlayerState::NORMAL;
			pAttackTimer = 0.f;
		}
	} else {
		if (!isGrounded) {
			pState = PlayerState::JUMP;
		} else if (std::abs(pVelocity.x) > 0.1f) {
			pState = PlayerState::WALK;
		} else {
			pState = PlayerState::NORMAL;
		}
	}
}

void Player::render() {
	if (asset != nullptr) {
		DrawRectangleRec(hitbox, RED);
    if (isAttackActive) DrawRectangleRec(attackHitbox, {0, 255, 0, 120});
		int targetRow = 0;
		int totalFrames = 1;
		float fw = 64;
		float fh = 64;

		switch (pState) {
		case PlayerState::NORMAL:
			targetRow = 7;
			totalFrames = 1;
			break;
		case PlayerState::WALK:
			targetRow = 11;
			totalFrames = 9;
			break;
		case PlayerState::JUMP:
			targetRow = 29;
			totalFrames = 5;
			break;
		case PlayerState::ATTACK:
			fw = 192.0f;
			targetRow = 64;
			totalFrames = 6;
			break;
		default:
			break;
		}

		curAnim = createSpriteAnimation(asset->getTexture(), 12, targetRow, totalFrames, fw, fh);

		float scale = 2.f;
		Rectangle dest = {position.x, position.y, fw * scale, fh * scale};
		Vector2 origin = {fw, fh};
		drawSpriteAnimation(curAnim, dest, origin, 0.f, !isFacingRight, WHITE);
	}
}

void Player::handleInput(float dt) {
	pVelocity.x = 0;
	if (IsKeyDown(KEY_A)) {
		pVelocity.x = -pSpeed;
		isFacingRight = false;
		pState = PlayerState::WALK;
	}
	if (IsKeyDown(KEY_D)) {
		pVelocity.x = pSpeed;
		isFacingRight = true;
		pState = PlayerState::WALK;
	}
	if (IsKeyPressed(KEY_SPACE) && isGrounded) {
		pState = PlayerState::JUMP;
		pVelocity.y = pJump;
		isGrounded = false;
	}
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && pState != PlayerState::ATTACK) {
		pState = PlayerState::ATTACK;
	}
}

void Player::handlePhysics(float dt) {
	pVelocity.y += pGravity * dt;
	position.x += pVelocity.x * dt;
	position.y += pVelocity.y * dt;
}
