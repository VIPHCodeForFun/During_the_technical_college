#pragma once
#include <string>
class Server {
	std::string ip;
public:
	Server(std::string ip) {
		this->ip = ip;
	}

	std::string GetIp() { return this->ip; }
	void SetIp(std::string ip) { 
		this->ip = ip; 
	}
};

