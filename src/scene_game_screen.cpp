#include "raylib.h"

#include "../include/game.hpp"
#include "../include/player.hpp"

void GameScreen::onEnter() {
	Player *p = new Player();
	p->setPosition((Vector2){0, 0});
	p->setPlayerAsset(assetM.getAsset("knight-sprites"));
	entities.push_back(p);
}

void GameScreen::update(float dt) {}

void GameScreen::render() {
	BeginDrawing();
	ClearBackground(BEIGE);
	DrawText("Game Screen", 350, 350, 30, BLACK);
	for (const auto &entity : entities) {
		entity->render();
	}
	EndDrawing();
}

void GameScreen::onExit() {
	for (const auto &entity : entities) {
		delete entity;
	}
	entities.clear();
}
