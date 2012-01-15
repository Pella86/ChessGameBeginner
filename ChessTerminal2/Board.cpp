/*
 *  Board.cpp
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 10.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */

#include "Board.h"

typedef std::pair<int,int> PositionPair;

std::pair<int,int> rcFromStr(std::string str){
#ifdef DEBUG
	if(str.length() != 2){
		PRINTVAR(str);
		std::cerr<< " the string too long "<<std::endl;
		exit(1);
	}
	if(str[0] < 'a' or str[0] > 'h'){
		PRINTVAR(str);
		std::cerr<<"the column is not formatted correctly"<<std::endl;
		exit(1);
	}
	int cInpDebug = str[1];
	cInpDebug -= 48; //ASCII Table map
	if (cInpDebug < 1 or cInpDebug > 8) {
		PRINTVAR(cInpDebug);
		std::cerr<<"the column is not formatted correctly"<<std::endl;
		exit(1);
	}
#endif
	char cInp = str[0];
	int getCol = cInp-'a';
	int getRow = str[1]-1;
	getRow -=  48;
	getRow = 7- getRow; //invert the row because the index are reversed
	std::pair<int, int> p(getRow,getCol);
	return p;
}


std::string strFromRC(int row, int col){
#ifdef DEBUG
	if (row < 0 or row >= 8) {
		PRINTVAR(row);
		std::cerr<< "Row out of range"<<std::endl;
	}
	if (col < 0 or col >= 8) {
		PRINTVAR(col);
		std::cerr<< "Coloumn out of range"<<std::endl;
	}
#endif
	
	//open a stringstream to contain the newly formed string
	std::stringstream ss;
	//map the column to a char
	char cCol = 'a'+col;
	ss<<cCol<<(row);
	return ss.str();
}

MAPidSTRING::MAPidSTRING(){
	//initialize the map with names
	idToStr.insert(std::make_pair(NONE, "NONE"));
	idToStr.insert(std::make_pair(PAWN, "PAWN"));
	idToStr.insert(std::make_pair(KNIGHT, "KNIGHT"));
	idToStr.insert(std::make_pair(BISHOP, "BISHOP"));
	idToStr.insert(std::make_pair(ROOK, "ROOK"));
	idToStr.insert(std::make_pair(KING, "KING"));
	idToStr.insert(std::make_pair(QUEEN, "QUEEN"));
	
	idToOneLetterStr.insert(std::make_pair(NONE, "-"));
	idToOneLetterStr.insert(std::make_pair(PAWN, "P"));
	idToOneLetterStr.insert(std::make_pair(KNIGHT, "k"));
	idToOneLetterStr.insert(std::make_pair(BISHOP, "B"));
	idToOneLetterStr.insert(std::make_pair(ROOK, "R"));
	idToOneLetterStr.insert(std::make_pair(KING, "K"));
	idToOneLetterStr.insert(std::make_pair(QUEEN, "Q"));
	
	idColToStr.insert(std::make_pair(colNONE, "-"));
	idColToStr.insert(std::make_pair(BLACK, "b"));
	idColToStr.insert(std::make_pair(WHITE, "w"));
	
	
}
std::string const& MAPidSTRING::operator[](PiecesID ID){
	//returns the string corresponding to the id
	return idToStr[ID];
}


ChessBoard::ChessBoard(){
	Piece wR1(ROOK,WHITE);
	Piece wR2(ROOK,WHITE);
	Piece wB1(BISHOP,WHITE);
	Piece wB2(BISHOP,WHITE);
	Piece wk1(KNIGHT,WHITE);
	Piece wk2(KNIGHT,WHITE);
	Piece wK(KING,WHITE);
	Piece wQ(QUEEN,WHITE);
	
	putPiece("a1",wR1);
	putPiece("b1",wk1);
	putPiece("c1",wB1);
	putPiece("d1",wQ);
	putPiece("e1",wK);
	putPiece("f1",wB2);
	putPiece("g1",wk2);
	putPiece("h1",wR2);
	
	
	Piece bR1(ROOK,BLACK);
	Piece bR2(ROOK,BLACK);
	Piece bB1(BISHOP,BLACK);
	Piece bB2(BISHOP,BLACK);
	Piece bk1(KNIGHT,BLACK);
	Piece bk2(KNIGHT,BLACK);
	Piece bK(KING,BLACK);
	Piece bQ(QUEEN,BLACK);
	
	putPiece("a8",bR1);
	putPiece("b8",bk1);
	putPiece("c8",bB1);
	putPiece("d8",bQ);
	putPiece("e8",bK);
	putPiece("f8",bB2);
	putPiece("g8",bk2);
	putPiece("h8",bR2);
	
	Piece wP(PAWN,WHITE);
	Piece bP(PAWN,BLACK);
	
	for (int i = 0; i<8; ++i) {
		std::string pos = strFromRC(2,i);
		putPiece(pos, wP);
	}
	for (int i = 0; i<8; ++i) {
		std::string pos = strFromRC(7,i);
		putPiece(pos, bP);
	}
	
}

Piece const& ChessBoard::getPieceAt(std::string pos) const{
	PositionPair p = rcFromStr(pos);
	return board[p.first][p.second];
}

bool ChessBoard::isEmpty(std::string pos){
	
	Piece const& p = getPieceAt(pos);
	if (p.getId() == NONE) {
		return true;
	}
	else {
		return false;
	}

}

void ChessBoard::putPiece(std::string pos, Piece p){
#ifdef DEBUG
if (!isEmpty(pos)) {
	PRINTVAR(pos);
	PRINTVAR(idStr.getOneLetterStr(p.getId()));
	std::cerr<<"The position is already occupied"<<std::endl;
	exit(1);
}
#endif
	PositionPair position = rcFromStr(pos);
	board[position.first][position.second] = p;
}
void ChessBoard::removePiece(std::string pos){
#ifdef DEBUG
	if (isEmpty(pos)) {
		PRINTVAR(pos);
		std::cerr<<"The position is already empty"<<std::endl;
		exit(1);
	}
#endif
	
	PositionPair position = rcFromStr(pos);
	board[position.first][position.second].setId() = NONE;
	board[position.first][position.second].setColor() = colNONE;
}
void ChessBoard::movePiece(std::string fromTo){
	//check if string has the right size
#ifdef DEBUG
	if (fromTo.length() != 5) {
		PRINTVAR(fromTo);
		std::cerr<< "String is too long or too short"<<std::endl;
		exit(1);
	}
#endif
	//split the from to string in two coordinates 
	std::stringstream ss;
	ss<<fromTo[0]<<fromTo[1];
	std::string from = ss.str();
	
	ss.str("");
	ss<<fromTo[3]<<fromTo[4];
	std::string to = ss.str();
	
	//get the piece in the original position
	Piece const& From_Piece = getPieceAt(from);
	
	//check if on the position there is a piece (!= NONE) of the other color
	if (getPieceAt(to).getColor() != getPieceAt(from).getColor() and getPieceAt(to).getId() != NONE) {
		std::cout<< "you eaten a "<<idStr[getPieceAt(to).getId()]<<std::endl;
		removePiece(to); //remove that piece
		putPiece(to, From_Piece); //place the new piece
		removePiece(from);//remove the piece from original position
	}
	else{ //the square is empty
		putPiece(to,From_Piece);
		removePiece(from);
	}
}

rcPair ChessBoard::getRowColAt(std::string pos) const{
	return rcFromStr(pos);
}


void ChessBoard::printBoard() {
	std::cout<<"-|--a-|--b-|--c-|--d-|--e-|--f-|--g-|--h-|"<<std::endl;
	for (int row = 0; row<8; ++row) {
		std::cout<< 8-row <<"|";
		for (int col = 0; col<8; ++col) {
			if ((row %2) == 0 xor (col%2) == 0) {
				std::cout<<"+"<<idStr.getColToStr(board[row][col].getColor())
			    	<<idStr.getOneLetterStr(board[row][col].getId())<<"+|";
			}
			else {
				std::cout<<"-"<<idStr.getColToStr(board[row][col].getColor())
				<<idStr.getOneLetterStr(board[row][col].getId())<<"-|";
			}

			
		}
		std::cout<<std::endl;
	}
}