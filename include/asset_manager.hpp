#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string>
#include <unordered_map>

#include "raylib.h"

class Asset {
private:
	std::string assetName;
	std::string filePath;
	Texture tex;

public:
	std::string getAssetName() { return assetName; }
	void setAssetName(std::string name) {
		assetName = name;
		filePath = "assets/sprites/" + name + ".png";
	}
	std::string getAssetFilePath() { return filePath; }
	Texture getTexture() { return tex; }
	void setTexture(Texture newtex) { tex = newtex; }
	void unloadTexture() { UnloadTexture(tex); }
};

class AssetManager {
private:
	std::unordered_map<std::string, Asset> assets;

public:
	void loadAsset(std::string assetName);
	void unloadAsset(std::string assetName);
	Asset *getAsset(std::string assetName);
};

extern AssetManager assetM;

#endif
