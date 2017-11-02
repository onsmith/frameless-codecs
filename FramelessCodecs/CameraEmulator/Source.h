#pragma once


template <typename T>
class Source {
public:
	virtual void read(T&) = 0;
};
