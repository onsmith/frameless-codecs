#pragma once

#include "YUVpFrame.h"

#include <cstring>


template <typename intensity_t>
class YUV444pFrame : public YUVpFrame<intensity_t> {
public:
	/*
	** Constructor.
	*/
	YUV444pFrame(int width, int height) :
		YUVpFrame(width, height, width, height) {
	}


	/*
	** Copy constructor.
	*/
	YUV444pFrame(const YUV444pFrame<intensity_t>& obj) :
		YUVpFrame(obj) {
	}


	/*
	** Copy assignment operator.
	*/
	YUV444pFrame& operator=(const YUV444pFrame<intensity_t>& obj) {
		if (this != &obj) {
			if (sizeofData() != obj.sizeofData()) {
				delete mem;
				mem = new intensity_t[obj.sizeofData() / sizeof(intensity_t)];
				yPlane.pointTo(mem);
				uPlane.pointTo(&mem[obj.numLumaPixels()]);
				vPlane.pointTo(&mem[obj.numLumaPixels() + obj.numChromaPixels()]);
			}
			yPlane.setDimensions(obj.lumaWidth(),   obj.lumaHeight());
			uPlane.setDimensions(obj.chromaWidth(), obj.chromaHeight());
			vPlane.setDimensions(obj.chromaWidth(), obj.chromaHeight());
			memcpy(mem, obj.mem, obj.sizeofData());
		}
		return *this;
	}
};
