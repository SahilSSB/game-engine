#include "raylib.h"

#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/game_state.hpp"

void GameScreen::onEnter() {
	player = new Player();
	player->setPosition((Vector2){0, 0});
	player->setPlayerState(NORMAL);
	player->setAsset(assetM.getAsset("test2"));
}

void GameScreen::update(float dt) {
	float speed = 400;
	Vector2 pos = player->getPosition();

	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		speed += 200;
	}

	if (IsKeyDown(KEY_W)) {
		if (pos.y > 0) pos.y -= speed * dt;
	}
	if (IsKeyDown(KEY_S)) {
		if (pos.y < 700) pos.y += speed * dt;
	}
	if (IsKeyDown(KEY_A)) {
		if (pos.x > 0) pos.x -= speed * dt;
	}
	if (IsKeyDown(KEY_D)) {
		if (pos.x < 1200) pos.x += speed * dt;
	}
	
	player->setPosition(pos);
}

void GameScreen::render() {
	BeginDrawing();
	ClearBackground(BEIGE);
	DrawText("Game Screen", 350, 350, 30, BLACK);
	player->render();
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
