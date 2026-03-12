#include "raylib.h"

#include "../include/game.hpp"

void MainMenu::onEnter() {}
void MainMenu::onExit() {}
void PauseScreen::onEnter() {}
void PauseScreen::onExit() {}
void GameOver::onEnter() {}
void GameOver::onExit() {}

void MainMenu::update(float dt) {}
void PauseScreen::update(float dt) {}
void GameOver::update(float dt) {}

void MainMenu::render() {
	BeginDrawing();
	ClearBackground(GRAY);
	DrawText("Main Menu", 350, 350, 30, WHITE);
	EndDrawing();
}

void PauseScreen::render() {
	BeginDrawing();
	ClearBackground(WHITE);
	DrawText("Pause Screen", 350, 350, 30, BLACK);
	EndDrawing();
}

void GameOver::render() {
	BeginDrawing();
	ClearBackground(GOLD);
	DrawText("Game Over", 350, 350, 30, BLACK);
	EndDrawing();
}
