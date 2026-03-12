#include "../include/asset_manager.hpp"

void AssetManager::loadAsset(std::string assetName) {
	Asset newAsset;
	newAsset.setAssetName(assetName);

	Image img = LoadImage(newAsset.getAssetFilePath().c_str());
	Texture tex = LoadTextureFromImage(img);
	UnloadImage(img);
	newAsset.setTexture(tex);

	assets[assetName] = newAsset;
}

void AssetManager::unloadAsset(std::string assetName) {
	assets[assetName].unloadTexture();
	assets.erase(assetName);
}

Asset *AssetManager::getAsset(std::string assetName) {
	return &assets[assetName];
}
