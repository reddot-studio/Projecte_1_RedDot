#include"Character.h"

Character::Character() 
{
	for (int i = 0; i < 30; i++)
	{
		Input_Queue[i] = IN_EMPTY;
	}

	FirstInQueue = &Input_Queue[0];
	LastInQueue = &Input_Queue[0];


}

void Character::AddCombo(int NumberOfInputs, inputs EndState,inputs Inp...)
{

	va_list args;
	va_start(args, Inp);

	Special_Move *Combo = new Special_Move();

	Combo->InputsToCompleteMovement[0] = Inp;
	for (int i = 1; i < NumberOfInputs; i++)
	{
		Combo->InputsToCompleteMovement[i] = va_arg(args, inputs);;
	}

	Combo->MovementLenght = NumberOfInputs;
	Combo->Completed_Input = EndState;
	PlayerSpecialMoves[SpecialLenght] = Combo;
	SpecialLenght++;

	va_end(args);

}

void Character::AddInput(inputs Inp)
{

	//Is new Input diferent from last one, check to avoid multiframed input
	if (Input_Queue[TopPosition - 1] != Inp) 
	{
		//Then add input to queue
		//TopPosition is now greater
		//TODO: Check is queue is full to start decreasing inputs
		if (TopPosition + 1 <= 30) 
		{

			Input_Queue[TopPosition] = Inp;
			LastInQueue = &Input_Queue[TopPosition];

			if (TopPosition + 1 == IN_EMPTY) 
			{
				FirstInQueue = &Input_Queue[0];
			}
			else 
			{
				FirstInQueue = &Input_Queue[TopPosition + 1];
			}

			//SDL_Log("%d Num: %d", TopPosition, Input_Queue[TopPosition]);
			TopPosition++;




		}
		else
		{
			TopPosition = 0;
			Input_Queue[TopPosition] = Inp;
			LastInQueue = &Input_Queue[TopPosition];
			TopPosition++;
		}
		
		LOG("\nA");

	}

}

inputs Character::CheckCombos()
{

	int Check = TopPosition;
	int Completed = 0;
	//CheckAllCombos
	for (int i = 0; i < SpecialLenght; i++)
	{
		
		Check = TopPosition;
		Completed = 0;
		//Check All inputs that form the combo
		for (int j = PlayerSpecialMoves[i]->MovementLenght - 1; j >= 0; j--)
		{

			//Next move wont top out the queue
			if (Check - 1 >= 0) 
			{
				if (Input_Queue[Check - 1] == PlayerSpecialMoves[i]->InputsToCompleteMovement[j]) 
				{
					Completed++;
				}

				Check--;
			}
			if(Check - 1 < 0)
			{
				Check = 30;
			}




		}

		if (Completed == PlayerSpecialMoves[i]->MovementLenght) 
		{
			LOG("\n Combo Completed");

			return PlayerSpecialMoves[i]->Completed_Input;
		}

	}

	return IN_EMPTY;

}