#pragma once
#include "raylib.h"
#include "services.hpp"
#include <vector>

class TileMap {
private:
	Texture2D tilesetTex;
	int tileSize = 64;

	static const int MAP_WIDTH = 20;
	static const int MAP_HEIGHT = 11;
	int mapData[MAP_HEIGHT][MAP_WIDTH]{
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

public:
	void loadTileset() { tilesetTex = Services::assets().getAsset("tilemap")->getTexture(); }
	void render() {
		float destTileSize = 64.f;
		float originalTileSize = 45.f;
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				int tileID = mapData[y][x];
				if (tileID == 0)
					continue;
				float sourceX = (tileID - 1) * originalTileSize;
				Rectangle src = {sourceX, 0.f, originalTileSize, originalTileSize};
				Rectangle dest = {(float)x * destTileSize, (float)y * destTileSize, destTileSize, destTileSize};
				Vector2 origin = {0.f, 0.f};
				DrawTexturePro(tilesetTex, src, dest, origin, 0.f, WHITE);
			}
		}
	}
	std::vector<Rectangle> getSolidTiles() {
		std::vector<Rectangle> solidRects;
		float destTileSize = 64;
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				if (mapData[y][x] == 1) {
					Rectangle tileHitbox = {(float)x * destTileSize, (float)y * destTileSize, destTileSize, destTileSize};
					solidRects.push_back(tileHitbox);
				}
			}
		}
		return solidRects;
	}
};
