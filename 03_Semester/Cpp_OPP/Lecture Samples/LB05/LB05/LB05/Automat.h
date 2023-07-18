#pragma once
#include <iostream>
#include "Server.h"

class Automat
{
	std::string standort;
	std::shared_ptr<Server> server;
public:
	Automat(std::string standort, std::string ip) : standort{ standort }, server(std::make_shared<Server>(ip)) {
		std::cout << "In Ctor mit Argumente" << std::endl;
	}

	Automat(const Automat& copy) {
		this->standort = copy.standort;
		this->server = std::make_shared<Server>(copy.server->GetIp());

		std::cout << "In CCtor" << std::endl;
	}

	Automat(Automat&& move) noexcept {
		this->standort = std::move(move.standort);
		this->server = std::move(move.server);
	}

	~Automat() {
		std::cout << "Zerstoere Objekt" << std::endl;
	}

	std::shared_ptr<Server> GetServer() {
		return this->server;
	}
};

