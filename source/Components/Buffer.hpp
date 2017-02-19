#ifndef COMPONENTS_BUFFER
#define COMPONENTS_BUFFER

#include <memory>

namespace Components
{

class Buffer
{
public:

	typedef unsigned char byte;

	Buffer(std::size_t capacity);
	Buffer(byte * data, std::size_t size);
	Buffer(const Buffer & buffer);
	Buffer & operator=(const Buffer & buffer);
	Buffer(Buffer && buffer);
	Buffer & operator=(Buffer && buffer);
	~Buffer();

	Buffer & append(const Buffer & buffer);
	Buffer & fit(std::size_t size);
	Buffer & expand(std::size_t capacity);
	Buffer block(std::size_t position, std::size_t size) const;
	void clear();
	byte * release();
	byte * data() const;
	std::size_t size() const;
	bool empty() const;

private:

	std::size_t _size;
	std::size_t _capacity;
	byte * _data;
};

}

#endif