#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"

struct Animation {
	Texture2D atlas;
	int framesPerSecond;
	int targetRow, frameCount;
	float frameWidth, frameHeight;
};

Animation createSpriteAnimation(Texture2D atlas, int fps, int targetRow, int frameCount, float w, float h);
void drawSpriteAnimation(Animation anim, Rectangle rect, Vector2 origin, float rotation, bool flipX, Color tint);

#endif