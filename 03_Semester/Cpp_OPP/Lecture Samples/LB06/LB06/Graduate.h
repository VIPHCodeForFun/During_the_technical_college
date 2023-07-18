#pragma once
#include "Student.h"
class Graduate :
    public Student {
private:
    std::string date;
public:
    Graduate(std::string name, int matNummer, std::string date) : date{ date }, Student(name, matNummer) {}

    // void print(Graduate* this) {
    void print() {
        std::cout << "Graduate, " << name << "," << matNummer << "," << date << std::endl;
    }

    // Kapselung auf public
    using Student::matNummer;
};

