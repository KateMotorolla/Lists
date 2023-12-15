#include "list.hpp"
#include "stack.hpp"
#include "graph.hpp"

int main()
{
	srand(time(NULL));

	// Task #1 - Lists merge
	lab::list<int> test_1, test_2;
	for (int i = 0; i < rand() % 10 + 1; ++i)
		test_1.push_back(rand() % 10);
	test_1.sort();
	for (int i = 0; i < rand() % 10 + 1; ++i)
		test_2.push_back(rand() % 10);
	test_2.sort();
	std::cout << "Lists merge: " << std::endl;
	std::cout << "List 1: ";
	for (auto e : test_1)
		std::cout << e << "  ";
	std::cout << std::endl << "List 2: ";
	for (auto e : test_2)
		std::cout << e << "  ";
	test_1.merge(std::move(test_2));
	std::cout << std::endl << "Merged: ";
	for (auto e : test_1)
		std::cout << e << "  ";
	std::cout << std::endl << std::endl;

	// Task #2 - Exchange of min & max element from list
	lab::list<int> test_3;
	for (int i = 0; i < rand() % 10 + 1; ++i)
		test_3.push_back(rand() % 10);
	std::cout << "Exchange of min & max element from list" << std::endl;
	std::cout << "List: ";
	for (auto e : test_3)
		std::cout << e << "  ";
	auto min_it = lab::min_element<int>(test_3.begin(), test_3.end());
	auto max_it = lab::max_element<int>(test_3.begin(), test_3.end());
	test_3.exchange(min_it, max_it);
	std::cout << std::endl << "After exchange: ";
	for (auto e : test_3)
		std::cout << e << "  ";
	std::cout << std::endl << std::endl;

	// Task #3 - Stack on list
	lab::stack<int> test_4;
	lab::list<int> seq;
	for (int i = 0; i < rand() % 10 + 1; ++i)
		seq.push_back(rand() % 10);
	std::cout << "Stack on list" << std::endl;
	std::cout << "Sequence to fill stack: ";
	for (auto e : seq)
		std::cout << e << "  ";
	std::cout << std::endl << "Fill stack (push operation): ";
	for (auto e : seq)
	{
		test_4.push(e);
		std::cout << "State of stack: ";
		for (auto s : test_4.get_container())
			std::cout << s << "  ";
		std::cout << std::endl;
	}
	std::cout << "Cleaning stack (pop operation): ";
	while (!test_4.empty())
	{
		test_4.pop();
		std::cout << "State of stack: ";
		for (auto s : test_4.get_container())
			std::cout << s << "  ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Task #4 - Simple insertion sort on list
	lab::list<int> test_5;
	for (int i = 0; i < rand() % 10 + 1; ++i)
		test_5.push_back(rand() % 10);
	std::cout << "Simple insertion sort" << std::endl;
	std::cout << "Befor sort: ";
	for (auto e : test_5)
		std::cout << e << "  ";
	test_5.sort();
	std::cout << std::endl << "After sort:";
	for (auto e : test_5)
		std::cout << e << "  ";
	std::cout << std::endl << std::endl;

	// Task #5 DFS & BFS
	lab::graph<5> test_6;
	std::cout << "DFS & BFS" << std::endl;
	std::cout << "Matrix: " << std::endl;
	test_6.print();
	unsigned int begin_vertex = rand() % 5;
	std::cout << "begin vertex is " << begin_vertex << std::endl;
	std::cout << "DFS: ";
	for (auto e : test_6.get_dfs_order(begin_vertex))
		std::cout << e << "  ";
	std::cout << std::endl << "BFS: ";
	for (auto e : test_6.get_bfs_order(begin_vertex))
		std::cout << e << "  ";
	std::cout << std::endl;


	return 0;
}