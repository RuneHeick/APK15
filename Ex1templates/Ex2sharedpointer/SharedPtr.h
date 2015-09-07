namespace Sharedptr
{


	template<typename T>
	class PtrContainor;

	template<typename T>
	class standard_deleter
	{
	public:
		standard_deleter()
		{}

		void operator()(T* item)
		{
			delete item;
		}
	};



	template<typename T>
	class FuncBase
	{
	public:
		FuncBase()
		{}

		virtual void operator()(T* item) = 0;
	private:
	};


	template<typename T, typename D>
	class FuncImplementation : public FuncBase<T>
	{
	public:
		FuncImplementation(D func)
		{
			function = func;
		}

		void operator()(T* item) override
		{
			function(item);
		}

	private:
		D function;
	};


	template<typename T, typename D = standard_deleter<T>>
	class SharedPtr
	{
	public:
		explicit SharedPtr(T* t, D deleter = standard_deleter<T>())
		{
			containor_ptr = new PtrContainor<T>(new FuncImplementation<T, D>(deleter));
			containor_ptr->heap_ptr = t;
			containor_ptr->count = 1;
		}

		SharedPtr(const SharedPtr& ptr)
		{
			containor_ptr = ptr.containor_ptr;
			containor_ptr->count++;
		}

		SharedPtr& operator=(const SharedPtr& ptr)
		{
			if (this != &ptr)
			{
				cleanUp();

				containor_ptr = ptr.containor_ptr;
				containor_ptr->count++;
			}
			return *this;
		}

		~SharedPtr()
		{
			cleanUp();
		}

		T& operator*()
		{
			return *(containor_ptr->heap_ptr);
		}

		T* operator->()
		{
			return (containor_ptr->heap_ptr);
		}

		bool operator==(const SharedPtr& other) const
		{
			return containor_ptr->heap_ptr == other.containor_ptr->heap_ptr;
		}

		size_t count() const
		{
			return containor_ptr->count;
		}

	private:
		PtrContainor<T>* containor_ptr;

		void cleanUp()
		{
			containor_ptr->count--;
			if (containor_ptr->count == 0)
			{
				(*(containor_ptr->deleter))(containor_ptr->heap_ptr);
				delete containor_ptr;
			}
		}

	};


	template<typename T, typename T2>
	bool operator==(SharedPtr<T>& left, SharedPtr<T2>& right)
	{
		return &(*left) == &(*right); // to get the heap address; 
	};



	template<typename T>
	struct PtrContainor
	{
		PtrContainor(FuncBase<T>* del)
		{
			deleter = del;
		}

		~PtrContainor()
		{
			delete deleter;
		}

		FuncBase<T>* deleter;

		T* heap_ptr;
		size_t count;

	};

};


