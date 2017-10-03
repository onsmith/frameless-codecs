#pragma once

#include "YUVpFrame.h"

#include <cstring>


template <typename intensity_t>
class YUV420pFrame : public YUVpFrame<intensity_t> {
public:
	/*
	** Constructor.
	*/
	YUV420pFrame(int width, int height) {
		yPlane.setDimensions(width,     height    );
		uPlane.setDimensions(width / 2, height / 2);
		vPlane.setDimensions(width / 2, height / 2);
		mem = new intensity_t[sizeofData() / sizeof(intensity_t)];
		yPlane.pointTo(mem);
		uPlane.pointTo(&mem[numLumaPixels()]);
		vPlane.pointTo(&mem[numLumaPixels() + numChromaPixels()]);
	}


	/*
	** Copy constructor.
	*/
	YUV420pFrame(const YUV420pFrame<intensity_t>& obj) {
		mem = new intensity_t[obj.sizeofData() / sizeof(intensity_t)];
		memcpy(mem, obj.mem, obj.sizeofData());
		yPlane.setDimensions(obj.lumaWidth(),   obj.lumaHeight());
		uPlane.setDimensions(obj.chromaWidth(), obj.chromaHeight());
		vPlane.setDimensions(obj.chromaWidth(), obj.chromaHeight());
		yPlane.pointTo(mem);
		uPlane.pointTo(&mem[numLumaPixels()]);
		vPlane.pointTo(&mem[numLumaPixels() + numChromaPixels()]);
	}


	/*
	** Copy assignment operator.
	*/
	YUV420pFrame& operator=(const YUV420pFrame<intensity_t>& obj) {
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


	/*
	** Destructor.
	*/
	~YUV420pFrame<intensity_t>() {
		delete mem;
	}
};
