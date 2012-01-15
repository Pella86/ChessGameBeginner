/*
 *  GameEngine.cpp
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 11.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */

#include "GameEngine.h"



bool isStrColOK(std::string answer){
	//recive the format 'a1'
	bool isOK = true;
	if (answer[0] < 'a' or answer[0] > 'h') { //check if column is right
		isOK = false;
	} 
	return isOK;
}

bool isStrRowOK(std::string answer){
	bool isOK = true;
	int cInpDebug = answer[1];
	cInpDebug -= 48; //to map the number between 1 and 8
	if (cInpDebug < 1 or cInpDebug > 8) { //check if row is right
		isOK = false;
	}
	return isOK;
}



std::string HPlayer::selectUnit() const{
	//takes an input fromt the player
	std::string answer;
	bool BADa = true;
	//parse the string:
	do{
		std::cout<< "Input a position:\n in the format (xy) x = column(letter), column y = row(number)"<<std::endl;
		std::getline(std::cin, answer);
		if (answer.length() != 2) { //check if size is right
			std::cout << "The string is too long, try again"<< std::endl;
			BADa = true;
		}
		else if (!isStrColOK(answer)) { //check if column is right
			std::cout<<"The column is not formatted correctly, try again"<<std::endl;
			BADa = true;
		} 
		else if (!isStrRowOK(answer)) { //check if row is right
			std::cout<< "The row is not formatted correctly, try again"<<std::endl;
			BADa = true;
		}
		else {
			//if after all the checks is good return the string
			BADa = false;
		}

	}while (BADa);
	
	return answer;
}

std::string HPlayer::mkMove() const{
	std::string answer;
	bool BADa = true;
	do {
		std::cout<< "Input a movement:\n in the format (xy:xy)\n x = column(letter), column y = row(number): ";

		std::getline(std::cin, answer);
		
		if(answer == "q" ){
			std::cout<< "THE END\n it was a plesure\n goodbye!"<<std::endl;
			exit(0);
		}

		std::stringstream ss;
		ss << answer[0] << answer[1];
		std::string from = ss.str();
		
		ss.str("");
		ss << answer[3] << answer[4];
		std::string to = ss.str();
		
		if (answer.length() != 5) {
			std::cout<< "String is too long or too short"<<std::endl;
			BADa = true;
		}
		else if (!isStrRowOK(from) or !isStrColOK(from)) {
			std::cout<< "from position not formatted correctly, try again"<<std::endl;
			BADa = true;
		}
		else if (!isStrRowOK(to) or !isStrColOK(to)) {
			std::cout<< "to position not formatted correctly, try again"<<std::endl;
			BADa = true;			
		}
		else {
			BADa = false;
		}
	} while (BADa);
	
	return answer;
}

std::string HPlayer::printPlayer(){
	std::stringstream ss;
	std::string colstr;
	if (color == WHITE) {
		colstr = "White";
	}
	else {
		colstr = "Black";
	}

	ss<< "Human player " << colstr;
	return ss.str();
}



std::string CPUPlayer::selectUnit() const{
	std::string a = "a1";
	std::cout<< "I'm in the CPU select unit"<<std::endl;
	return a;
}
std::string CPUPlayer::mkMove() const{
	std::string b = "a1:b1";
	std::cout<< "I'm in the CPU mkMove"<<std::endl;
	return b;
}


std::string CPUPlayer::printPlayer(){
	std::stringstream ss;
	std::string colstr;
	if (color == WHITE) {
		colstr = "White";
	}
	else {
		colstr = "Black";
	}
	
	ss<< "CPU player " << colstr;
	return ss.str();
}

void GEngine::setPlayers(){
	std::string answer;
	bool BADa = true;
	do {
		std::cout<<"player1 is white and is CPU or Human?"<<std::endl;
		std::getline(std::cin, answer);
		if (answer == "h" or answer == "human") {
			p1 = new HPlayer(WHITE);
			BADa = false;
		}
		else if(answer == "pc" or answer == "c" or answer == "cpu"
				or answer == "CPU"){
			p1 = new CPUPlayer(WHITE);
			BADa = false;
		}
		else {
			BADa = true;
		}
	} while (BADa);
	do {
		std::cout<<"player2 is black and is CPU or Human?"<<std::endl;
		std::getline(std::cin, answer);
		if (answer == "h" or answer == "human") {
			p2 = new HPlayer(BLACK);
			BADa = false;
		}
		else if(answer == "pc" or answer == "c" or answer == "cpu"
				or answer == "CPU"){
			p2 = new CPUPlayer(BLACK);
			BADa = false;
		}
		else {
			BADa = true;
		}
	} while (BADa);
	
}


GEngine::GEngine():board(),checkBoard(board){
	checkBoard.printcBoard();
	setPlayers();
}

void GEngine::printBoard(){
	board.printBoard();
}


void GEngine::gameLoop(){
	bool endgame = false;
	while (!endgame) {
		//print the board:
		board.printBoard();
		
		//ask move to p1
		std::string move = "invalid";
		do{
			//check if move is valid
			std::cout<< "Player 1 ";
			move = p1->mkMove();
		}while (!isValidMove(move, p1));
		board.movePiece(move);
		//reset move
		board.printBoard();
		
		//ask move p2
		move = "invalid";
		do {
			std::cout<< "Player 2 ";
			move = p2->mkMove();
		} while (!isValidMove(move, p2));
		board.movePiece(move);
		
		//end turn
		std::cout<< "END TURN\n\n"<<std::endl;
	}
}

bool GEngine::isValidMove(std::string mv, Player* p){
	//mv is already correctly formatted
	//get the from to..
	
	bool isValid = true;
	std::stringstream ss;
	ss << mv[0]<< mv[1];
	std::string from = ss.str();
	
	ss.str("");
	ss<< mv[3]<< mv[4];
	std::string to = ss.str();

	//check if the piece is there
	if (board.getPieceAt(from).getId() == NONE) {
		std::cout<<"Invalid move: Position "<< from << " empty"<<std::endl;
		return isValid = false;
	}
	//check if the piece is the right color
	if (board.getPieceAt(from).getColor() != p->getColor() ) {
		std::cout<<"Invalid move: Picked "<< from <<" piece with wrong color"<<std::endl;
		return isValid = false;
	}
	
	//check if the piece in the to position is not of player color
	if (board.getPieceAt(to).getColor() == p->getColor()) {
		std::cout << "Invalid move: Positon "<< to <<" already occupied by a piece of the same color"<<std::endl;
		return isValid = false;
	}
	//check if piece can move there
	checkBoard.fillcBoard(from);
	if(checkBoard.get(to) == canPASS or checkBoard.get(to) == canEAT){
		/*empty*/
	}
	else{
		std::cout<< "Invalid move for piece: "<< 
			idToStr[board.getPieceAt(from).getId()]<< 
			" at position: " << from <<std::endl;
		checkBoard.printcBoard();
		return isValid = false;
	}
	return isValid = true;
}

void GEngine::printPlayers() const {
	std::cout << p1->printPlayer()<<std::endl;
	std::cout << p2->printPlayer()<<std::endl;
}
