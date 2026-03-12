#include "../include/player.hpp"

void Player::update(float dt) {
	
}

void Player::render() {
	if (playerAsset != nullptr) {
		Texture t = (*playerAsset).getTexture();
		Rectangle src = {0, 0, (float)t.width / 7, (float)t.height / 4};
		Rectangle dest = {position.x, position.y, t.width * 0.6f / 7, t.height * 0.6f / 4};
		DrawTexturePro(t, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
	}
}
