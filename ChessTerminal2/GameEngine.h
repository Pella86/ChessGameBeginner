/*
 *  GameEngine.h
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 11.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *  
 *  This file contains:
 *  The game engine is the structure that takes the input from a player either
 *  CPU or human and handles their move checking if are possible or not.
 *  the rules are created by an external class called ChessMoves.
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <sstream>
#include <string>

#include "PieceMoves.h"

enum PlayerID {pNONE,HUMAN,CPU};

//Player Base class to manage players
//  both players hase the same interface with the GE
//  mkMove, printPlayer, selectUnit(still no support for this function)
//  TODO:
//      members ColorID color; PlayerID pID;
//      getters and setter
class Player{
public:
	virtual ColorID const& getColor() const = 0;
	virtual std::string mkMove() const = 0;
	virtual std::string selectUnit() const = 0;
	virtual std::string printPlayer() =0;
};

//Human Player class
class HPlayer : public Player {
private:
	ColorID color;
	PlayerID pID;
public:
	HPlayer(ColorID col):color(col),pID(HUMAN){}
	HPlayer():color(WHITE),pID(HUMAN){}
	
	ColorID const& getColor() const{return color;}
	
	std::string selectUnit() const;
	std::string mkMove() const;
	std::string printPlayer();
};

//CPU PLayer class
class CPUPlayer : public Player {
private:
	ColorID color;
	PlayerID pID;
public:
	CPUPlayer(ColorID col):color(col),pID(CPU){}
	CPUPlayer():color(WHITE),pID(CPU){}
	
	
	ColorID const& getColor() const{return color;}
	
	std::string selectUnit() const;
	std::string mkMove() const;
	std::string printPlayer();
};

//Game Engine Class:
//  the game engine set the players and handle the moves
class GEngine {
private:
	ChessBoard board; //the real board
	ChessMoves checkBoard; //the board containing the rules
	
    //players
    Player* p1; 
	Player* p2;
    void setPlayers(); //used in the constructor

	MAPidSTRING idToStr;
public:
    //c'tor
	GEngine();
	
	void printBoard();
	void gameLoop();
	bool isValidMove(std::string mv, Player* p);
	void printPlayers() const;
};

#endif
