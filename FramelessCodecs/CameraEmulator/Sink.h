#pragma once


template <typename T>
class Sink {
public:
	virtual void write(const T&) = 0;
	virtual ~Sink() = default;
};
