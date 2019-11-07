#pragma once

#include <unordered_map>
#include <algorithm>

template <typename T>
class Matrix
{
public:
	int width;
	int height;

	Matrix(int w, int h) : width(w), height(h), data(w * h) {
		
	}

	T get(const int& a, const int& b) {
		return data[a + b * width];
	}

	const T& get(const int& a, const int& b) const {
		return data[a + b * width];
	}

	void set(const int& a, const int& b, T val) {
		data[a + b * width] = val;
	}

	void set_all(T val) {
		std::fill(data.begin(), data.end(), val);
	}

	void set_row(const int&row, T val) {
		std::fill_n(data.begin() + width * row, width , val);
	}
	
	//hack to get the double index notation to work
	class Row {
		Matrix* parent;
		const Matrix* c_parent;
		int a;

	public:
		Row(Matrix* parent, int a)
			: parent(parent)
			, a(a)
		{}

		Row(const Matrix* c_parent, int a)
			: c_parent(c_parent)
			, a(a)
		{}

		T operator[](int b)
		{
			return parent->get(a, b);
		}

		const T& operator[](int b) const
		{
			return c_parent->get(a, b);
		}
	};

	Row operator[](int a) {
		return Row{ this, a };
	}

	const Row operator[] (int b) const {
		return Row{ this, b };
	}

private: 
	std::vector<T> data;
};