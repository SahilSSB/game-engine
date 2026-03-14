#ifndef GAME_H
#define GAME_H

#include <vector>

#include "entity.hpp"
#include "scene.hpp"
#include "entity_manager.hpp"

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
  EntityManager entityManager;
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;
};

class GameOver : public Scene {
public:
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void render() override;
};

#endif
