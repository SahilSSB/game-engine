#include "../include/corpse.hpp"

void Corpse::update(float dt) {}

void Corpse::render() {
	if (asset != nullptr) {
		Texture t = (*asset).getTexture();
		Rectangle src = {0, 0, (float)t.width, (float)t.height};
		Rectangle dest = {position.x, position.y, (float)t.width, (float)t.height};
		DrawTexturePro(t, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
	}
}
