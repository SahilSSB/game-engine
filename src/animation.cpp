#include "../include/animation.hpp"

Animation createSpriteAnimation(Texture2D atlas, int fps, int targetRow, int frameCount, float w, float h) {
	Animation anim = {atlas, fps, targetRow, frameCount, w, h};
	return anim;
}

void drawSpriteAnimation(Animation anim, Rectangle rect, Vector2 origin, float rotation, bool flipX, Color tint) {
	if (anim.frameCount == 0 || anim.framesPerSecond == 0)
		return;
	int index = int(GetTime() * anim.framesPerSecond) % anim.frameCount;

	Rectangle source = {(float)index * anim.frameWidth, (float)anim.targetRow * anim.frameHeight,
	                    flipX ? -anim.frameWidth : anim.frameWidth, anim.frameHeight};
	DrawTexturePro(anim.atlas, source, rect, origin, rotation, tint);
}