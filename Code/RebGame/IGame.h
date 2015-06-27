#ifndef IGAME_H
#define IGAME_H

#ifdef REBGAME_H
#define REBGAMEAPI __declspec(dllexport)
#else
#define REBGAMEAPI __declspec(dllimport)
#endif

class IGame
{
public:
	virtual void Init() = 0;

	virtual void GameLoop() = 0;

	virtual void Release() = 0;
};

REBGAMEAPI void LoadGame(IGame **IG);

REBGAMEAPI void ReleaseGame(IGame **IG);


#endif