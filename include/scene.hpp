#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	virtual void onEnter() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void onExit() = 0;
	virtual ~Scene() {}
};

#endif
