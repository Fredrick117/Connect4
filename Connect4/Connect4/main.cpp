#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
    using namespace sf;

    RenderWindow window(VideoMode(560, 480), "Connect4");

    Texture t_p1Piece, t_p2Piece;
    Texture t_gameBoard;

    // put this in Game Initialization()?
    t_p1Piece.loadFromFile("img/p1_piece.png");
    t_p2Piece.loadFromFile("img/p2_piece.png");
    t_gameBoard.loadFromFile("img/gameboard.png");

    /*Sprite s_p1Piece(t_p1Piece);
    Sprite s_p2Piece(t_p2Piece);*/

    Sprite s_gameBoard(t_gameBoard);

    Game* game = new Game();

    std::vector<Sprite> pieceSprites;
    
    while (window.isOpen())
    {
        // TODO: waitEvent?
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {

                    int column = game->GetColumnFromMouse(Mouse::getPosition(window));

                    bool placedSuccessfully = false;

                    if (game->GetCurrentTurn() == 1 && game->CanPlace(column))
                    {
                        placedSuccessfully = game->PlacePiece(column, pieceSprites, t_p1Piece);
                    }
                    else if (game->GetCurrentTurn() == 2 && game->CanPlace(column))
                    {
                        placedSuccessfully = game->PlacePiece(column, pieceSprites, t_p2Piece);
                    }

                    //if (game->CheckWinCondition())
                    //{
                    //    // TODO: display text saying "you won!" instead of immediately quitting
                    //    window.close();
                    //}

                    int winStatus = game->CheckWinCondition();
                    printf("Win status: %i", winStatus);

                    if (placedSuccessfully)
                        game->ChangeTurn();

                }
            }
        }

        window.clear();
        window.draw(s_gameBoard);
        for (size_t i = 0; i < pieceSprites.size(); i++)
        {
            window.draw(pieceSprites[i]);
        }
        window.display();
    }

    delete game;

    return 0;
}