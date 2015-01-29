
#pragma once
class Position
{
public:
	int vertical, horizontal;
	Position();
	Position(int, int);
	~Position();
	bool operator<(const Position&) const;
};

