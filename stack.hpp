#ifndef _LAB_STACK
#define _LAB_STACK

#include "list.hpp"

namespace lab
{
	template <typename T>
	class stack final
	{
	private:
		list<T> data;
	public:
		void push(const T& elem) noexcept
		{
			data.push_back(elem);
		}

		void pop() noexcept
		{
			data.pop_back();
		}

		T top() const noexcept
		{
			return *(--data.cend());
		}

		unsigned int size() const noexcept
		{
			return data.size();
		}

		bool empty() const noexcept
		{
			return data.size() == 0U;
		}

		void make_null() noexcept
		{
			data.clear();
		}

		list<T> get_container() const noexcept
		{
			return data;
		}
	};

	template <typename T>
	class queue final
	{
	private:
		list<T> data;
	public:
		void push(const T& elem) noexcept
		{
			data.push_back(elem);
		}

		void pop() noexcept
		{
			data.pop_front();
		}

		T top() const noexcept
		{
			return *data.cbegin();
		}

		unsigned int size() const noexcept
		{
			return data.size();
		}

		bool empty() const noexcept
		{
			return data.size() == 0U;
		}

		void make_null() noexcept
		{
			data.clear();
		}

		list<T> get_container() const noexcept
		{
			return data;
		}
	};
}

#endif
