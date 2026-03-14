#include "../include/player.hpp"
#include "raylib.h"
#include <cstddef>
#include <cstdlib>
#include <vector>

void Player::update(float dt) {
 handleInput(dt);
<<<<<<< HEAD
 pVelocity.y += pGravity * dt;
 position.x += pVelocity.x * dt;
 position.y += pVelocity.y * dt;
 
=======

 pVelocity.y += pGravity * dt;
 position.x += pVelocity.x * dt;
 position.y += pVelocity.y * dt;

>>>>>>> a77e24b (completed player animations)
 if (position.y >= 200) {
        position.y = 200;
        pVelocity.y = 0;
        isGrounded = true;
    }
<<<<<<< HEAD
=======

  if (pState == PlayerState::ATTACK) return;

  if (pState != PlayerState::ATTACK) {
        pVelocity.y += pGravity * dt;
  }
  else {
        pVelocity.y = 0;
  }
  if (pState == PlayerState::ATTACK) {
    pAnimationTimer += dt;
    if (pAnimationTimer >= 0.70f) {
      pState = PlayerState::NORMAL;
      pAnimationTimer = 0.f;
    }
  }
  else {
    if (!isGrounded) {
      pState = PlayerState::JUMP;
    }
    else if (std::abs(pVelocity.x) > 0.1f) {
      pState = PlayerState::WALK;
    }
    else {
      pState = PlayerState::NORMAL;
    }
  }

>>>>>>> a77e24b (completed player animations)
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
	if (playerAsset != nullptr) {
<<<<<<< HEAD
    float scale = 1.f;
		Texture t = (*playerAsset).getTexture();
    int frameIndex = 0;
    if (pVelocity.x != 0) {
      frameIndex = (int)(GetTime() * currAnim.framesPerSecond) % currAnim.rects.size();
    }
    else frameIndex = 0;
		Rectangle src = currAnim.rects[frameIndex]; 
    if (!isFacingRight) {
      src.width += -1;
    }
		Rectangle dest = {position.x, position.y, 128, 128};
		DrawTexturePro(t, src, dest, (Vector2){64, 64}, 0.0f, WHITE);
=======
  int targetRow = 0;
  int totalFrames = 1;
  float fw = 64;
  float fh = 64;
  
  switch (pState) {
    case PlayerState::NORMAL: targetRow = 7;  totalFrames = 1; break;
    case PlayerState::WALK: targetRow = 11; totalFrames = 9; break;
    case PlayerState::JUMP:   targetRow = 29; totalFrames = 5; break;
    case PlayerState::ATTACK: fw = 192.0f;  targetRow = 64; totalFrames = 6; break;
  }

  int frameIndex = 0;
  if (totalFrames > 1) {
    frameIndex = (int)(GetTime() * 12.0f) % totalFrames;
  }
    float scale = 2.f;
		Texture t = (*playerAsset).getTexture();
		Rectangle src = { (float)frameIndex * fw, (float)targetRow * fh, fw, fh };
    
    if (!isFacingRight) src.width = -fw;
    else src.width = fw;
		
    Rectangle dest = {position.x, position.y, fw * scale, fh * scale};
    Vector2 origin = {fw, fh};
    DrawTexturePro(t, src, dest, origin, 0.0f, WHITE);
>>>>>>> a77e24b (completed player animations)
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
 if (anim.rects.empty() || anim.framesPerSecond == 0) return;
 int index = int(GetTime() * anim.framesPerSecond) % anim.rects.size();
 Rectangle source = anim.rects[index];
 DrawTexturePro(anim.atlas, source, rect, origin, rotation, tint);
}

void Player::handleInput(float dt) {
  pVelocity.x = 0;
  if (IsKeyDown(KEY_A)) {
        pVelocity.x = -pSpeed;
        isFacingRight = false;
<<<<<<< HEAD
=======
        pState = PlayerState::WALK;
>>>>>>> a77e24b (completed player animations)
    };
    if (IsKeyDown(KEY_D)) {
        pVelocity.x = pSpeed;
        isFacingRight = true;
<<<<<<< HEAD
    };
    if (IsKeyPressed(KEY_SPACE)) {
      pVelocity.y = pJump;
      isGrounded = false;
    }
=======
        pState = PlayerState::WALK;
    };
    if (IsKeyPressed(KEY_SPACE)) {
      pState = PlayerState::JUMP;
      pVelocity.y = pJump;
      isGrounded = false;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && pState != PlayerState::ATTACK) {
      pState = PlayerState::ATTACK;
    }
>>>>>>> a77e24b (completed player animations)
}
