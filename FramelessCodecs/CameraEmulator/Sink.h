#pragma once


template <typename T>
class Sink {
public:
	virtual void write(T&) = 0;
};
