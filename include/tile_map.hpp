#pragma once
#include "raylib.h"

class TileMap {
  private:
    Texture2D TileMap;
    int tileSize = 64;

    static const int MAP_WIDTH = 10;
    static const int MAP_HEIGHT = 8;
    int mapData[MAP_HEIGHT][MAP_WIDTH] {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    public:
    void loadTileset(const char* filepath) {
        TileMap = LoadTexture(filepath);
    }

    void render() {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                int tileID = mapData[y][x];
                
                if (tileID == 0) continue;
                Vector2 destPosition = { (float)(x * tileSize), (float)(y * tileSize) };
                
                int sourceX = (tileID - 1) * tileSize; 
                Rectangle src = { (float)sourceX, 0.0f, (float)tileSize, (float)tileSize };
                
                DrawTextureRec(TileMap, src, destPosition, WHITE);
            }
        }
    }
};
