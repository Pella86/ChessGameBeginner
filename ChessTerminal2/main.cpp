#include <iostream>

#include "Board.h"
#include "GameEngine.h"
#include "PieceMoves.h"


std::string printiPair(std::pair<int,int> const& p){
	std::stringstream ss;
	ss<<p.first<<" "<<p.second<<std::endl;
	return ss.str();
};

int main (int argc, char * const argv[]) {
	GEngine chessGame;
	chessGame.printPlayers();
	chessGame.gameLoop();
	/*

	ChessBoard cBoard;
	cBoard.putPiece("d5",Piece(ROOK,WHITE));
	ChessMoves moves(cBoard);
	
	cBoard.printBoard();
	moves.printcBoard();
	moves.fillcBoard("d5");
	moves.printcBoard();
    */

    return 0;
}
