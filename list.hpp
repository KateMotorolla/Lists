#ifndef _LAB_LIST
#define _LAB_LIST

#include <iostream>
#include <initializer_list>

namespace lab
{
	template <typename T>
	class list final
	{
	private:
		struct node
		{
			node* prev, * next;
			T elem;

			node(const T& arg_elem, node* arg_prev, node* arg_next) noexcept
				: elem(arg_elem), prev(arg_prev), next(arg_next) {}
		};

		node* head = nullptr;
		node* tail = nullptr;
		unsigned int element_count = 0U;
	public:
		class iterator final
		{
		private:
			node* ptr = nullptr;

			iterator(node* arg_ptr) noexcept
				: ptr(arg_ptr) {}

			friend class list<T>;
			friend class const_iterator;
		public:
			iterator() = default;

			iterator& operator++() noexcept
			{
				ptr = ptr->next;
				return *this;
			}

			iterator& operator--() noexcept
			{
				ptr = ptr->prev;
				return *this;
			}

			T& operator*() noexcept
			{
				return ptr->elem;
			}

			const T& operator*() const noexcept
			{
				return ptr->elem;
			}

			bool operator==(const iterator& other) noexcept
			{
				return ptr == other.ptr;
			}

			bool operator!=(const iterator& other) noexcept
			{
				return !(ptr == other.ptr);
			}
		};

		class const_iterator final
		{
		private:
			node* ptr = nullptr;

			const_iterator(node* arg_ptr) noexcept
				: ptr(arg_ptr) {}

			friend class list<T>;
		public:
			const_iterator() = default;

			const_iterator(const iterator& it) noexcept
				: ptr(it.ptr) {}

			const_iterator& operator++() noexcept
			{
				ptr = ptr->next;
				return *this;
			}

			const_iterator& operator--() noexcept
			{
				ptr = ptr->prev;
				return *this;
			}

			T operator*() const noexcept
			{
				return ptr->elem;
			}

			bool operator==(const const_iterator& other) noexcept
			{
				return ptr == other.ptr;
			}

			bool operator!=(const const_iterator& other) noexcept
			{
				return !(ptr == other.ptr);
			}
		};

		void push_back(const T& elem) noexcept
		{
			if (tail->prev == nullptr)
			{
				tail->prev = new node(elem, nullptr, tail);
				head = tail->prev;
				++element_count;
			}
			else
			{
				node* current = tail->prev;
				tail->prev = new node(elem, current, tail);
				current->next = tail->prev;
				++element_count;
			}
		}

		void push_front(const T& elem) noexcept
		{
			head->prev = new node(elem, nullptr, head);
			head = head->prev;
			++element_count;
		}

		void pop_back() noexcept
		{
			if (head != tail)
			{
				tail = tail->prev;
				delete tail->next;
				tail->next = nullptr;
				--element_count;
			}
		}

		void pop_front() noexcept
		{
			if (head != tail)
			{
				head = head->next;
				delete head->prev;
				head->prev = nullptr;
				--element_count;
			}
		}

		void insert(iterator it, const T& elem)
		{
			if (it.ptr == nullptr)
				throw "empty iterator";
			if (it.ptr == tail)
				throw "insert out of range";
			if (it.ptr == head)
				push_front(elem);
			else
			{
				it.ptr->prev->next = new node(elem, it.ptr->prev, it.ptr);
				it.ptr->prev = it.ptr->prev->next;
				++element_count;
			}
		}

		void erase(iterator it)
		{
			if (it.ptr == nullptr)
				throw "empty iterator";
			if (it.ptr == tail)
				throw "erase out of range";
			if (it.ptr == head)
				pop_front();
			else
			{
				it.ptr->prev->next = it.ptr->next;
				it.ptr->next->prev = it.ptr->prev;
				delete it.ptr;
				--element_count;
			}
		}

		list() noexcept
			: head(new node(T(), nullptr, nullptr)), tail(head) 
		{
			head->prev = tail->next = nullptr;
		}

		list(const std::initializer_list<T>& args) noexcept
			: head(new node(T(), nullptr, nullptr)), tail(head)
		{
			head->prev = tail->next = nullptr;
			for (auto i = args.begin(); i != args.end(); ++i)
				push_back(*i);
		}

		list(const list<T>& other) noexcept
			: head(new node(T(), nullptr, nullptr)), tail(head)
		{
			head->prev = tail->next = nullptr;
			for (auto i = other.cbegin(); i != other.cend(); ++i)
				push_back(*i);
		}

		list(list<T>&& other) noexcept
			: head(other.head), tail(other.tail), element_count(other.element_count)
		{
			other.head = nullptr;
			other.tail = nullptr;
			other.element_count = 0U;
		}

		~list() noexcept
		{
			clear();
			delete tail;
		}

		list<T>& operator=(const list<T>& other) noexcept
		{
			clear();
			for (auto i = other.cbegin(); i != other.cend(); ++i)
				push_back(i);
			return *this;
		}

		list<T>& operator=(list<T>&& other) noexcept
		{
			clear();
			head = other.head;
			tail = other.tail;
			element_count = other.element_count;
			other.head = nullptr;
			other.tail = nullptr;
			other.element_count = 0U;
			return *this;
		}

		unsigned int size() const noexcept
		{
			return element_count;
		}

		iterator begin() noexcept
		{
			return iterator(head);
		}

		iterator end() noexcept
		{
			return iterator(tail);
		}

		const_iterator cbegin() const noexcept
		{
			return const_iterator(head);
		}

		const_iterator cend() const noexcept
		{
			return const_iterator(tail);
		}

		void clear() noexcept
		{
			if (head != tail)
			{
				for (node* i = head->next; i != tail; i = i->next)
					delete i->prev;
				head = tail;
				head->prev = tail->next = nullptr;
				element_count = 0U;
			}
		}

		bool is_sorted() const noexcept
		{
			for (auto i = cbegin(); i != --cend(); ++i)
			{
				if (*i > *++const_iterator(i))
					return false;
			}
			return true;
		}

		void merge(list<T>&& other)
		{
			if (!is_sorted() || !other.is_sorted())
				throw "some list is not sorted";
			iterator i = this->begin();
			iterator j = other.begin();
			static auto insert_ptr = [](iterator& a, iterator& b)
			{
				if (b.ptr->next == nullptr)
				{
					++a;
					return;
				}
				iterator c = a.ptr->prev;
				if (c.ptr != nullptr)
				{
					a.ptr->prev = b.ptr;
					++b;
					a.ptr->prev->next = a.ptr;
					a.ptr->prev->prev = c.ptr;
					c.ptr->next = a.ptr->prev;
				}
				else
				{
					a.ptr->prev = b.ptr;
					++b;
					a.ptr->prev->next = a.ptr;
				}
			};
			if (*j < *i)
			{
				insert_ptr(i, j);
				head = i.ptr->prev;
			}
			while (i != this->end())
			{
				if (*j < *i)
					insert_ptr(i, j);
				else
					++i;
			}
			other.head = other.tail = nullptr;
		}

		void exchange(iterator first, iterator second)
		{
			if (first.ptr == nullptr || second.ptr == nullptr)
				throw "empty iterator";
			if (first.ptr == tail || second.ptr == tail)
				throw "exchange out of range";
			if (first.ptr == second.ptr)
				return;
			if (first.ptr->next == second.ptr)
			{
				second.ptr->prev = first.ptr->prev;
				first.ptr->prev = second.ptr;
				first.ptr->next = second.ptr->next;
				second.ptr->next = first.ptr;
				first.ptr->next->prev = first.ptr;
				if (second.ptr->prev != nullptr) second.ptr->prev->next = second.ptr;
			}
			else if (second.ptr->next == first.ptr)
			{
				first.ptr->prev = second.ptr->prev;
				second.ptr->prev = first.ptr;
				second.ptr->next = first.ptr->next;
				first.ptr->next = second.ptr;
				second.ptr->next->prev = second.ptr;
				if (first.ptr->prev != nullptr) first.ptr->prev->next = first.ptr;
			}
			else
			{
				if (first.ptr->prev != nullptr) first.ptr->prev->next = second.ptr;
				if (second.ptr->prev != nullptr) second.ptr->prev->next = first.ptr;
				first.ptr->next->prev = second.ptr;
				second.ptr->next->prev = first.ptr;
				std::swap(first.ptr->prev, second.ptr->prev);
				std::swap(first.ptr->next, second.ptr->next);
			}
			head = first.ptr == head ? second.ptr : (second.ptr == head ? first.ptr : head);
		}

		void sort() noexcept
		{
			for (auto i = ++begin(); i != end();)
			{
				iterator insert_it = iterator(nullptr);
				for (auto j = i; j != iterator(nullptr); --j)
				{
					if (*j < *i)
					{
						insert_it = j;
						break;
					}
				}
				iterator temp = i;
				++i;
				if (insert_it == iterator(nullptr))
				{
					temp.ptr->prev->next = temp.ptr->next;
					temp.ptr->next->prev = temp.ptr->prev;
					head->prev = temp.ptr;
					temp.ptr->prev = nullptr;
					temp.ptr->next = head;
					head = head->prev;
				}
				else
				{
					temp.ptr->prev->next = temp.ptr->next;
					temp.ptr->next->prev = temp.ptr->prev;
					temp.ptr->prev = insert_it.ptr;
					temp.ptr->next = insert_it.ptr->next;
					insert_it.ptr->next->prev = temp.ptr;
					insert_it.ptr->next = temp.ptr;
				}
			}
		}
	};

	template <typename T>
	typename list<T>::iterator max_element(typename list<T>::iterator first,
		typename list<T>::iterator last) noexcept
	{
		typename list<T>::iterator result = first;
		for (auto i = first; i != last; ++i)
		{
			if (*i > *result)
				result = i;
		}
		return result;
	}

	template <typename T>
	typename list<T>::iterator min_element(typename list<T>::iterator first,
		typename list<T>::iterator last) noexcept
	{
		typename list<T>::iterator result = first;
		for (auto i = first; i != last; ++i)
		{
			if (*i < *result)
				result = i;
		}
		return result;
	}
}

#endif