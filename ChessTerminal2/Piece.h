/*
 *  Piece.h
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 10.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 *  The file contains the Piece definition and some debugging functions:
 *      The piece has 2 proprieties:
 *          id
 *          color
 *      both proprieties has an appropriate ENUM that describes the possibility
 */


#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <map>
#include <string>

#define DEBUG

//the variable will be printed to the console as varname:var, line, file
#define PRINTVAR(VAR) \
std::cerr << "DEBUG "<< #VAR << ": "<< VAR << " at line: " << __LINE__<< " in file: "<< __FILE__ <<std::endl 

enum PiecesID {NONE = 0, PAWN, KNIGHT, BISHOP, ROOK, KING, QUEEN};

enum ColorID {colNONE = 0, BLACK, WHITE};

class Piece {
private:
	PiecesID idPiece;
	ColorID color;
public:
    //constructors
	Piece():idPiece(NONE), color(colNONE){}
	Piece(PiecesID pid, ColorID cid):idPiece(pid),color(cid){}
	
    //setter and getter
	PiecesID const& getId() const {return idPiece;}
	PiecesID& setId() {return idPiece;}
	
	ColorID const& getColor() const {return color;}
	ColorID & setColor(){return color;}
};

#endif //end PIECE_H
