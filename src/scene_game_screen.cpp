#include "raylib.h"

#include "../include/corpse.hpp"
#include "../include/entity_manager.hpp"
#include "../include/game.hpp"
#include "../include/game_state.hpp"
#include "../include/player.hpp"
#include <vector>

GameState state;

void GameScreen::onEnter() {
	p = new Player();
	p->setPosition((Vector2){40, 40});
	Texture2D atlas = assetM.getAsset("default")->getTexture();
	float frameWidth = 64.f;
	float frameHeight = 64.f;
	float sideWalkY = 11.f * frameHeight;
	std::vector<Rectangle> walkFrames;
	for (int i = 0; i < 9; i++) {
		walkFrames.push_back({(float)i * frameWidth, sideWalkY, frameWidth, frameHeight});
	}
	p->currAnim = p->CreateSpriteAnimation(atlas, 12, walkFrames);
	p->setPlayerAsset(assetM.getAsset("default"));

	Corpse *c = new Corpse();
	c->setPosition((Vector2){200, 200});
	state.addCorpsePosition((Vector2){200, 200});
	c->setAsset(assetM.getAsset("dead"));
	entityManager.add(c);

	// platforms
	platforms.push_back({0, 500, 1200, 50});
	platforms.push_back({200, 380, 200, 20});
	platforms.push_back({500, 300, 200, 20});
}

void GameScreen::update(float dt) {
	entityManager.flush();
	entityManager.updateAll(dt);
	p->update(dt);
	for (auto &platform : platforms) {
		if (CheckCollisionRecs(p->getHitbox(), platform)) {
			if (p->getVelocity().y > 0) {
				p->setPositionY(platform.y - (p->getHitbox().height / 2));
				p->setGrounded(true);
				p->setVelocityY(0);
			}
		}
	}
}

void GameScreen::render() {
	BeginDrawing();
	ClearBackground(BLACK);
	Texture bg = assetM.getAsset("background")->getTexture();
	DrawTexture(bg, 0, 0, (Color){255, 255, 255, 100});
	entityManager.renderAll();
	p->render();
	for (auto &platform : platforms) {
		DrawRectangleRec(platform, BROWN);
	}
	EndDrawing();
}

void GameScreen::onExit() {
	entityManager.clear();
	delete p;
}
