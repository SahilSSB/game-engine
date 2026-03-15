#pragma once
#include "raylib.h"
#include "services.hpp"
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

struct TilesetData {
	Texture2D texture;
	int firstID;
	int lastID;
	int columns;
};

class TileMap {
private:
	std::vector<TilesetData> tilesets;
	Texture2D tilesetTex;
	int tileSize = 64;

	int mapWidth = 0;
	int mapHeight = 0;
	std::vector<std::vector<int>> mapData;

public:
	int getPixelWidth() const { return mapWidth * 64; }
	int getPixelHeight() const { return mapHeight * 64; }
	void loadTileset(const char *filepath) { tilesetTex = LoadTexture(filepath); }
	void addTileset(const char *filepath, int firstID, int lastID, float originalTileSize) {
		Texture2D tex = LoadTexture(filepath);
		int cols = tex.width / (int)originalTileSize;
		if (cols == 0)
			cols = 1;
		tilesets.push_back({tex, firstID, lastID, cols});
	}
	void loadMapCSV(const char *filepath) {
		mapData.clear();
		std::ifstream file(filepath);
		if (!file.is_open()) {
			std::cout << "ERROR: Could not load map file: " << filepath << std::endl;
			return;
		}
		std::string line;
		while (std::getline(file, line)) {
			std::vector<int> row;
			std::stringstream ss(line);
			std::string tileValue;
			while (std::getline(ss, tileValue, ',')) {
				row.push_back(std::stoi(tileValue));
			}
			mapData.push_back(row);
		}
		mapHeight = mapData.size();
		if (mapHeight > 0) {
			mapWidth = mapData[0].size();
		}
	}
	void render() {
		if (mapData.empty())
			return;
		float destTileSize = 64.f;
		float originalTileSize = 45.f;
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				int tileID = mapData[y][x];
				if (tileID < 0)
					continue;
				for (auto &ts : tilesets) {
					if (tileID >= ts.firstID && tileID <= ts.lastID) {
						int localID = tileID - ts.firstID;
						int tileX = localID % ts.columns;
						int tileY = localID / ts.columns;
						Rectangle src = {tileX * originalTileSize, tileY * originalTileSize, originalTileSize, originalTileSize};
						Rectangle dest = {(float)x * destTileSize, (float)y * destTileSize, destTileSize, destTileSize};
						DrawTexturePro(ts.texture, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
						break;
					}
				}
			}
		}
	}

	std::vector<Rectangle> getSolidTiles() {
		std::vector<Rectangle> solidRects;
		float destTileSize = 64;
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				int tileID = mapData[y][x];
				bool isSolid = (tileID == 0 || tileID == 7 || tileID == 2 || tileID == 14 || tileID == 4 || tileID == 5 ||
				                tileID == 12 || tileID == 8 || tileID == 10 || tileID == 9 || tileID == 6 || tileID == 3);
				if (isSolid) {
					Rectangle tileHitbox = {(float)x * destTileSize, (float)y * destTileSize, destTileSize, destTileSize};
					solidRects.push_back(tileHitbox);
				}
			}
		}
		return solidRects;
	}

	std::vector<Rectangle> getHazardTiles(int targetID) {
		std::vector<Rectangle> hazardRects;
		float destTileSize = 64.f;

		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				// We check the ID exactly as it appears in the CSV
				if (mapData[y][x] == targetID) {
					Rectangle hazardHitbox = {(float)x * destTileSize, (float)y * destTileSize, destTileSize, destTileSize};
					hazardRects.push_back(hazardHitbox);
				}
			}
		}
		return hazardRects;
	}
};
