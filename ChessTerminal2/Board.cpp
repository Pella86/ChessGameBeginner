/*
 *  Board.cpp
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 10.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */

#include "Board.h"

std::pair<int,int> rcFromStr(std::string str){
// Given:  a string contaning a position (for example "a1")
// Task:   transform the string in a pair of int row and col
//         if debug is active check the correct input and the board boundaries
// Return: row and col stored in a std::pair containint two int
#ifdef DEBUG
	if(str.length() != 2){
		PRINTVAR(str);
        std::string shortORlong = (str.length() > 2)?"long":"short";
		std::cerr<< " the string too "<< shortORlong <<std::endl;
		exit(1);
	}
	if(str[0] < 'a' or str[0] > 'h'){
		PRINTVAR(str);
		std::cerr<<"the column is not formatted correctly"<<std::endl;
		exit(1);
	}
    //check if the range of the column is right
	int cInpDebug = str[1]; 
	cInpDebug -= 48; //Map the number from char(e.g.:47) to int(e.g.:1) 
	if (cInpDebug < 1 or cInpDebug > 8) {
		PRINTVAR(cInpDebug);
		std::cerr<<"the column is not formatted correctly"<<std::endl;
		exit(1);
	}
#endif
	//format Row from char to index
    char cInp = str[0]; 
	int getCol = cInp-'a'; //the string is inputted as "cr" where c is a char

	int getRow = str[1]; //better using sstream?
	getRow -=  48;
	getRow = 8- getRow; //invert the row because the index are reversed

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
	putPiece("a1",Piece(ROOK,   WHITE));
	putPiece("b1",Piece(KNIGHT, WHITE));
	putPiece("c1",Piece(BISHOP, WHITE));
	putPiece("d1",Piece(QUEEN,  WHITE));
	putPiece("e1",Piece(KING,   WHITE));
	putPiece("f1",Piece(BISHOP, WHITE));
	putPiece("g1",Piece(KNIGHT, WHITE));
	putPiece("h1",Piece(ROOK,   WHITE));
	
	putPiece("a8",Piece(ROOK,   BLACK));
	putPiece("b8",Piece(KNIGHT, BLACK));
	putPiece("c8",Piece(BISHOP, BLACK));
    putPiece("d8",Piece(QUEEN,  BLACK));
	putPiece("e8",Piece(KING,   BLACK));
	putPiece("f8",Piece(BISHOP, BLACK));
	putPiece("g8",Piece(KNIGHT, BLACK));
	putPiece("h8",Piece(ROOK,   BLACK));
	
	Piece wP(PAWN,WHITE);
	for (int i = 0; i<8; ++i) {
		std::string pos = strFromRC(2,i);
		putPiece(pos, wP);
	}

	Piece bP(PAWN,BLACK);
	for (int i = 0; i<8; ++i) {
		std::string pos = strFromRC(7,i);
		putPiece(pos, bP);
	}
	
}

Piece const& ChessBoard::getPieceAt(std::string pos) const{
    //Given:  the string containing the position
    //Task:   format the string and get the row col pair
    //Return: the row col pair	
    rcPair p = rcFromStr(pos);
	return board[p.first][p.second];
}

bool ChessBoard::isEmpty(std::string pos){
	//Given:  a string containing the position
    //Task:   get the square and signal if there is a piece
    //Return: if idPiece is NONE the square at position is empty
	Piece const& p = getPieceAt(pos);
	if (p.getId() == NONE) {
		return true;
	}
	else {
		return false;
	}

}

void ChessBoard::putPiece(std::string pos, Piece p){
    //Given:  A position and a piece
    //Task:   Put the piece in the board and if debug is active check if it's free
    //Return: nothing, but the board is changed
#ifdef DEBUG
if (!isEmpty(pos)) {
	PRINTVAR(pos);
	PRINTVAR(idStr.getOneLetterStr(p.getId()));
	std::cerr<<"The position is already occupied"<<std::endl;
	exit(1);
}
#endif
	rcPair position = rcFromStr(pos); //get the row column
	board[position.first][position.second] = p; // put the piece
}
void ChessBoard::removePiece(std::string pos){
    //Given: A position
    //Task: delete the piece from the position if the DEBUG is active signals that the position is already empty
    //Return: nothing but change the board
#ifdef DEBUG
	if (isEmpty(pos)) {
		PRINTVAR(pos);
		std::cerr<<"The position is already empty"<<std::endl;
		exit(1);
	}
#endif
	
	rcPair position = rcFromStr(pos);
	board[position.first][position.second].setId() = NONE;
	board[position.first][position.second].setColor() = colNONE;
}
void ChessBoard::movePiece(std::string fromTo){
    //Given:  a string containing 2 position separated by : (eg.: "e2:e4")
    //Task:   move the piece from a square to an other square
    //Return: nothing but change the board

    //check if string has the right size
#ifdef DEBUG
	if (fromTo.length() != 5) {
		PRINTVAR(fromTo);
        std::string shortORlong = (fromTo.length() > 5)?"long":"short";
		std::cerr<< "String is too long or too "<< shortORlong<<std::endl;
		exit(1);
	}
#endif
	//split the from to string in two coordinates 
    //the first position
	std::stringstream ss;
	ss<<fromTo[0]<<fromTo[1];
	std::string from = ss.str();
	
    //the second position
	ss.str("");
	ss<<fromTo[3]<<fromTo[4];
	std::string to = ss.str();
	
	//get the piece in the original position
	Piece const& From_Piece = getPieceAt(from);
	
	//check if on the position there is a piece (!= NONE) of the other color
	if (getPieceAt(to).getColor() != getPieceAt(from).getColor() and getPieceAt(to).getId() != NONE) {
		std::cout<< "you eaten a "<<idStr[getPieceAt(to).getId()]<<std::endl;
		removePiece(to); //remove the eaten piece
		putPiece(to, From_Piece); //place the new piece
		removePiece(from);//remove the piece from original position
	}
	else{ //the square is empty
		putPiece(to,From_Piece);
		removePiece(from);
	}
}

rcPair ChessBoard::getRowColAt(std::string pos) const{
    //convert the string to row col
    //remove the function once everybody is changed to the global string parser
	return rcFromStr(pos);
}


void ChessBoard::printBoard() {
	//first row:
    std::cout<<"-|---a--|---b--|---c--|---d--|---e--|---f--|---g--|---h--|"<<std::endl;
    //   Output format
    //   -|------|
    //rown|--wP--|
    //   -|------|
    for (int row = 0; row<8*3; ++row) {
        //if is the middle row cout the row n
		if(row%3 == 1){ std::cout<< 8-row/3 <<"|";}
        else{std::cout<< "-|";}

		for (int col = 0; col<8; ++col) {
            //get if the square is black(+) or white(-)
            char const* cl = ((row/3 %2) == 0 xor (col%2) == 0)?"+":"-";
            //if is the middle one print "--cI--", c = color, I = ID
            if(row%3 == 1){
			    std::cout<< cl << cl <<
                    idStr.getColToStr(board[row/3][col].getColor()) <<
                    idStr.getOneLetterStr(board[row/3][col].getId())<<
                    cl<<cl<<"|";
            }
            else{
                std::cout<<cl<<cl<<cl<<cl<<cl<<cl<<"|";
            }
		}
		std::cout<<std::endl;
	}
}
