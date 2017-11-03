#pragma once

#include "Sink.h"
#include "PixelFire.h"


class PixelFireConsoleSink final : public Sink<PixelFire> {
public:
	/*
	** Writes a PixelFire object to cout.
	*/
	void write(const PixelFire&) final;
};
