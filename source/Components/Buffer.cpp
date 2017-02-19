#include "Buffer.hpp"

namespace Components
{

Buffer::Buffer(std::size_t capacity)
	: _data(new byte[capacity]),
	_size(0),
	_capacity(capacity)
{
}

Buffer::Buffer(byte * data, std::size_t size)
	: _data(data),
	_size(size),
	_capacity(size)
{
}

Buffer::Buffer(const Buffer & buffer)
{
	_size = buffer._size;
	_capacity = buffer._capacity;
	_data = new byte[_capacity];
	memcpy(_data, buffer._data, _size);
}

Buffer &
Buffer::operator=(const Buffer & buffer)
{
	if (&buffer == this)
		return *this;

	delete[] _data;
	_size = buffer._size;
	_capacity = buffer._capacity;
	_data = new byte[_capacity];
	memcpy(_data, buffer._data, _size);

	return *this;
}

Buffer::Buffer(Buffer && buffer)
{
	_size = buffer._size;
	_capacity = buffer._capacity;
	_data = buffer._data;

	buffer._size = 0;
	buffer._capacity = 0;
	buffer._data = nullptr;
}


Buffer &
Buffer::operator=(Buffer && buffer)
{
	if (&buffer == this)
		return *this;

	std::swap(_size, buffer._size);
	std::swap(_capacity, buffer._capacity);
	std::swap(_data, buffer._data);

	return *this;
}


Buffer::~Buffer()
{
	delete[] _data;
}


Buffer &
Buffer::append(const Buffer & buffer)
{
	std::size_t size = _size + buffer._size;
	if (_capacity >= size)
	{
		memcpy(_data + _size, buffer._data, buffer._size);
		_size = size;
	}
	else
	{
		_capacity = size * 2;
		byte * data = new byte[_capacity];
		memcpy(data, _data, _size);
		memcpy(data + _size, buffer._data, buffer._size);
		_size = size;
		delete[] _data;
		_data = data;
	}
	return *this;
}

Buffer &
Buffer::fit(std::size_t size)
{
	if (size >= _size)
		return *this;

	_capacity = _size = size;
	byte * data = new byte[_size];
	memcpy(data, _data, _size);
	delete[] _data;
	_data = data;
	return *this;
}

Buffer &
Buffer::expand(std::size_t capacity)
{
	if (capacity <= _capacity)
		return *this;

	_capacity = capacity;
	byte * data = new byte[_capacity];
	memcpy(data, _data, _size);
	delete[] _data;
	_data = data;
	return *this;

}

Buffer
Buffer::block(std::size_t position, std::size_t size) const
{
	std::size_t bSize =
		size <= _size - position ? size : _size - position;
	byte * data = new byte[bSize];
	memcpy(data, _data + position, bSize);
	return Buffer(data, bSize);
}

void
Buffer::clear()
{
	delete[] _data;
	_data = nullptr;
	_capacity = _size = 0;
}

Buffer::byte *
Buffer::release()
{
	byte * data = _data;
	_capacity = _size = 0;
	_data = nullptr;
	return data;
}

Buffer::byte *
Buffer::data() const
{
	return _data;
}

std::size_t
Buffer::size() const
{
	return _size;
}

bool
Buffer::empty() const
{
	return
		_data == nullptr ||
		(_capacity == 0 && _size == 0);
}

}