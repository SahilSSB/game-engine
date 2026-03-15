#include "../include/corpse.hpp"

Corpse::Corpse() : Entity(100, 50) {}

void Corpse::updateHitbox() {
	hitbox.x = position.x - hitbox.width / 2;
	hitbox.y = position.y - hitbox.height / 2;
}

void Corpse::update(float dt) { updateHitbox(); }

void Corpse::render() {
	if (asset != nullptr) {
		DrawRectangleRec(hitbox, RED);
		Texture t = (*asset).getTexture();
		Rectangle src = {((float)t.width / 6) * 2, ((float)t.height / 4) * 1, (float)t.width / 6, (float)t.height / 4};
		Rectangle dest = {position.x, position.y, 128, 128};
		DrawTexturePro(t, src, dest, (Vector2){64, 64}, 0.f, (Color){255, 255, 255, 150});
	}
}
