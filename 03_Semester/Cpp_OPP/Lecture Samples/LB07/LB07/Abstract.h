#pragma once
class Abstract { // Abstract class
public:
	virtual void print() const = 0; // Purely virtual function
};

class Concrete : public Abstract {
public:

	// Inherited via Abstract
	virtual void print() const override; // Implementation of parent pureky virtual function
};

class AbstractConcrete : public Concrete { // Can be made abstract again
	virtual int foo() = 0; // Purely virtual function
};