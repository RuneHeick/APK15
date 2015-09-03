

template <typename T, typename TP>
T* myfind(T* first, T* last, const TP& v)
{
	auto* ptr = first;
	while (ptr != last)
	{
		if ((*ptr) == v)
			return ptr;
		ptr++;
	}
	return last;
}


template <typename T, typename V>
T** myfind(T** first, T** last, const V& v)
{
	auto* ptr = first;
	while (ptr != last)
	{
		T* element_ptr = (*ptr); 
		if (element_ptr != nullptr)
		{
			if ((*element_ptr) == v)
				return ptr;
		}
		ptr++;
	}
	return last;
}