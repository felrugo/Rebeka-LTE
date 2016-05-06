/*Audio interface*/
#ifndef IAUDIODEVICE_H
#define IAUDIODEVICE_H

#ifdef REBAL_H
#define REBAUDIOAPI __declspec(dllexport)
#else
#define REBAUDIOAPI __declspec(dllimport)
#endif




#include <windows.h> 
#include <string>
#include <vector>

class ISoundSource
{
};



class IMusicPlayer
{
public:
	virtual void Init() = 0;

	virtual void Release() = 0;

	virtual void Play() = 0;

	virtual bool SetSource(std::string file) = 0;

	virtual bool SetSource(UINT ID) = 0;

	virtual void Pause() = 0;

	virtual void Stop() = 0;

	virtual void SetVolume(float volume) = 0;

	virtual bool IsPlaying() = 0;

	virtual ~IMusicPlayer() {}
};


class ISoundSystem
{
public:
	virtual void Test() = 0;
	virtual void Update() {}
};


class IAudioDevice
{
public:
	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Release() = 0;

	virtual IMusicPlayer * GetMusicPlayer() = 0;

	virtual ISoundSystem * GetSoundSystem() = 0;

};


//For AudioSystem

REBAUDIOAPI void CreateAudioDevice(IAudioDevice ** IAD);

REBAUDIOAPI void ReleaseAudioDevice(IAudioDevice ** IAD);

#endif