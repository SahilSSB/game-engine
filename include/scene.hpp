#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "player.hpp"
#include "tile_map.hpp"
#include "corpse.hpp"

class Scene {
public:
	virtual void onEnter() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void onExit() = 0;
	virtual ~Scene() {}
};

class GameScreen : public Scene {
private:
	Player *p;
	TileMap levelMap;
  TileMap layer1;
  TileMap layer2;
	Camera2D camera;
  std::vector<Corpse*> corpses;
  bool corpseSpawned = false;
	void resolveCollisions();
  float fadeAlpha = 0.f;
  bool isFading = false;
  float fadeDuration = 2.0f;



public:
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;

  Vector2 respawnPoint = {200, 200};  
  bool isRespawning = false;
};

#endif
