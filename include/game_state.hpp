#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>

#include "raylib.h"

class GameState {
private:
	int deathCount = 0;
	std::vector<Vector2> corpsePositions = {};

public:
	int getDeathCount() { return deathCount; }
	void incrementDeathCount() { deathCount++; }
	std::vector<Vector2> getCorpsePosition() { return corpsePositions; }
	void addCorpsePosition(Vector2 pos) { corpsePositions.push_back(pos); }
};

extern GameState state;

#endif
