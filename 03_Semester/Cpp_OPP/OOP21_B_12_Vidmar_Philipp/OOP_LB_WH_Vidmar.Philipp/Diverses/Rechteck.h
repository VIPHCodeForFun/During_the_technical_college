#pragma once
class Rechteck
{
private:
protected:
	int a;
	int b;
public:
	Rechteck(int a, int b) : a{ a }, b{ b } {}
	~Rechteck() = default;	// Dtor

	Rechteck(const Rechteck& copy)  //CCtor
	{
		this->a = copy.a;
		this->b = copy.b;
	}
	Rechteck(Rechteck&& move) noexcept //Move
	{
		this->a = move.a;
		this->b = move.b;
	}

};

