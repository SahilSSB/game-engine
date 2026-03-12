#ifndef GAME_H
#define GAME_H

#include <vector>

#include "entity.hpp"
#include "scene.hpp"

class MainMenu : public Scene {
public:
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;
};

class PauseScreen : public Scene {
public:
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;
};

class GameScreen : public Scene {
public:
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;
	std::vector<Entity *> entities;
};

class GameOver : public Scene {
public:
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;
};

#endif
