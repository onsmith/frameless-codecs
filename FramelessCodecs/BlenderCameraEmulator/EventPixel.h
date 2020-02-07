#pragma once
using namespace std;
class EventPixel
{
public:
	int x;
	int y;
	float current_integration;
	int D;

	EventPixel(int x, int y) {
		this->x = x;
		this->y = y;
		current_integration = 0.0;
		D = 8;
	}

	void integrate(float accumulation) {
		current_integration += accumulation;
	}
};

