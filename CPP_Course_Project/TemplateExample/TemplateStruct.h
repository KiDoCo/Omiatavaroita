#pragma once
#include <cstddef>

struct Templates
{
	template<typename T>
	T average(T number1, T number2, T number3)
	{
		T result = (number1 + number2 + number3) / 3;
		return result;
	}
	//uses std::array and returns lowest value
	template<typename value, size_t SIZE>
	value LowestVal(std::array<value, SIZE>& a)
	{
		std::cout << SIZE << std::endl;
		value b = a[0];
		for (int i = 0; i < SIZE; i++)
		{
			if (b > a[i])
			{
				b = a[i];
			}
		}

		return b;
	}

	template<typename val, size_t SIZE>
	void Sort(std::array<val, SIZE> &arr)
	{
		std::sort(arr.begin(), arr.end(), [](const val& v1, const val& v2) {return v1 < v2; });
	}

	template<typename val, size_t SIZE>
	bool Contains(std::array<val, SIZE> &arr, val variable)
	{
		for (const auto&value : arr)
		{
			if (variable == value)
			{
				return true;
			}
		}
		return false;
	}
};

template<typename Val>
class Stack
{
public:

	Stack(int maxSize) : max(maxSize), size(0)
	{
		data = new Val[max];
	}

	~Stack() { if (size > 0) delete[] data; }

	void push(Val element)
	{
		try
		{
			if (size >= max) throw;
			Val temp;

			data[size] = element;
			size++;

		}
		catch (const std::exception&e)
		{
			if (size >= max)
			{
				std::cout << "Stack is full!" << e.what() << std::endl;
				return;
			}
		}

	}

	Val pop()
	{
		try
		{
			if (size <= 0) throw;
			Val temp = data[size - 1];
			data[size] = 0;
			size--;
			return temp;

		}
		catch (const std::exception&e)
		{
			std::cout << "No Elements to pop out" << e.what() << std::endl;
			return 0;
		}
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << data[i] << std::endl;
		}
	}

private:
	int size, max;
	Val *data;
};


