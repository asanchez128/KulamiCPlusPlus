#include "Move.h"


Move::Move()
{
}

Move::Move(Position _position, int _tileNumber, int _color)
{
	position = _position;
	tileNumber = _tileNumber;
	color = _color;
}



Move::~Move()
{
}
