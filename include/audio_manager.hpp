#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <unordered_map>

#include "raylib.h"

class Audio {
private:
	std::string audioName;
	std::string filePath;
	Sound sound;

public:
	std::string getAudioName() { return audioName; }
	void setAudioName(std::string name) {
		audioName = name;
		filePath = "assets/sound/" + name + ".wav";
	}
	std::string getAudioFilePath() { return filePath; }
	Sound getSound() { return sound; }
	void setSound(Sound s) { sound = s; }
	void unloadSound() { UnloadSound(sound); }
};

class AudioManager {
private:
	std::unordered_map<std::string, Audio> sounds;

public:
	void loadSound(std::string audioName);
	void unloadSound(std::string audioName);
	void playSound(std::string audioName);
	void stopSound(std::string audioName);
};

extern AudioManager audioM;

#endif
