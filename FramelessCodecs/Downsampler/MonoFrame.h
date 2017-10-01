#pragma once


#include <cassert>
#include <cstring>
#include <fstream>


using std::memcpy;
using std::istream;
using std::ostream;


template <typename intensity_t>
class MonoFrame {
private:
	/*
	 ** The width and height of the frame.
	 */
	int const w, h;

	/*
	 ** Points to the memory holding the frame data.
	 */
	intensity_t* const mem;

public:
	/*
	** Gets the total number of pixels in the frame.
	*/
	int numPixels() const;

	/*
	** Gets the height of the frame, in pixels.
	*/
	int height() const;

	/*
	** Gets the width of the frame, in pixels.
	*/
	int width() const;

	/*
	** Gets the total size of the frame data.
	*/
	size_t sizeofData() const;

	/*
	** Gets the underlying array of pixel intensity values.
	*/
	intensity_t* data() const;

	/*
	** Gets the intensity of the pixel located at position i, where pixels are
	**   zero-indexed in row-major order starting from the top left of the frame.
	*/
	intensity_t& operator()(int i) const;

	/*
	** Gets the intensity of the pixel located at position (x,y), where the
	**   origin is located at the top left corner of the frame, and pixels are
	**   zero-indexed.
	*/
	intensity_t& operator()(int x, int y) const;

	/*
	** Populates the frame's data using a given istream. Returns true if
	**   successful.
	*/
	bool readFrom(istream&);

	/*
	** Writes the frame's data to a given output stream.
	*/
	void writeTo(ostream&);

	/*
	** Assignment operator.
	*/
	MonoFrame<intensity_t>& operator=(const MonoFrame<intensity_t>&);

	/*
	** Constructors.
	*/
	MonoFrame() = delete;
	MonoFrame(const MonoFrame<intensity_t>&);
	MonoFrame(int width, int height);
	MonoFrame(int width, int height, intensity_t* mem);

	/*
	** Deconstructor.
	*/
	~MonoFrame();
};


template <typename intensity_t>
inline int MonoFrame<intensity_t>::numPixels() const {
	return w * h;
}

template<typename intensity_t>
inline int MonoFrame<intensity_t>::height() const {
	return h;
}

template<typename intensity_t>
inline int MonoFrame<intensity_t>::width() const {
	return w;
}


template <typename intensity_t>
inline size_t MonoFrame<intensity_t>::sizeofData() const {
	return numPixels() * sizeof(intensity_t);
}


template <typename intensity_t>
inline intensity_t* MonoFrame<intensity_t>::data() const {
	return mem;
}


template<typename intensity_t>
inline intensity_t& MonoFrame<intensity_t>::operator()(int i) const {
	return mem[i];
}


template <typename intensity_t>
inline intensity_t& MonoFrame<intensity_t>::operator()(int x, int y) const {
	return mem[y * w + x];
}


template<typename intensity_t>
bool MonoFrame<intensity_t>::readFrom(istream& stream) {
	stream.read((char*) mem, sizeofData());
	return stream.gcount() == sizeofData();
}

template<typename intensity_t>
void MonoFrame<intensity_t>::writeTo(ostream& stream) {
	stream.write((char*) mem, sizeofData());
}

template<typename intensity_t>
MonoFrame<intensity_t>& MonoFrame<intensity_t>::operator=(const MonoFrame<intensity_t>& obj) {
	if (this != &obj) {
		assert(w == obj.w);
		assert(h == obj.h);
		memcpy(mem, obj.mem, sizeofData());
	}
	return *this;
}


template<typename intensity_t>
MonoFrame<intensity_t>::MonoFrame(const MonoFrame<intensity_t>& obj) :
	width(obj.w),
	height(obj.h),
	mem(new intensity_t[w * h]) {
	memcpy(mem, obj.mem, sizeofData());
}


template<typename intensity_t>
MonoFrame<intensity_t>::MonoFrame(int width, int height) :
	w(width),
	h(height),
	mem(new intensity_t[width * height]) {
}


template <typename intensity_t>
MonoFrame<intensity_t>::MonoFrame(int width, int height, intensity_t* mem) :
	w(width),
	h(height),
	mem(new intensity_t[width * height]) {
	memcpy(this->mem, mem, sizeofData());
}


template<typename intensity_t>
MonoFrame<intensity_t>::~MonoFrame() {
	delete mem;
}
