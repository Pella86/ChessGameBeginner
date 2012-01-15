/*
 *  PieceMoves.cpp
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 11.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */

#include "PieceMoves.h"



Flags const& ChessMoves::get(std::string pos) const {
	rcPair rc = refBoard.getRowColAt(pos);
	int row = rc.first;
	int col = rc.second;
	return cBoard[row][col];
}


void ChessMoves::resetcBoard(){
	for (int i = 0; i<8; ++i) {
		for (int j = 0; j<8; ++j) {
			cBoard[i][j] = fNONE;
		}
	}
	
}

void ChessMoves::printcBoard(){
	std::map<Flags, std::string> flagToStr;
	flagToStr.insert(std::make_pair(fNONE, std::string("N")));
	flagToStr.insert(std::make_pair(canEAT, std::string("E")));
	flagToStr.insert(std::make_pair(canPASS, std::string("P")));
	flagToStr.insert(std::make_pair(cannotPASS, std::string("S")));
	std::cout<<"-|--a-|--b-|--c-|--d-|--e-|--f-|--g-|--h-|"<<std::endl;
	for (int row = 0; row<8; ++row) {
		std::cout<< 8-row <<"|";
		for (int col = 0; col<8; ++col) {
			if ((row %2) == 0 xor (col%2) == 0) {
				std::cout<<row << col <<flagToStr[cBoard[row][col]]<<"+|";
			}
			else {
				std::cout<<row << col <<flagToStr[cBoard[row][col]]<<"-|";
			}
		}
		std::cout<<std::endl;
	}
	
}

//auxiliary funcitons
void ChessMoves::checkPiece(Piece const& master, int row, int col){
	Piece const& actualPiece = refBoard.getPieceAt(row, col);
	//if there is a piece on the line
	//PRINTVAR(row);
	//PRINTVAR(col);
	if (actualPiece.getId() != NONE) {
		//if the piece is of the other color flag canEat
		if (actualPiece.getColor() != master.getColor()) {
			cBoard[row][col] = canEAT; 
		}
		//if the piece is of the same color cannot pass
		else{ 
			cBoard[row][col] = cannotPASS;
		}
		return; //exit upper rowScan
	}
	//if there are no piece on the way can PASS
	else{
		cBoard[row][col] = canPASS;
	}
}

void ChessMoves::scanRowUp(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row, col);
	for(int r = row+1; r< 8; ++r){
		checkPiece(pieceMaster,r,col);
		if(cBoard[r][col] == cannotPASS 
				or cBoard[r][col] == canEAT){break;}
	}

}

void ChessMoves::scanRowDown(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row, col);
	for (int r = row-1; r>=0; --r) {
		checkPiece(pieceMaster,r,col);
		if(cBoard[r][col] == cannotPASS 
				or cBoard[r][col] == canEAT){break;}
	}
}	

//scan column
void ChessMoves::scanColLeft(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row, col);
	for (int c = col-1; c>=0; --c) {
		checkPiece(pieceMaster,row,c);
		if(cBoard[row][c] == cannotPASS 
				or cBoard[row][c] == canEAT){break;}
	}

}

void ChessMoves::scanColRight(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row, col);
	for (int c = col+1; c<=8; ++c) {
		checkPiece(pieceMaster,row,c);
		if(cBoard[row][c] == cannotPASS 
				or cBoard[row][c] == canEAT){break;}
	}
}

//diagonal scan
void ChessMoves::scanDiaUpRi(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row,col);
	//for(int r,c = row+1,col+1; r<8 or c<8; r++,c++){
	int c = col + 1;
	for(int r = row + 1; r < 8; ++r){
		if(col > 8){break;}
		checkPiece(pieceMaster,r,c);
		if(cBoard[r][c] == cannotPASS or cBoard[r][c] == canEAT){break;}
		c++;
	}
}

void ChessMoves::scanDiaUpLe(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row,col);
	//for(int r,c = row+1,col+1; r<8 or c<8; r++,c++){
	int c = col-1;
	for(int r = row + 1; r < 8; ++r){
		if(col <= 0){break;}
		checkPiece(pieceMaster,r,c);
		if(cBoard[r][c] == cannotPASS or cBoard[r][c] == canEAT){break;}
		c--;
	}
}

void ChessMoves::scanDiaDoRi(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row,col);
	//for(int r,c = row+1,col+1; r<8 or c<8; r++,c++){
	int c = col+1;
	for(int r = row - 1; r >= 0; --r){
		if(col > 8){break;}
		checkPiece(pieceMaster,r,c);
		if(cBoard[r][c] == cannotPASS or cBoard[r][c] == canEAT){break;}
		c++;
	}
}

void ChessMoves::scanDiaDoLe(int row, int col){
	Piece const& pieceMaster = refBoard.getPieceAt(row,col);
	//for(int r,c = row+1,col+1; r<8 or c<8; r++,c++){
	int c = col-1;
	for(int r = row - 1; r >= 0; --r){
		if(col <= 0){break;}
		checkPiece(pieceMaster,r,c);
		if(cBoard[r][c] == cannotPASS or cBoard[r][c] == canEAT){break;}
		c--;
	}
}

void ChessMoves::fillcBoardPawn(int row, int col){
    //rewrite from Stackoverflow.com comments
	resetcBoard();

	Piece const& pieceMaster = refBoard.getPieceAt(row,col);
    //to find the coloumns if is black or white
    int const direction = (pieceMaster.getColor() == WHITE)?-1:1; 
    
    //check if can go forward
    Piece const& pieceFW = refBoard.getPieceAt(row + direction, col);
    cBoard[row + direction][col] = (pieceFW.getId() == NONE)? canPASS:cannotPASS;
    //check if can eat
    for(int side = -1; side <= 1; side += 2){
      Piece const& pieceToTake = refBoard.getPieceAt(row+direction, col + side);
      if((pieceToTake.getId() != NONE) && 
          (pieceToTake.getColor() != pieceMaster.getColor())){
          cBoard [row + direction][col + side] = canEAT;
      }
    }

    //check if in initial position, then can make two jump
    int startPosition = (pieceMaster.getColor() == WHITE)? 6 : 1; //2 is row "b" 7 is row "g"
    if( row == startPosition){
        Piece const& piece2Ahead = refBoard.getPieceAt(row + 2*direction, col);
        cBoard[row + 2*direction][col] = canPASS;
    }
    //TODO: insert the en-passant!
}

void ChessMoves::fillcBoardRook(int row,int col){
	//reset cBoard
	resetcBoard();

	//scan through the row 
	scanRowUp(row,col);
	scanRowDown(row,col);
	//column scan
	scanColLeft(row,col);
	scanColRight(row,col);
}

void ChessMoves::fillcBoardBishop(int row, int col){
	//reset cBoard
	resetcBoard();

	scanDiaUpRi(row,col);
	scanDiaUpLe(row,col);
	scanDiaDoRi(row,col);
	scanDiaDoLe(row,col);

}

void ChessMoves::fillcBoardQueen(int row, int col){
	//reset cBoard
	resetcBoard();
	//scan row
	scanRowUp(row,col);
	scanRowDown(row,col);

	//scan col
	scanColLeft(row,col);
	scanColRight(row,col);

	//scan dia
	scanDiaUpRi(row,col);
	scanDiaUpLe(row,col);
	scanDiaDoRi(row,col);
	scanDiaDoLe(row,col);
}

void ChessMoves::fillcBoardKing(int row, int col){
	resetcBoard();
	
	//initialize variable so that they won't go out of boarder
	Piece const& masterPiece = refBoard.getPieceAt(row,col);

	for(int r = row -1; r <= row + 1; ++r){
		if(r > 8) {break;}	
		if(r < 0) {r = 0;}
		for(int c = col-1; c<= col + 1; ++c){
			if(c > 8) {break;}
			if(c < 0) {c = 0;}
			//check all squares a part of the one occupied by the
			//piece
			if(r == row and c == col){
				continue;
			}
			else{
				checkPiece(masterPiece,r,c);
			}
		}
	}

    //arrocco o-o
    //if king is in d1 and has not moved yet (register of moves in Piece?)
    //e1 = row 7 and col 4
    if(row == 7 and col ==4){
        //scan the squares between king and rook
        for(int i = col; i < 7; ++i) {
            Piece const& pieceBetween =  refBoard.getPieceAt(row, i).getId();
            if(pieceBetween.getId() != NONE){
              break;   
            }
        }
    }



}
bool isInBoard(int rORc){
	if(rORc <0 and rORc > 8){return false;}
	else                    {return true; }
}
bool isInBoard(int r, int c){
	if(isInBoard(r) and isInBoard(c)){return true;}
	else{return false;}
}
void ChessMoves::fillcBoardKnight(int row, int col){
	//reset cBoard
	resetcBoard();

	Piece const& masterPiece = refBoard.getPieceAt(row,col);
	//row up 2 and col left right
	if(isInBoard(row+2, col-1)) checkPiece(masterPiece, row+2,col-1);
	if(isInBoard(row+2, col+1)) checkPiece(masterPiece, row+2,col+1);
	//col up 2 and row left right
	if(isInBoard(row+1, col+2)) checkPiece(masterPiece, row+1,col+2);
	if(isInBoard(row-1, col+2)) checkPiece(masterPiece, row-1,col+2);
	//row down 2 and col left right
	if(isInBoard(row-2, col+1)) checkPiece(masterPiece, row-2,col+1);
	if(isInBoard(row-2, col-1)) checkPiece(masterPiece, row-2,col-1);
	//col down 2 and left right
	if(isInBoard(row+1, col-2)) checkPiece(masterPiece, row+1,col-2);
	if(isInBoard(row-1, col-2)) checkPiece(masterPiece, row-1,col-2);
}

void ChessMoves::fillcBoard(std::string pos){
	//refBoard.printBoard();
	
	Piece const& mPiece = refBoard.getPieceAt(pos);
	rcPair rc = refBoard.getRowColAt(pos);
	
	int row = rc.first;
	int col = rc.second;

	if(mPiece.getId() == NONE){
		std::cout<<"Pirla il quadrato e' vuoto"<<std::endl;
		return;
	}
	else{

		PiecesID pID = mPiece.getId();
		switch(pID){
			case ROOK:
				fillcBoardRook(row,col);
				break;
			case KNIGHT:
				fillcBoardKnight(row,col);
				break;
			case QUEEN:
				fillcBoardQueen(row,col);
				break;
			case BISHOP:
				fillcBoardBishop(row,col);
				break;
			case KING:
				fillcBoardKing(row,col);
				break;
			case PAWN:
				fillcBoardPawn(row,col);
				break;
			default:
				break;
		}
	}

}
