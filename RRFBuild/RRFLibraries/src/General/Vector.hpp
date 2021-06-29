/*
 * Vector.hpp
 *
 * Created: 09/11/2014 09:50:41
 *  Author: David
 */


#ifndef VECTOR_H_
#define VECTOR_H_

#include "ecv.h"
#undef array
#undef result
#undef value
#include <cstddef>		// for size_t
#include <functional>

// Bounded vector class
template<class T, size_t N> class Vector
{
public:
	Vector() : filled(0) { }

	Vector(const size_t n, const T& fill);

	bool Full() const { return filled == N; }

	constexpr size_t Capacity() const { return N; }

	size_t Size() const { return filled; }

	bool IsEmpty() const { return filled == 0; }

	const T& operator[](size_t index) const pre(index < N) { return storage[index]; }

	T& operator[](size_t index) pre(index < N) { return storage[index]; }

	bool Add(const T& x);

	bool Add(const T* _ecv_array p, size_t n);

	void Erase(size_t pos, size_t count = 1);

	void Truncate(size_t pos) pre(pos <= filled);

	void Clear() { filled = 0; }

	const T* _ecv_array c_ptr() { return storage; }

	void Sort(std::function<bool(T, T)> sortfunc);

	bool Replace(T oldVal, T newVal);

protected:
	T storage[N];
	size_t filled;
};

template<class T, size_t N> Vector<T, N>::Vector(const size_t n, const T& fill)
	: filled(n)
{
	for (size_t i = 0; i < n; ++i)
	{
		storage[i] = fill;
	}
}

template<class T, size_t N> bool Vector<T, N>::Add(const T& x)
{
	if (filled < N)
	{
		storage[filled++] = x;
		return true;
	}
	return false;
}

template<class T, size_t N> bool Vector<T, N>::Add(const T* _ecv_array p, size_t n)
{
	while (n != 0)
	{
		if (filled == N)
		{
			return false;
		}
		storage[filled++] = *p++;
		--n;
	}
	return true;
}

// The sort function has to return true if the first element is greater than the second element
template<class T, size_t N> void Vector<T, N>::Sort(std::function<bool(T, T)> sortfunc)
{
	for (size_t i = 1; i < filled; ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			if (sortfunc(storage[j], storage[i]))
			{
				T temp = storage[i];
				// Insert element i just before element j
				for (size_t k = i; k > j; --k)
				{
					storage[k] = storage[k - 1];
				}
				storage[j] = temp;
			}
		}
	}
}

template<class T, size_t N> void Vector<T, N>::Erase(size_t pos, size_t count)
{
	while (pos + count < filled)
	{
		storage[pos] = storage[pos + count];
		++pos;
	}
	if (pos < filled)
	{
		filled = pos;
	}
}

template<class T, size_t N> void Vector<T, N>::Truncate(size_t pos)
{
	if (pos < filled)
	{
		filled = pos;
	}
}

template<class T, size_t N> bool Vector<T, N>::Replace(T oldVal, T newVal)
{
	for (size_t i = 0; i < filled; ++i)
	{
		if (storage[i] == oldVal)
		{
			storage[i] = newVal;
			return true;
		}
	}
	return false;
}

#endif /* VECTOR_H_ */
