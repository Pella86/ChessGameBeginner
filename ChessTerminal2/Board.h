/*
 *  Board.h
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 10.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include <sstream>
#include "Piece.h"

typedef std::pair<int,int> rcPair;

std::pair<int,int> rcFromStr(std::string str);
std::string strFromRC(int row, int col);


class MAPidSTRING{
private:
	std::map<PiecesID,std::string> idToStr;
	std::map<PiecesID,std::string> idToOneLetterStr;
	std::map<ColorID,std::string> idColToStr;
public:
	MAPidSTRING();
	std::string const& operator[](PiecesID ID);
	std::string const& getOneLetterStr(PiecesID ID) {return idToOneLetterStr[ID];}
	std::string const& getColToStr(ColorID ID){return idColToStr[ID];}
};

class ChessBoard {
private:
	Piece board[8][8]; //row column
	
	MAPidSTRING idStr;
public:
	ChessBoard();

	ChessBoard const& operator=(ChessBoard const& rhs) const{this->operator=(rhs); return *this;}
	Piece const& getPieceAt(int row, int col) const {return board[row][col];}
	bool isEmpty(std::string pos);
	void putPiece(std::string pos, Piece p);
	void removePiece(std::string pos);
	void movePiece(std::string fromTo);
	Piece const& getPieceAt(std::string pos) const;
	rcPair getRowColAt(std::string pos) const;
	void printBoard();
};

#endif
