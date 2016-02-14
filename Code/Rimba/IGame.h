#ifndef IGAME_H
#define IGAME_H


class IGame
{
public:
	virtual void Init() = 0;

	virtual void GameLoop() = 0;

	virtual void Release() = 0;
};


#endif