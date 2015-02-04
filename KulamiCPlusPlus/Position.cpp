// Author: Amadeus Sanchez

#include "Position.h"

Position::Position()
{
	horizontal = -1, vertical = -1;
}

Position::Position(int _horizontal, int _vertical)
{
	horizontal = _horizontal, vertical = _vertical;
}

bool Position::operator< (const Position& p)const{
	if (horizontal < p.horizontal)
		return true;
	else if (horizontal == p.horizontal){
		if (vertical < p.vertical){
			return true;
		}
	}
	return false;
}
Position::~Position()
{
}
