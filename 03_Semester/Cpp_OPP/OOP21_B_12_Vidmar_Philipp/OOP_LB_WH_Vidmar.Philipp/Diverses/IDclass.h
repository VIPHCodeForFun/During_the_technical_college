#pragma once
class IDclass
{
private:
	const int ID;
protected:
public:
	IDclass() : ID{ getUniqueID() } {}

	int getUniqueID()
	{
		static int id = 0;
		id++;
		return id;
	}
};

