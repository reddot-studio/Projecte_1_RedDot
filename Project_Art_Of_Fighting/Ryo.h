#ifndef __RYO_H__
#define __RYO_H__

#include "Character.h"

struct SDL_Texture;

class Ryo : public Character
{
public:
	Ryo(int player);
	~Ryo();
	bool Start() override;
	bool CleanUp() override;

	//Special Move Settings
	int SpecialLenght = 0;
	Special_Move *PlayerSpecialMoves[20];
	inputs Input_Queue[30];
	inputs *FirstInQueue = nullptr;
	inputs *LastInQueue = nullptr;
	int TopPosition = 0;
	int BottomPosition = 0;
	virtual void AddInput(inputs);
	virtual inputs CheckCombos();
	virtual void AddCombo(int NumberOfInputs, inputs EndState, inputs Inp...);
};

#endif // !__RYO_H__
