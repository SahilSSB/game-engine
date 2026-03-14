#include "raylib.h"

#include <stack>

#include "../include/scene.hpp"
#include "../include/services.hpp"

std::stack<Scene *> sceneStack;

int main() {
	GameScreen gs;

	InitWindow(1200, 700, "Remnants");
	SetTargetFPS(60);
	InitAudioDevice();

	Services::assets().loadAsset("default");
	Services::assets().loadAsset("dead");
	Services::assets().loadAsset("background");
	Services::assets().loadAsset("tilemap");

	sceneStack.push(&gs);
	sceneStack.top()->onEnter();

	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();
		sceneStack.top()->update(deltaTime);
		sceneStack.top()->render();
	}

	sceneStack.top()->onExit();

	CloseAudioDevice();
	CloseWindow();
}
