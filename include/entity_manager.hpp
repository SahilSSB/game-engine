#pragma once

#include "entity.hpp"
#include <vector>

class EntityManager {
private:
	std::vector<Entity *> entities;
	std::vector<Entity *> toRemove;

public:
	void add(Entity *entity) { entities.push_back(entity); }

	void remove(Entity *entity) { toRemove.push_back(entity); }

	void flush() {
		for (Entity *e : toRemove) {
			for (int i = 0; i < entities.size(); i++) {
				if (entities[i] == e) {
					delete entities[i];
					entities.erase(entities.begin() + i);
					break;
				}
			}
		}
		toRemove.clear();
	}

	void updateAll(float dt) {
		for (int i = 0; i < entities.size(); i++) {
			entities[i]->update(dt);
		}
	}

	void renderAll() {
		for (int i = 0; i < entities.size(); i++) {
			entities[i]->render();
		}
	}

	void clear() {
		for (int i = 0; i < entities.size(); i++) {
			delete entities[i];
		}
		entities.clear();
		toRemove.clear();
	}

	int count() { return entities.size(); }
};
