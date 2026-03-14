#ifndef SERVICES_H
#define SERVICES_H

#include "asset_manager.hpp"
#include "audio_manager.hpp"
#include "entity_manager.hpp"
#include "game_manager.hpp"

class Services {
public:
	static AssetManager &assets() { return AssetManager::get(); }
	static AudioManager &audio() { return AudioManager::get(); }
	static EntityManager &entities() { return EntityManager::get(); }
	static GameManager &manager() { return GameManager::get(); }
};

#endif