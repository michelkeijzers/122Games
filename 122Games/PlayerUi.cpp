#include "PlayerUi.h"


int PlayerUi::GetScore()
{
	return _ledSegments.GetValue();
}	


void PlayerUi::SetScore(int score)
{
	_ledSegments.SetValue(score);
}


LedSegments* PlayerUi::GetLedSegments()
{
	return &_ledSegments;
}