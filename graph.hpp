#ifndef _LAB_GRAPHS
#define _LAB_GRAPHS

#include <array>
#include <random>
#include "stack.hpp"

namespace lab
{
	template <unsigned int n>
	class graph final
	{
	private:
		std::array<int, n * n> matrix;

		void dfs(unsigned int index, stack<unsigned int>& result,
			std::array<bool, n>& used) const noexcept
		{
			result.push(index);
			used[index] = true;
			for (int i = index + 1; i < n; ++i)
			{
				if (matrix[i + index * n] && !used[i])
					dfs(i, result, used);
			}
		}

		void bfs(unsigned int index, queue<unsigned int>& current,
			stack<unsigned int>& result, std::array<bool, n>& used) const noexcept
		{
			result.push(index);
			used[index] = true;
			current.pop();
			for (int i = index + 1; i < n; ++i)
			{
				if (matrix[i + index * n] && !used[i])
					current.push(i);
			}
			if (!current.empty())
				bfs(current.top(), current, result, used);
		}
	public:
		graph() noexcept
		{
			srand(time(NULL));
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
					matrix[j + i * n] = rand() % 2;
				matrix[i + i * n] = 0;
			}
		}

		void print() const noexcept
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
					std::cout << matrix[j + i * n] << "  ";
				std::cout << std::endl;
			}
		}

		list<unsigned int> get_dfs_order(unsigned int first) const
		{
			stack<unsigned int> result;
			std::array<bool, n> used { false };
			dfs(first, result, used);
			return result.get_container();
		}

		list<unsigned int> get_bfs_order(unsigned int first) const
		{
			stack<unsigned int> result;
			queue<unsigned int> current;
			std::array<bool, n> used { false };
			bfs(first, current, result, used);
			return result.get_container();
		}
	};
}

#endif
