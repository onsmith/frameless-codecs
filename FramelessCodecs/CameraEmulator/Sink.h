#pragma once


template <typename T>
class Sink {
public:
	virtual write(T) = 0;
};
