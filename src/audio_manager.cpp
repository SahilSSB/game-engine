#include "../include/audio_manager.hpp"

void AudioManager::loadSound(std::string audioName) {
	Audio newAudio;
	newAudio.setAudioName(audioName);

	Sound sound = LoadSound(newAudio.getAudioFilePath().c_str());
	newAudio.setSound(sound);

	sounds[audioName] = newAudio;
}

void AudioManager::unloadSound(std::string audioName) {
	sounds[audioName].unloadSound();
	sounds.erase(audioName);
}

void AudioManager::playSound(std::string audioName) {
	auto it = sounds.find(audioName);
	if (it == sounds.end()) return;
	PlaySound((it->second).getSound());
}

void AudioManager::stopSound(std::string audioName) {
	auto it = sounds.find(audioName);
	if (it == sounds.end()) return;
	StopSound((it->second).getSound());
}
