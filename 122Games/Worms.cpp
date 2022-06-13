#include "Worms.h"
#include "MathUtils.h"
#include "LedMatrix.h"

Worms::Worms()
	: _player1x(3),
	  _player1y(5),
	  _player2x(8),
	  _player2y(6)
{

}


/* virtual */ void Worms::Start()
{
	DrawCursors();
}


/* virtual */ void Worms::Play()
{


}


void Worms::DrawCursors()
{
	LedMatrix* ledMatrix = _ui->GetMainUi()->GetLedMatrix();
	ledMatrix->SetLed(_player1x, _player1y, 255, 0, 0);
	ledMatrix->SetLed(_player2x, _player2y, 0, 0, 255);
}



/* virtual */ void Worms::HandleButton(int player, Game::EButton button)
{
	switch (button)
	{
	case Game::EButton::Up:
		switch (player)
		{
		case 0:
			_player1y = MathUtils::Trim(_player1y - 1, 0, LedMatrix::MAX_Y - 1);
			break;

		case 1:
			_player2y = MathUtils::Trim(_player2y - 1, 0, LedMatrix::MAX_Y - 1);
			break;
		}
		break;

	case Game::EButton::Right:
		switch (player)
		{
		case 0:
			_player1x = MathUtils::Trim(_player1x + 1, 0, LedMatrix::MAX_X - 1);
			break;

		case 1:
			_player2x = MathUtils::Trim(_player2x + 1, 0, LedMatrix::MAX_X - 1);
			break;
		}
		break;

	case Game::EButton::Down:
		switch (player)
		{
		case 0:
			_player1y = MathUtils::Trim(_player1y + 1, 0, LedMatrix::MAX_Y - 1);
			break;

		case 1:
			_player2y = MathUtils::Trim(_player2y + 1, 0, LedMatrix::MAX_Y - 1);
			break;
		}
		break;

	case Game::EButton::Left:
		switch (player)
		{
		case 0:
			_player1x = MathUtils::Trim(_player1x - 1, 0, LedMatrix::MAX_X - 1);
			break;

		case 1:
			_player2x = MathUtils::Trim(_player2x - 1, 0, LedMatrix::MAX_X - 1);
			break;
		}
		break;

	case Game::EButton::Select:
		break;

	default:
		throw "Illegal case";
		break;
	}

	DrawCursors();
}
