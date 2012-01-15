/*
 *  GameEngine.cpp
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 11.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */

#include "GameEngine.h"


//parser for the column 
bool isStrColOK(std::string answer){
	//recive the format 'a1'
	if (answer[0] > 'a' or answer[0] < 'h') {return true;} 
    else{return false;}
}

//parser for the rows
bool isStrRowOK(std::string answer){
	int cInpDebug = answer[1];
	cInpDebug -= 48; //to map the number between 1 and 8
	if (cInpDebug > 1 or cInpDebug < 8) {return true;}
    else{return false;}
}



std::string HPlayer::selectUnit() const{
	//takes an input fromt the player
	std::string answer;
	bool BADa = true; //Bad answer flag
	//parse the string:
	do{
		std::cout<< "Input a position:\n"<<
            "in the format (xy) x = column(letter), column y = row(number)"<<
            std::endl;
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
	bool BADa = true; //bad Answer flag
    //ask to input while the string is not correctly formatted
    //no check for the rules performed here
    //The rules are checked by the GE
    //this is just a parser for the string inputted by the user
	do {
		std::cout<< "Input a movement, in the format (xy:xy)\n x = column(letter), y = row(number): ";

		std::getline(std::cin, answer);
		
		if(answer == "q" ){
			std::cout<< "THE END\n Thank you for playing\n goodbye!"<<std::endl;
			exit(0);
		}

        //get the From position
		std::stringstream ss;
		ss << answer[0] << answer[1];
		std::string from = ss.str();
		
        //get the row position
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
		else {
			BADa = false;
		}
	} while (BADa);
	
	return answer;
}

std::string HPlayer::printPlayer(){
    //print the player
	std::stringstream ss;
	std::string colstr= (color == WHITE)?"White":"Black";

	ss<< "Human player " << colstr;
	return ss.str();
}



std::string CPUPlayer::selectUnit() const{
	//function prototype
    std::cerr<<"CPU Player not defined yet"<<std::endl;
    exit(1);
}
std::string CPUPlayer::mkMove() const{
	//function prototype
    std::cerr<<"CPU Player not defined yet"<<std::endl;
    exit(1);
}


std::string CPUPlayer::printPlayer(){
	std::stringstream ss;
	std::string colstr = (color == WHITE)?"White":"Black";
	
	ss<< "CPU player " << colstr;
	return ss.str();
}



/************
 * GameEngine
 ***********/

void GEngine::setPlayers(){
    //Given:  Nothing
    //Task:   Parse user input for human or CPU
    //Return: Nothing but instanciate two new player
	std::string answer;
	bool BADa = true; //Bad answer flag
    //set Player 1
	do {
		std::cout<<"player1 is white and is CPU or Human? ";
		std::getline(std::cin, answer);
		if (answer == "h" or answer == "human") {
			p1 = new HPlayer(WHITE);
			BADa = false;
		}
		else if(answer == "pc" or answer == "c" or
                answer == "cpu"	or answer == "CPU"){
			p1 = new CPUPlayer(WHITE);
			BADa = false;
		}
		else {
			BADa = true;
		}
	} while (BADa);
	//set Player 2
    do {
		std::cout<<"player2 is black and is CPU or Human? ";
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

//constructor
//  initialize the board
//  pass it as a reference to che checkBoard
GEngine::GEngine():board(),checkBoard(board){
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
		
		//ask move p2
		move = "invalid";
		board.printBoard();
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

    //get the from position
	std::stringstream ss;
	ss << mv[0]<< mv[1];
	std::string from = ss.str();
	
    //get the to position
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
