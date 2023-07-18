#pragma once
class IUniqueID
{
public:
	virtual void setID() = 0;

	//protected:
	int uniqueID;
};