/*
 *  Board.h
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 10.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *  
 *
 *
 *  The file contains the board definition:
 *      - the board is defined as a 8 x 8 Piece board
 *      - the board provide function to access to its member from a string or
 *        from the row and column index
 *  The functions rcFromStr and strFromRC are used to help to transform
 *  row and columns in the chess string format
 */

#ifndef BOARD_H
#define BOARD_H

#include <sstream>
#include "Piece.h"

typedef std::pair<int,int> rcPair; //stores the row(first) col(second) index

//Trasnsformation of the table indexes
std::pair<int,int> rcFromStr(std::string str);
std::string strFromRC(int row, int col);


//Maps the id to a string for example PAWN = "PAWN"
//  there are three options:
//      idToStr:          PAWN = "PAWN" , full name
//      idToOneLetterStr: PAWN = "P"    , one letter name
//      idColToStr:       WHITE = "W"   , one letter color
class MAPidSTRING{
private:
	std::map<PiecesID,std::string> idToStr;
	std::map<PiecesID,std::string> idToOneLetterStr;
	std::map<ColorID,std::string> idColToStr;
public:
    //c'tor
	MAPidSTRING();
    
    //getters
	std::string const& operator[](PiecesID ID); //output the full name
	std::string const& getOneLetterStr(PiecesID ID) {return idToOneLetterStr[ID];} //output the one letter code
	std::string const& getColToStr(ColorID ID){return idColToStr[ID];} //outpud the color in one letter code
};

class ChessBoard {
private:
	Piece board[8][8]; //row column
	
	MAPidSTRING idStr;
public:
    //c'tor
	ChessBoard();

    // assignment operator
	ChessBoard const& operator=(ChessBoard const& rhs) const{this->operator=(rhs); return *this;}

    //getter for pieces
	//get the piece from the indexes (7, 0 correspond to "a1")
    Piece const& getPieceAt(int row, int col) const {return board[row][col];} 	
    //get the piece from the string there if the DEBUG flag is active guards the board boundaries
    Piece const& getPieceAt(std::string pos) const; 
    //function to interact with the board
    bool isEmpty(std::string pos);
	void putPiece(std::string pos, Piece p);
	void removePiece(std::string pos);
	void movePiece(std::string fromTo);
	rcPair getRowColAt(std::string pos) const; //same function as rcFromStr
	
    void printBoard(); //should be constant but conflict with the map operator[]
};

#endif
