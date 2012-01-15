/*
 *  PieceMoves.h
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 11.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */


#ifndef PICEMOVES_H
#define PICEMOVES_H



#include "Board.h"

enum Flags {
	fNONE,
    canEAT,
	canPASS,
	cannotPASS
};




class ChessMoves {
private:
	ChessBoard const& refBoard;
	Flags cBoard[8][8]; //checkboard
public:
	ChessMoves(ChessBoard& ref):refBoard(ref){resetcBoard();};

	Flags const& get(std::string pos) const;	
	void resetcBoard();
	void printcBoard();

	//auxiliari funcions:
	void checkPiece(Piece const& master, int row, int col); 
	void scanRowUp(int row,int col);
	void scanRowDown(int row,int col);
	void scanColLeft(int row,int col);
	void scanColRight(int row,int col);

	void scanDiaUpRi(int row, int col);
	void scanDiaUpLe(int row, int col);
	void scanDiaDoRi(int row, int col);
	void scanDiaDoLe(int row, int col);
	
	void fillcBoard(std::string pos);
	
	void fillcBoardPawn(int row, int col);
	void fillcBoardKing(int row, int col);
	void fillcBoardBishop(int row, int col);
	void fillcBoardQueen(int row, int col);
	void fillcBoardKnight(int row, int col);
	void fillcBoardRook(int row, int col);
};


#endif
