#include <iostream>

#include "Board.h"
#include "GameEngine.h"
#include "PieceMoves.h"

std::string opening_str = "\
##################################\n \
    Chess Game by Pella vr1.0     \n \
##################################\n\n\n";

int main (int argc, char * const argv[]) {
    std::cout<<opening_str<<std::endl;
	GEngine chessGame;
	chessGame.printPlayers();
	chessGame.gameLoop();
    return 0;
}
