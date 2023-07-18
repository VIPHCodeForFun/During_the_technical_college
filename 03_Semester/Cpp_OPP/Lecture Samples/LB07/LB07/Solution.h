#pragma once
#include <iostream>
struct WorkerSolved {
    virtual void print() const {
        std::cout << "WorkerSolved ..." << std::endl;
    }
};

struct ManagerSolved : public WorkerSolved {
    virtual void print() const override {
        std::cout << "ManagerSolved ..." << std::endl;
    }
};

struct BigBossSolved : public ManagerSolved {
    virtual void print() const final {
        std::cout << "BigBossSolved ..." << std::endl;
    }
};