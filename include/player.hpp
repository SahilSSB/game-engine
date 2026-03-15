#ifndef PLAYER_H
#define PLAYER_H

#include "animation.hpp"
#include "entity.hpp"
#include "raylib.h"

enum class PlayerState { NORMAL, WALK, JUMP, ATTACK, BLOCK, DASH, DEATH };

class Player : public Entity {
private:
	float pJump = -700.f;
	float pGravity = 1600.f;
	float pSpeed = 200.0f;
	Vector2 pVelocity = {0, 0};
	bool isGrounded = false;
	bool isFacingRight = true;

  int health = 100;
  int maxHealth = 100;
  bool isDead = false;
  float iFrameTimer = 0.f;
  float iFrameDuration = 0.5f;

	Animation curAnim;
	float pAttackTimer = 0.f;

	PlayerState pState;

	void handleInput(float dt);
	void handlePhysics(float dt);

  float shakeTimer = 0.f;
  float shakeDuration = 0.4f;
  float shakeMagnitude = 8.f;

  Rectangle attackHitbox = {0, 0, 0, 0};
  bool isAttackActive = false;

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
  
  int getHealth() const { return health; }
  bool checkDead() const { return isDead; }
  bool isInvincible() { return iFrameTimer > 0.f; }
  void tickIFrames(float dt) { if (iFrameTimer > 0.f) iFrameTimer -= dt; }
  
  void takeDamage(int amount) {
    if (iFrameTimer > 0.f) return;
    health -= amount;
    iFrameTimer = iFrameDuration;
    triggerShake();   // add this
    if (health <= 0) { health = 0; isDead = true; } 
  }

  bool isShaking() { return shakeTimer > 0.f; }
  float getShakeTimer() { return shakeTimer; }
  void triggerShake() { shakeTimer = shakeDuration; }
  void tickShake(float dt) { if (shakeTimer > 0.f) shakeTimer -= dt; }

  void reset() {
    health = maxHealth;
    isDead = false;
    iFrameTimer = 0.f;
    shakeTimer = 0.f;
    pVelocity = {0, 0};
    pState = PlayerState::NORMAL;
    pAttackTimer = 0.f;
  }

  Rectangle getAttackHitbox() { return attackHitbox; }
  bool getAttackActive() { return isAttackActive; }
  void updateAttackHitbox() {
    if (pState == PlayerState::ATTACK) {
        isAttackActive = true;
        float attackWidth = 80.f;
        float attackHeight = 60.f;
        if (isFacingRight) {
            attackHitbox = {
                position.x + hitbox.width / 2,
                position.y - attackHeight / 2,
                attackWidth,
                attackHeight
            };
        } else {
            attackHitbox = {
                position.x - hitbox.width / 2 - attackWidth,
                position.y - attackHeight / 2,
                attackWidth,
                attackHeight
            };
        }
    } else {
        isAttackActive = false;
        attackHitbox = {0, 0, 0, 0};
    }
  }

};

#endif
