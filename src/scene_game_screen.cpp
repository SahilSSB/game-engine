#include "raylib.h"

#include "../include/corpse.hpp"
#include "../include/player.hpp"
#include "../include/scene.hpp"
#include "../include/services.hpp"

#include <vector>

void GameScreen::onEnter() {
	p = new Player();
	p->setPosition((Vector2){200, 200});
	p->setAsset(Services::assets().getAsset("default"));

  float tilesize = 45.f;
  
  layer1.addTileset("assets/sprites/tilemap.png", 0, 0, tilesize);
  layer1.addTileset("assets/sprites/spikes.png", 7, 7, tilesize);
  layer1.addTileset("assets/sprites/float1.png", 2, 2, tilesize);
  layer1.addTileset("assets/sprites/float2.png", 14, 14, tilesize);
  layer1.addTileset("assets/sprites/float3.png", 4, 4, tilesize);
  layer1.addTileset("assets/sprites/float4.png", 5, 5, tilesize);
  layer1.addTileset("assets/sprites/rightWall.png", 12, 12, tilesize);
  layer1.loadMapCSV("assets/sprites/hackathon_Tile Layer 1.csv");
  
  layer2.addTileset("assets/sprites/spikes.png", 7, 7, tilesize);
  layer2.addTileset("assets/sprites/tilemap.png", 0, 0, tilesize);
  layer2.addTileset("assets/sprites/leftWall.png", 6, 6, tilesize);
  layer2.addTileset("assets/sprites/corner.png", 8, 8, tilesize);
  layer2.addTileset("assets/sprites/mid1.png", 10, 10, tilesize);
  layer2.addTileset("assets/sprites/mid2.png", 11, 11, tilesize);
  layer2.addTileset("assets/sprites/mid.png", 9, 9, tilesize);
  layer2.loadMapCSV("assets/sprites/hackathon_Tile Layer 2.csv");

	/*Corpse *c = new Corpse();
	c->setPosition((Vector2){200, 200});
	Services::manager().addCorpsePosition((Vector2){200, 200});
	c->setAsset(Services::assets().getAsset("dead"));
	Services::entities().add(c);*/

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
  p->tickIFrames(dt);
  p->setGrounded(false);

  if (p->checkDead() && !isFading) {
        isFading = true;
        Corpse* c = new Corpse();
        c->setPosition(p->getPosition());
        c->setAsset(Services::assets().getAsset("dead"));
        Services::entities().add(c);
        corpses.push_back(c);
  }

	std::vector<Rectangle> layer1Hitboxes = layer1.getSolidTiles();
  std::vector<Rectangle> layer2Hitboxes = layer2.getSolidTiles();
  std::vector<Rectangle> allHitboxes = layer1Hitboxes;
  allHitboxes.insert(allHitboxes.end(), layer2Hitboxes.begin(), layer2Hitboxes.end());

	for (auto &tile : allHitboxes) {
		Rectangle hb = p->getHitbox();
		if (CheckCollisionRecs(hb, tile)) {
			if (p->getVelocity().y > 0) {
				p->setPositionY(tile.y - (p->getHitbox().height / 2));
				p->setGrounded(true);
				p->setVelocityY(0);
			}
		}
  }
  std::vector<Rectangle> spikesL1 = layer1.getHazardTiles(7);
  std::vector<Rectangle> spikesL2 = layer2.getHazardTiles(7);
  std::vector<Rectangle> allSpikes = spikesL1;
  allSpikes.insert(allSpikes.end(), spikesL2.begin(), spikesL2.end());
  for (auto &spike : allSpikes) {
      if (CheckCollisionRecs(p->getHitbox(), spike)) {
        p->takeDamage(10); 
        p->setVelocityY(-400); 
        if (p->getPosition().x < (spike.x + 32)) p->setVelocityX(-300);
        else p->setVelocityX(300);
        break;         
        }
    }

  float mapWidthPx = (float)layer2.getPixelWidth();
  float mapHeightPx = (float)layer2.getPixelHeight();
	// resolveCollisions();
  camera.target = (Vector2){ 
        p->getPosition().x + (p->getHitbox().width / 2.0f), 
        p->getPosition().y
  };
  float minX = camera.offset.x;
  float maxX = mapWidthPx - (GetScreenWidth() - camera.offset.x);
  float minY = camera.offset.y;
  float maxY = mapHeightPx - (GetScreenHeight() - camera.offset.y);

  if (camera.target.x < minX) camera.target.x = minX;
  if (camera.target.x > maxX) camera.target.x = maxX;
  if (camera.target.y < minY) camera.target.y = minY;
  if (camera.target.y > maxY) camera.target.y = maxY;

  p->tickShake(dt);

  if (p->isShaking()) {
    float t = p->getShakeTimer();
    float magnitude = 8.f * (t / 0.4f);  // fades out over time
    camera.offset.x = (1200.f / 2.f) + (float)(rand() % (int)(magnitude * 2) - (int)magnitude);
    camera.offset.y = (700.f / 2.f)  + (float)(rand() % (int)(magnitude * 2) - (int)magnitude);
  } 
  else {
    camera.offset = {1200.f / 2.f, 700.f / 2.f};  // reset
  }
  if (p->checkDead()) {
    isFading = true;
  }
  if (isFading) {
    if (!isRespawning) {
        fadeAlpha += (255.f / fadeDuration) * dt;
        if (fadeAlpha >= 255.f) {
            fadeAlpha = 255.f;
            isRespawning = true;       
            p->reset();
            p->setPosition(respawnPoint);
        }
    } else {
        fadeAlpha -= (255.f / fadeDuration) * dt;
        if (fadeAlpha <= 0.f) {
            fadeAlpha = 0.f;
            isFading = false;
            isRespawning = false;
        }
    }
  }
  for (auto& corpse : corpses) {
        Rectangle ch = corpse->getHitbox();
        Rectangle ph = p->getHitbox();
        if (CheckCollisionRecs(ph, ch)) {
            if (p->getVelocity().y > 0) {
                p->setPositionY(ch.y - (ph.height / 2));
                p->setGrounded(true);
                p->setVelocityY(0);
            }
        }
    }
}


void GameScreen::render() {
	BeginDrawing();
	ClearBackground(BLACK);
	Texture2D bg = Services::assets().getAsset("background")->getTexture();
	DrawTexture(bg, 0, 0, (Color){255, 255, 255, 100});
	BeginMode2D(camera);
	levelMap.render();
  layer2.render();
  layer1.render();
	Services::entities().renderAll();
	p->render();
	EndMode2D();

  if (p->isShaking()) {
    float alpha = (p->getShakeTimer() / 0.4f) * 180.f;   
    Color vignetteColor = {145, 68, 68, (unsigned char)alpha};

    DrawRectangleGradientH(0, 0, 300, 700, vignetteColor, {0,0,0,0});                      
    DrawRectangleGradientH(900, 0, 300, 700, {0,0,0,0}, vignetteColor);                   
    DrawRectangleGradientV(0, 0, 1200, 250, vignetteColor, {0,0,0,0});                   
    DrawRectangleGradientV(0, 450, 1200, 250, {0,0,0,0}, vignetteColor);                  
}

  DrawRectangle(20, 20, 200, 20, BLACK);
  float healthWidth = (float)p->getHealth() / 100.0f * 200.0f;
  DrawRectangle(20, 20, (int)healthWidth, 20, GREEN);
  DrawText(TextFormat("HP: %i", p->getHealth()), 230, 20, 20, WHITE);

  if (isFading) {
    DrawRectangle(0, 0, 1200, 700, {0, 0, 0, (unsigned char)fadeAlpha});
  }
	EndDrawing();
}

void GameScreen::onExit() {
	Services::entities().clear();
  corpses.clear();
	delete p;
}
