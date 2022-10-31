#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void Initialize();
	void Deinitialize();
	
	bool PlacePiece(int column, std::vector<sf::Sprite>& spritePieces, sf::Texture& texture);

	int GetCurrentTurn();
	void ChangeTurn();

	int GetColumnFromMouse(sf::Vector2i mousePosition);

	int Grid[6][7];	// TODO: make private
	bool CanPlace(int column);
	int CheckWinCondition();

private:
	int currentTurn;
};