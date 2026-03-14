#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>

#include "raylib.h"

class GameManager {
private:
	int deathCount = 0;
	std::vector<Vector2> corpsePositions = {};

public:
	static GameManager &get() {
		static GameManager gameM;
		return gameM;
	}
	int getDeathCount() { return deathCount; }
	void incrementDeathCount() { deathCount++; }
	std::vector<Vector2> getCorpsePosition() { return corpsePositions; }
	void addCorpsePosition(Vector2 pos) { corpsePositions.push_back(pos); }
};

#endif
