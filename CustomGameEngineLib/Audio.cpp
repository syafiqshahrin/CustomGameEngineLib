#include <iostream>
#include "Audio.h"

Audio::Audio()
{
	InitFMOD();
}
Audio::~Audio()
{
	
}
void Audio::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}
void Audio::InitFMOD()
{
	FMOD_RESULT       result;
	unsigned int      version;

	result = FMOD::System_Create(&m_fmodSystem);
	ERRCHECK(result);

	result = m_fmodSystem->getVersion(&version);
	ERRCHECK(result);

	if (version < FMOD_VERSION)
		printf("FMOD Error!  You are using an old version of FMOD.", version, FMOD_VERSION);

	//initialize fmod system
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
}

void Audio::PauseAudio(bool p)
{
	m_musicChannel->setPaused(p);
}

bool Audio::GetPause()
{
	bool pause = false;
	return (m_musicChannel->getPaused(&pause));
}

void Audio::LoadMusic(const char* path)
{
	
	FMOD_RESULT result;
	songs.push_back(nullptr);
	//load and set up music
	result = m_fmodSystem->createStream(path, FMOD_SOFTWARE, 0, &(songs.back()));
	ERRCHECK(result);
	//result = m_fmodSystem->createStream("../media/How You Like That.mp3", FMOD_SOFTWARE, 0, &songs[1]);
}

int Audio::GetMusicListLength()
{

	return songs.size();
}

void Audio::PlayAudio(int i)
{
	FMOD_RESULT result;
	result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, songs[i], false, &m_musicChannel);
	ERRCHECK(result);
}

void Audio::StopAudio()
{
	m_musicChannel->stop();
}


