#include "raylib.h"

#include <stack>

#include "../include/asset_manager.hpp"
#include "../include/audio_manager.hpp"
#include "../include/game.hpp"
#include "../include/game_state.hpp"
#include "../include/scene.hpp"

AudioManager audioM;
AssetManager assetM;
GameState state;

std::stack<Scene *> sceneStack;

int main() {
	MainMenu mm;
	GameScreen gs;
	GameOver go;
	PauseScreen ps;

	InitWindow(1200, 700, "Game engine RAAAHHHHH");
	SetTargetFPS(60);
	InitAudioDevice();

	assetM.loadAsset("knight-nobg");
	assetM.loadAsset("test2");

	sceneStack.push(&mm);
	sceneStack.top()->onEnter();

	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();
		if (IsKeyPressed(KEY_ONE)) {
			if (sceneStack.top() != &mm) {
				sceneStack.top()->onExit();
				sceneStack.pop();
				sceneStack.push(&mm);
				sceneStack.top()->onEnter();
			}
		} else if (IsKeyPressed(KEY_TWO)) {
			if (sceneStack.top() != &gs) {
				sceneStack.top()->onExit();
				sceneStack.pop();
				sceneStack.push(&gs);
				sceneStack.top()->onEnter();
			}
		} else if (IsKeyPressed(KEY_THREE)) {
			if (sceneStack.top() != &go) {
				sceneStack.top()->onExit();
				sceneStack.pop();
				sceneStack.push(&go);
				sceneStack.top()->onEnter();
			}
		} else if (IsKeyPressed(KEY_FOUR)) {
			if (sceneStack.top() != &ps) {
				sceneStack.top()->onExit();
				sceneStack.pop();
				sceneStack.push(&ps);
				sceneStack.top()->onEnter();
			}
		}

		sceneStack.top()->update(deltaTime);
		sceneStack.top()->render();
	}

	sceneStack.top()->onExit();

	CloseAudioDevice();
	CloseWindow();
}
