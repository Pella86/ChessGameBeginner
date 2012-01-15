/*
 *  GameEngine.h
 *  ChessTerminal2
 *
 *  Created by Mauro Pellanda on 11.01.12.
 *  Copyright 2012 ETH. All rights reserved.
 *
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <sstream>
#include <string>

#include "PieceMoves.h"

enum PlayerID {
	pNONE,
	HUMAN,
	CPU
};


class Player{
public:
	virtual ColorID const& getColor() const = 0;
	virtual std::string mkMove() const = 0;
	virtual std::string selectUnit() const = 0;
	virtual std::string printPlayer() =0;
};


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

class GEngine {
private:
	ChessBoard board;
	ChessMoves checkBoard;
	Player* p1;
	Player* p2;
	void setPlayers();

	MAPidSTRING idToStr;
public:
	GEngine();
	
	void printBoard();
	void gameLoop();
	bool isValidMove(std::string mv, Player* p);
	void printPlayers() const;
};

#endif
