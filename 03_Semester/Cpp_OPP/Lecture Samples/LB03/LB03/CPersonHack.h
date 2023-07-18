#pragma once
#include <string>
class CPersonHack {
public:
	std::string name = "Musterfrau";
	unsigned int plz;

	const std::string GetName() const;
	void SetName(const std::string& name) { this->name = name; }
};

