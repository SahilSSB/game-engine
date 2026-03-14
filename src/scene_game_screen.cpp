#include "raylib.h"

#include "../include/corpse.hpp"
#include "../include/player.hpp"
#include "../include/scene.hpp"
#include "../include/services.hpp"

#include <vector>

void GameScreen::onEnter() {
	p = new Player();
	p->setPosition((Vector2){40, 40});
	p->setAsset(Services::assets().getAsset("default"));

	levelMap.loadTileset();

	Corpse *c = new Corpse();
	c->setPosition((Vector2){200, 200});
	Services::manager().addCorpsePosition((Vector2){200, 200});
	c->setAsset(Services::assets().getAsset("dead"));
	Services::entities().add(c);

	camera = {0};
	camera.offset = (Vector2){1200.f / 2.f, 700.f / 2.f};
	camera.rotation = 0.f;
	camera.zoom = 1.f;
}

// void GameScreen::resolveCollisions() {
// 	// for (auto &platform : platforms) {
// 		Rectangle playerHitbox = p->getHitbox();
// 		if (!CheckCollisionRecs(playerHitbox, platform))
// 			continue;

// 		float leftOverlap = (playerHitbox.x + playerHitbox.width) - platform.x;
// 		float rightOverlap = (platform.x + platform.width) - playerHitbox.x;
// 		float topOverlap = (playerHitbox.y + playerHitbox.height) - platform.y;
// 		float bottomOverlap = (platform.y + platform.height) - playerHitbox.y;

// 		float minOverlapX = leftOverlap < rightOverlap ? leftOverlap : rightOverlap;
// 		float minOverlapY = topOverlap < bottomOverlap ? topOverlap : bottomOverlap;

// 		if (minOverlapY < minOverlapX) {
// 			if (topOverlap < bottomOverlap) {
// 				p->setPositionY(platform.y - playerHitbox.height / 2 + 10);
// 				p->setVelocityY(0);
// 				p->setGrounded(true);
// 			} else {
// 				p->setPositionY(platform.y + platform.height + playerHitbox.height / 2 - 10);
// 				p->setVelocityY(0);
// 			}
// 		} else {
// 			if (leftOverlap < rightOverlap) {
// 				p->setPositionX(platform.x - playerHitbox.width / 2);
// 			} else {
// 				p->setPositionX(platform.x + platform.width + playerHitbox.width / 2);
// 			}
// 		}
// 	// }
// }

void GameScreen::update(float dt) {
	Services::entities().flush();
	Services::entities().updateAll(dt);
	p->update(dt);
	std::vector<Rectangle> tileHitbox = levelMap.getSolidTiles();
	for (auto &tile : tileHitbox) {
		Rectangle hb = p->getHitbox();
		if (CheckCollisionRecs(hb, tile)) {
			if (p->getVelocity().y > 0) {
				p->setPositionY(tile.y - (p->getHitbox().height / 2));
				p->setGrounded(true);
				p->setVelocityY(0);
			}
		}
	}
	// resolveCollisions();
}

void GameScreen::render() {
	BeginDrawing();
	ClearBackground(BLACK);
	Texture2D bg = Services::assets().getAsset("background")->getTexture();
	DrawTexture(bg, 0, 0, (Color){255, 255, 255, 100});
	BeginMode2D(camera);
	levelMap.render();
	Services::entities().renderAll();
	p->render();
	EndMode2D();
	EndDrawing();
}

void GameScreen::onExit() {
	Services::entities().clear();
	delete p;
}
