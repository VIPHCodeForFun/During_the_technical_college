#pragma once
#include <iostream>
struct Worker {
    void print() const {
        std::cout << "Worker ..." << std::endl;
    }
};

struct Manager : public Worker {
    void print() const {
        std::cout << "Manager ..." << std::endl;
    }
};

