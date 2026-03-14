#include "raylib.h"

#include "../include/corpse.hpp"
#include "../include/entity_manager.hpp"
#include "../include/game.hpp"
#include "../include/game_state.hpp"
#include "../include/player.hpp"
#include <vector>

GameState state;

void GameScreen::onEnter() {
	Player *p = new Player();
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
	entityManager.add(p);

	Corpse *c = new Corpse();
	c->setPosition((Vector2){200, 200});
	state.addCorpsePosition((Vector2){200, 200});
	c->setAsset(assetM.getAsset("dead"));
	entityManager.add(c);
}

void GameScreen::update(float dt) {
	entityManager.flush();
	entityManager.updateAll(dt);
}

void GameScreen::render() {
	BeginDrawing();
	ClearBackground(BLACK);
	Texture bg = assetM.getAsset("background")->getTexture();
	DrawTexture(bg, 0, 0, (Color){255, 255, 255, 100});
	entityManager.renderAll();
	EndDrawing();
}

void GameScreen::onExit() { entityManager.clear(); }
