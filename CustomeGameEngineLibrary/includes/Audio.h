#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include <vector>
class Audio
{
public:
	Audio();
	~Audio();

	void PlayAudio(int i);
	void StopAudio();
	void PauseAudio(bool p);
	bool GetPause();
	void LoadMusic(const char* path);
	int GetMusicListLength();
	FMOD::Channel* m_musicChannel;
private:
	FMOD::System* m_fmodSystem;
	std::vector<FMOD::Sound*> songs;

	FMOD::Channel* m_SFXChannel;
	void InitFMOD();
	void ERRCHECK(FMOD_RESULT result);
	//float m_spectrumLeft[SPECTRUM_SIZE];
	//float m_spectrumRight[SPECTRUM_SIZE];
};