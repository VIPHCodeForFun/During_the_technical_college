#pragma once
#include <string>
class CPerson {
	std::string name = "Musterfrau";
	unsigned int plz;

public:
	const std::string GetName() const;
	void SetName(const std::string& name) { this->name = name; }
};