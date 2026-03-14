#include "../include/entity_manager.hpp"
#include "raylib.h"

#include "../include/game.hpp"
#include "../include/player.hpp"
#include <vector>

void GameScreen::onEnter() {
	Player *p = new Player();
	p->setPosition((Vector2){40, 40});
	Texture2D atlas = assetM.getAsset("default")->getTexture();
  float frameWidth = 64.f;
  float frameHeight = 64.f;
  float sideWalkY = 11.f * frameHeight;
  std::vector<Rectangle> walkFrames;
    for (int i = 0; i < 9; i++) {
        walkFrames.push_back({ (float)i * frameWidth, sideWalkY, frameWidth, frameHeight });
    }
  p->currAnim = p->CreateSpriteAnimation(atlas, 12, walkFrames);
  p->setPlayerAsset(assetM.getAsset("default"));
  entityManager.add(p);
<<<<<<< HEAD
=======
  Texture2D tileMap = assetM.getAsset("tilemap")->getTexture();
  float tileW = 1024;
  float tileH = 1024;
  entityManager.add(tileMap);
>>>>>>> a77e24b (completed player animations)
}

void GameScreen::update(float dt) {
  entityManager.flush();
  entityManager.updateAll(dt);
}

void GameScreen::render() {
	BeginDrawing();
	ClearBackground(BLACK);
	entityManager.renderAll();
  EndDrawing();
}

void GameScreen::onExit() {
  entityManager.clear();
}
