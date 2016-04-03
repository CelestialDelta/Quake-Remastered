#include "..\Include\vector.hpp"

template<typename T, typename A>
const Vec_Value<T, A> Vector<T, A>::EMPTY_VALUE = _array[-1];

template<typename T, typename A>
Vector<T, A>::Vector(size_t maxSize)
	: _array(), _size(), _maxSize(maxSize), _allocator()
{
	Block block = _allocator.allocate(sizeof(Value) * maxSize);
	_array = static_cast<Array>(block.memory);
}

template<typename T, typename A>
Vector<T, A>::Vector(const Container& container)
	: _array(), _size(container._size), _maxSize(container._maxSize), _allocator()
{
	Block block = _allocator.allocate(sizeof(Value) * _maxSize);
	_array = static_cast<Array>(block.memory);
	for (size_t i = 0; i < _size; i++)
	{
		Value value = container[i];
		_array[i] = value;
	}
}

template<typename T, typename A>
Vector<T, A>::~Vector()
{
	if (_array)
	{
		clear();
	}
	_allocator.destroy();
}

template<typename T, typename A>
void Vector<T, A>::pushBack(ConstReference reference)
{
	if (!_hasSpaceFor(1))
	{
		reserve(_maxSize + VECTOR_RESERVE_SIZE);
	}
	_array[_size] = reference;
	_incrementSize();
}

template<typename T, typename A>
void Vector<T, A>::popBack()
{
	if (!isEmpty())
	{
		_array[_size - 1] = Value();
		_decrementSize();
	}
}

template<typename T, typename A>
Vec_Reference<T, A>
Vector<T, A>::front() const
{
	return !isEmpty() ? _array[0] : EMPTY_VALUE;
}

template<typename T, typename A>
Vec_Reference<T, A>
Vector<T, A>::back() const
{
	return !isEmpty() ? _array[_size - 1] : EMPTY_VALUE;
}

template<typename T, typename A>
Vec_Iterator<T, A>
Vector<T, A>::find(ConstReference reference) const
{
	for (size_t i = 0; i < _size; i++)
	{
		if (_array[i] == reference)
		{
			return Iterator(&_array[i]);
		}
	}
	return this->end();
}

template<typename T, typename A>
QBool Vector<T, A>::has(ConstReference reference) const
{
	for (size_t i = 0; i < _size; i++)
	{
		if (_array[i] == reference)
		{
			return true;
		}
	}
	return false;
}

template<typename T, typename A>
void Vector<T, A>::clear()
{
	size_t size = sizeof(Value) * _maxSize;
	void* mem = static_void<void*>(_array);
	Block block(mem, size);
	_allocator.deallocate(block);
	_maxSize = 0;
	_size = 0;
}

template<typename T, typename A>
void Vector<T, A>::isEmpty() const
{
	return _size == 0;
}

template<typename T, typename A>
QBool Vector<T, A>::isFull() const
{
	return _size == _maxSize;
}

template<typename T, typename A>
Vec_Reference<T, A>
Vector<T, A>::at(size_t index) const
{
	return _checkIndex(index) ? _array[index] : EMPTY_VALUE;
}

template<typename T, typename A>
Vec_Reference<T, A>
Vector<T, A>::operator[](size_t index) const
{
	return at(index);
}

template<typename T, typename A>
void Vector<T, A>::operator=(const Container& other)
{
	_size = other._size;
	_maxSize = other._maxSize;
	Block block = _allocator.allocate(sizeof(Value) * _maxSize);
	_array = static_cast<Array>(block.memory);
	for (size_t i = 0; i < _size; i++)
	{
		Value value = container[i];
		_array[i] = value;
	}
}

template<typename T, typename A>
QBool Vector<T, A>::equals(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (size_t i = 0; i < tSize; i++)
		{
			if (_array[i] != other[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename T, typename A>
Vector<T, A>::operator bool() const
{
	return _size && _maxSize && _array;
}

template<typename T, typename A>
QBool Vector<T, A>::operator==(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (size_t i = 0; i < tSize; i++)
		{
			if (_array[i] != other[i])
			{
				return false
			}
		}
		return true;
	}
	return false;
}

template<typename T, typename A>
QBool Vector<T, A>::operator!=(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (size_t i = 0; i < tSize; i++)
		{
			if (_array[i] != other[i])
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

template<typename T, typename A>
QBool Vector<T, A>::operator<(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		for (size_t i = 0; i < tSize; i++)
		{
			if (_array[i] >= other[i])
			{
				return false;
			}
		}
		return true;
	}
	return tSize < oSize;
}

template<typename T, typename A>
QBool Vector<T, A>::operator<=(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		for (size_t i = 0; i < tSize; i++)
		{
			if (_array[i] > other[i])
			{
				return false;
			}
		}
		return true;
	}
	return tSize <= oSize;
}

template<typename T, typename A>
QBool Vector<T, A>::operator>(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		for (size_t i = 0; i < tSize; i++)
		{
			if (_array[i] <= other[i])
			{
				return false;
			}
		}
		return true;
	}
	return tSize > oSize;
}

template<typename T, typename A>
QBool Vector<T, A>::operator>=(const Container& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		for (size_t i = 0; i < tSize; i++)
		{
			if (_array[i] < otheri])
			{
				return false;
			}
		}
		return true;
	}
	return tSize >= oSize;
}

template<typename T, typename A>
const Vec_Iterator<T, A>
Vector<T, A>::begin() const
{
	return Iterator(_array[0]);
}

template<typename T, typename A>
const Vec_ConstIterator<T, A>
Vector<T, A>::end() const
{
	return Iterator(_array[_size]);
}

template<typename T, typename A>
const Vec_ConstIterator<T, A>
Vector<T, A>::cbegin() const
{
	return ConstIterator(_array[0]);
}

template<typename T, typename A>
const Vec_ConstIterator<T, A>
Vector<T, A>::cend() const
{
	return ConstIterator(_array[_size]);
}

template<typename T, typename A>
const Vec_ReverseIterator<T, A>
Vector<T, A>::rbegin() const
{
	return ReverseIterator(_array[_size - 1]);
}

template<typename T, typename A>
const Vec_ReverseIterator<T, A>
Vector<T, A>::rend() const
{
	return ReverseIterator(_array[-1]);
}

template<typename T, typename A>
const Vec_ConstReverseIterator<T, A>
Vector<T, A>::crbegin() const
{
	return ConstReverseIterator(_array[_maxSize - 1]);
}

template<typename T, typename A>
const Vec_ConstReverseIterator<T, A>
Vector<T, A>::crend() const
{
	return ConstReverseIterator(_array[-1]);
}

template<typename T, typename A>
size_t Vector<T, A>::size() const
{
	return _size;
}

template<typename T, typename A>
size_t Vector<T, A>::maxSize() const
{
	return _maxSize;
}

template<typename T, typename A>
const Vec_Allocator<T, A> 
Vector<T, A>::allocator() const
{
	return _allocator;
}

template<typename T, typename A>
ALLOCATOR_ID Vector<T, A>::allocatorID() const
{
	return _allocator.getID();
}

template<typename T, typename A>
QBool Vector<T, A>::_hasSpaceFor(size_t size) const
{
	return _size + size <= _maxSize;
}

template<typename T, typename A>
void Vector<T, A>::_incrementSize()
{
	_size++;
}

template<typename T, typename A>
void Vector<T, A>::_decrementSize()
{
	_size--;
}

template<typename T, typename A>
QBool Vector<T, A>::_checkIndex(size_t index) const
{
	return index >= 0 && index < _size;
}