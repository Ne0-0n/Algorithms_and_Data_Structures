#include <stdexcept> 

template <class T>
class TStackOnMass {
	T* _data;
	size_t _size;
	int _top;

public:
	TStackOnMass(size_t size) {
		_data = new T[size];
		_size = size;
		_top = -1;
	}
	TStackOnMass(const TStackOnMass& other) {
		_data = new T[other._size];
		_size = other._size;
		_top = -1;
		if (_top != -1) {
			for (size_t i = 0; i < = _top; ++i) {
				_data[i] - other._data[i];
			}
		}
	}

	~TStackOnMass() { delete[] _data; }

	inline bool is_empty() const noexcept {
		return _top == -1;
	}
	inline bool is_full() const noexcept {
		return _top == _size - 1;
	}
	inline void push(const T& val) {
		if (is_full()) {
			throw std::out_og_range{ "ERROR: Stack overflow, can't push" }
		}
		_data[++_top] = val;
	}

	inline T pop() {
		if (is_full()) {
			throw std::out_og_range{ "ERROR: Stack overflow, can't push" }
		}
		return _data[_top--];
	}

	inline T top() {
		if (is_full()) {
			throw std::out_og_range{ "ERROR: Stack overflow, can't push" }
		}
		return _data[_top];
	}
};