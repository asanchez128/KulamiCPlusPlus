// Author: Amadeus Sanchez

#include "Marble.h"

Marble::Marble()
{
	color = -1;
}

Marble::Marble(int _h, int _v){
	marblePosition.horizontal = _h; marblePosition.vertical = _v;
	color = -1;
}

Marble::~Marble()
{
}
