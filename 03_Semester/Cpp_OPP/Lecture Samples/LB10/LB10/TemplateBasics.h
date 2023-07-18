#pragma once
#include <iostream>
#include <vector>

// "C-Way"
int intAdd(int a, int b) { return a + b; }
float floatAdd(float a, float b) { return a + b; }
std::string stringAdd(std::string a, std::string b) { return a + b; }

// Operator Overloading
int Add(int a, int b) { return a + b; }
float Add(float a, float b) { return a + b; }
std::string Add(std::string a, std::string b) { return a + b; }

// Template function
template <typename T> // <class T>
T TAdd(T a, T b) { return a + b; };

// Template function
template <typename T> // <class T>
T TMulti(T a, T b) { return a * b; };

template <typename T>
std::string TMulti(std::string a, std::string b) {
    std::cerr << "Multiplication of strings not supported!" << std::endl;
    return a + b;
}

template <class T>
class MyClass {
    T value;
};