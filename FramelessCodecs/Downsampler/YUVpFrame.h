#pragma once

#include "Plane.h"

#include <cstring>
using std::memcpy;

#include <fstream>
using std::istream;
using std::ostream;


template <typename intensity_t>
class YUVpFrame {
protected:
	/*
	 ** The y, u, and v planes.
	 */
	Plane yPlane, uPlane, vPlane;


	/*
	 ** A pointer to the memory containing the frame data.
	 */
	intensity_t* mem;


public:
	/*
	** Gets the width of the luma plane, in pixels.
	*/
	int lumaWidth() const {
		return yPlane.width();
	}


	/*
	** Gets the height of the luma plane, in pixels.
	*/
	int lumaHeight() const {
		return yPlane.height();
	}


	/*
	** Gets the width of the chroma planes, in pixels.
	*/
	int chromaWidth() const {
		return uPlane.width();
	}


	/*
	** Gets the height of the chroma planes, in pixels.
	*/
	int chromaHeight() const {
		return uPlane.height();
	}


	/*
	** Gets the number of pixels in the luma plane.
	*/
	int numLumaPixels() const {
		return yPlane.numPixels();
	}


	/*
	** Gets the number of pixels in each chroma plane.
	*/
	int numChromaPixels() const {
		return uPlane.numPixels();
	}


	/*
	** Gets the total number of intensity values stored by the frame.
	*/
	int numIntensities() const {
		return
			yPlane.numIntensities() +
			uPlane.numIntensities() +
			vPlane.numIntensities();
	}


	/*
	** Gets the size of the pixel intensity array, in number of bytes.
	*/
	size_t sizeofData() const {
		return
			yPlane.sizeofData() +
			uPlane.sizeofData() +
			vPlane.sizeofData();
	}


	/*
	** Gets the underlying array of pixel intensity values.
	*/
	intensity_t* data() const {
		return mem;
	}


	/*
	** Gets a pointer to the underlying y plane memory.
	*/
	intensity_t* y() const {
		return yPlane.data();
	}


	/*
	** Gets a reference to a given pixel's y-plane intensity value.
	*/
	intensity_t& y(int i) const {
		return yPlane.intensityAt(i);
	}


	/*
	** Gets a reference to a given pixel's y-plane intensity value.
	*/
	intensity_t& y(int x, int y) const {
		return yPlane.intensityAt(x, y);
	}


	/*
	** Gets a pointer to the underlying u plane memory.
	*/
	intensity_t* u() const {
		return uPlane.data();
	}


	/*
	** Gets a reference to a given pixel's u-plane intensity value.
	*/
	intensity_t& u(int i) const {
		return uPlane.intensityAt(i);
	}


	/*
	** Gets a reference to a given pixel's u-plane intensity value.
	*/
	intensity_t& u(int x, int y) const {
		return uPlane.intensityAt(x, y);
	}


	/*
	** Gets a pointer to the underlying v plane memory.
	*/
	intensity_t* v() const {
		return vPlane.data();
	}


	/*
	** Gets a reference to a given pixel's v-plane intensity value.
	*/
	intensity_t& v(int i) const {
		return vPlane.intensityAt(i);
	}


	/*
	** Gets a reference to a given pixel's v-plane intensity value.
	*/
	intensity_t& v(int x, int y) const {
		return vPlane.intensityAt(x, y);
	}


	/*
	** Populates the frame's intensity array by reading from a given istream.
	**   Returns true if successful.
	*/
	bool readFrom(istream& stream) {
		stream.read(reinterpret_cast<char*>(mem), sizeofData());
		return stream.gcount() == sizeofData();
	}


	/*
	** Writes the frame's intensity array to a given output stream.
	*/
	void writeTo(ostream& stream) {
		stream.write(reinterpret_cast<char*>(mem), sizeofData());
	}


	/*
	** Constructor.
	*/
	YUVpFrame(int lumaWidth, int lumaHeight, int chromaWidth, int chromaHeight) :
		yPlane(lumaWidth,   lumaHeight),
		uPlane(chromaWidth, chromaHeight),
		vPlane(chromaWidth, chromaHeight) {
		mem = new intensity_t[numIntensities()];
		yPlane.pointTo(mem);
		uPlane.pointTo(&mem[numLumaPixels()]);
		vPlane.pointTo(&mem[numLumaPixels() + numChromaPixels()]);
	}


	/*
	** Copy constructor.
	*/
	YUVpFrame(const YUVpFrame<intensity_t>& obj) :
		yPlane(obj.lumaWidth(),   obj.lumaHeight()),
		uPlane(obj.chromaWidth(), obj.chromaHeight()),
		vPlane(obj.chromaWidth(), obj.chromaHeight()) {
		mem = new intensity_t[numIntensities()];
		memcpy(mem, obj.mem, obj.sizeofData());
		yPlane.pointTo(mem);
		uPlane.pointTo(&mem[numLumaPixels()]);
		vPlane.pointTo(&mem[numLumaPixels() + numChromaPixels()]);
	}


	/*
	** Copy assignment operator.
	*/
	YUVpFrame& operator=(const YUVpFrame<intensity_t>& obj) {
		if (this != &obj) {
			if (sizeofData() != obj.sizeofData()) {
				delete mem;
				mem = new intensity_t[obj.numIntensities()];
				yPlane.pointTo(mem);
				uPlane.pointTo(&mem[obj.numLumaPixels()]);
				vPlane.pointTo(&mem[obj.numLumaPixels() + obj.numChromaPixels()]);
			}
			yPlane.setDimensionsTo(obj.lumaWidth(),   obj.lumaHeight());
			uPlane.setDimensionsTo(obj.chromaWidth(), obj.chromaHeight());
			vPlane.setDimensionsTo(obj.chromaWidth(), obj.chromaHeight());
			memcpy(mem, obj.mem, obj.sizeofData());
		}
		return *this;
	}


	/*
	** Destructor.
	*/
	~YUVpFrame<intensity_t>() {
		delete mem;
	}
};
