#pragma once


template <typename T>
class Source {
public:
	virtual T read() = 0;
};
