#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "player.hpp"
#include "tile_map.hpp"

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
	Camera2D camera;
	void resolveCollisions();

public:
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;
};

#endif
