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
	PlaySound(sounds[audioName].getSound());
}

void AudioManager::stopSound(std::string audioName) {
	StopSound(sounds[audioName].getSound());
}
