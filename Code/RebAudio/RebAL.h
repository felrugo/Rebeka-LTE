#ifndef REBAL_H
#define REBAL_H

#include "IAudioDevice.h"
#include <AL/al.h>
#include <AL/alc.h>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "RebAL_SoundPlayer.h"

class RebAL : public IAudioDevice
{
ALCdevice *device;
ALCcontext *context;

ISoundSystem * ss;

public:
	void Init();

	void Update();

	void Release();

	IMusicPlayer * GetMusicPlayer();

	ISoundSystem * GetSoundSystem();

	~RebAL()
	{
	}
};



#endif