#pragma once 

template<typename T, size_t capacity = 10>
class MyArray
{
public:

	MyArray()
	{}

	template<typename T2, size_t capacity2>
	MyArray(MyArray<T2, capacity2>& array)
	{
		size_t minsize = (capacity2 < capacity ? capacity2 : capacity); 
		for (int i = 0; i < minsize; i++)
		{
			_array[i] = static_cast<T>(array[i]);
		}
	}

	template<typename T2, size_t capacity2>
	MyArray& operator= (const MyArray<T2, capacity2>& array)
	{
		if (static_cast<const void*>(this) != static_cast<const void*>(&array))
		{
			size_t minsize = (capacity2 < capacity ? capacity2 : capacity);
			for (int i = 0; i < minsize; i++)
			{
				_array[i] = static_cast<T>(array[i]);
			}
		}
		return *this;

	}


	void fill(const T& value)
	{
		for (int i = 0; i < capacity; i++)
			_array[i] = value; 
	}

	const T*  begin() const
	{
		return &_array[0];
	}

	T*  begin() 
	{
		return &_array[0];
	}

	T* const end()
	{
		return &_array[capacity];
	}

	const T* const end() const
	{
		return &_array[capacity];
	}

	T& operator[](int i)
	{
		return _array[i];
	}

	const T& operator[](int i) const
	{
		return _array[i];
	}

	

	size_t size() const
	{
		return capacity;
	}


	typedef T value_type;
	

private:
	T _array[capacity]; 
};



template<typename T, size_t capacity>
class MyArray<T*, capacity>
{
public:

	MyArray()
	{
		for (int i = 0; i < capacity; i++)
		{
			_array[i] = nullptr; 
		}
	}


	~MyArray()
	{
		for (int i = 0; i < capacity; i++)
		{
			delete _array[i];
		}
	}

	//fill is removed since we don't what multible pointers to same object. 


	const T**  begin() const
	{
		return &_array[0];
	}

	T**  begin()
	{
		return &_array[0];
	}

	T** const end()
	{
		return &_array[capacity];
	}

	const T** const end() const
	{
		return &_array[capacity];
	}

	T*& operator[](int i)
	{
		return _array[i];
	}

	const T*& operator[](int i) const
	{
		return _array[i];
	}

	size_t size() const
	{
		return capacity;
	}



private:
	T* _array[capacity];
};

