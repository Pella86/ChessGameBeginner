/*
 *  Piece.h
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 10.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */


#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>

#define DEBUG

#define PRINTVAR(VAR) \
std::cerr << "DEBUG "<< #VAR << ": "<< VAR << " at line: " << __LINE__<< " in file: "<< __FILE__ <<std::endl 

enum PiecesID {
	NONE = 0,
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	KING,
	QUEEN,
};

enum ColorID {
	colNONE = 0,
	BLACK,
	WHITE
};

class Piece {
private:
	PiecesID idPiece;
	ColorID color;
public:
	Piece():idPiece(NONE), color(colNONE){}
	Piece(PiecesID pid, ColorID cid):idPiece(pid),color(cid){}
	
	PiecesID const& getId() const {return idPiece;}
	PiecesID& setId() {return idPiece;}
	
	ColorID const& getColor() const {return color;}
	ColorID & setColor(){return color;}
	
};

#endif