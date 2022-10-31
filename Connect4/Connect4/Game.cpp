#include "Game.h"
#include <iostream>

Game::Game()
{
	Initialize();
}

Game::~Game()
{
	Deinitialize();
}

void Game::Initialize()
{
	currentTurn = 1;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Grid[i][j] = 0;
		}
	}
}

void Game::Deinitialize()
{

}

bool Game::PlacePiece(int column, std::vector<sf::Sprite>& pieceSprites, sf::Texture& texture)
{
	for (int i = 5; i >= 0; i--)
	{
		if (Grid[i][column] == 0)
		{
			Grid[i][column] = GetCurrentTurn();
			sf::Sprite s(texture);
			//std::cout << "position set to: " << c.col << ", " << i << std::endl;
			s.setPosition(column * 80.f, i * 80.f);
			pieceSprites.push_back(s);

			return true;
		}
	}

	return false;
}

int Game::GetCurrentTurn()
{
	return currentTurn;
}

void Game::ChangeTurn()
{
	if (currentTurn == 1)
		currentTurn = 2;
	else if (currentTurn == 2)
		currentTurn = 1;
}

int Game::GetColumnFromMouse(sf::Vector2i mousePosition)
{
	return mousePosition.x / 80;
}

bool Game::CanPlace(int column)
{
	for (int i = 0; i < 6; i++)
	{
		//std::cout << "checking (" << i << ", " << column << ")" << std::endl;
		if (Grid[i][column] == 0)
			return true;
	}

	return false;
}

int Game::CheckWinCondition()
{
	// Check vertical
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int currentPiece = Grid[j][i];
			if (Grid[j][i] != 0)
			{
				if (Grid[j + 1][i] == currentPiece
					&& Grid[j + 2][i] == currentPiece
					&& Grid[j + 3][i] == currentPiece)
				{
					return currentPiece;
				}
			}
		}
	}

	// Check horizontal
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int currentPiece = Grid[i][j];
			if (Grid[i][j] != 0)
			{
				if (Grid[i][j + 1] == currentPiece
					&& Grid[i][j + 2] == currentPiece
					&& Grid[i][j + 3] == currentPiece)
				{
					return currentPiece;
				}
			}
		}
	}

	// Left diagonal
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int currentPiece = Grid[i][j];
			if (Grid[i][j] != 0)
			{
				if (Grid[i + 1][j + 1] == currentPiece
					&& Grid[i + 2][j + 2] == currentPiece
					&& Grid[i + 3][j + 3] == currentPiece)
				{
					return currentPiece;
				}
			}
		}
	}

	// Right diagonal
	for (int i = 0; i < 3; i++)
	{
		for (int j = 3; j < 7; j++)
		{
			int currentPiece = Grid[i][j];
			if (Grid[i][j] != 0)
			{
				if (Grid[i + 1][j - 1] == currentPiece
					&& Grid[i + 2][j - 2] == currentPiece
					&& Grid[i + 3][j - 3] == currentPiece)
				{
					return currentPiece;
				}
			}
		}
	}

	return 0;	// No winner
}
