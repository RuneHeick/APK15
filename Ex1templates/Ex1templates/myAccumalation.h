template <typename U>
typename U::value_type myAccumalation(const U& u)
{

	// this creates a instance of the type T from the contaionor class. 
	typename U::value_type m = typename U::value_type();

	/*The value_type must have a default constructor, and the puls operator must be implemented*/

	for (auto first = u.begin(); first != u.end(); ++first)
	{
		m += *first;
	}

	return m;
}