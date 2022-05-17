
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator> 

#include "../map.hpp"
#include "../map_iterator.hpp"
#include "test_utils/test_utils.hpp"

#include "test_utils/test_utils.hpp"
#include "map_tests.hpp"

#define T1 int
#define T2 int
typedef NAMESPACE::map<T1, T2>::value_type T3;
typedef NAMESPACE::map<T1, T2>::iterator			ft_iterator;
typedef NAMESPACE::map<T1, T2>::const_iterator		ft_const_iterator;
typedef NAMESPACE::map<T1, T2>			maptype;

static int iter = 0;

std::string	printPair(const ft_iterator &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

std::string	printPair(const ft_const_iterator &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

void	printSize(maptype &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << "not ploted" << std::endl;
	if (print_content)
	{
		ft_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <class Key, class T>
void	print(NAMESPACE::map<Key, T>& lst)
{
	std::cout << "printing a map : \n";
	for (typename NAMESPACE::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

void	ft_bound(maptype &mp, const T1 &param)
{
	ft_iterator ite = mp.end(), it[2];
	NAMESPACE::pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

void	ft_const_bound(const maptype &mp, const T1 &param)
{
	ft_const_iterator ite = mp.end(), it[2];
	NAMESPACE::pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		map_custom_2(void)
{
	{
		std::cout << "######################################################" << std::endl;
		std::cout << "map_custom_2" << std::endl;
		std::list<T3> lst;
		unsigned int lst_size = 10;
		for (unsigned int i = 0; i < lst_size; ++i)
			lst.push_back(T3(i + 1, (i + 1) * 3));
		NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
		printSize(mp);

		ft_const_bound(mp, -10);
		ft_const_bound(mp, 1);
		ft_const_bound(mp, 5);
		ft_const_bound(mp, 10);
		ft_const_bound(mp, 50);

		printSize(mp);

		mp.lower_bound(3)->second = 404;
		mp.upper_bound(7)->second = 842;
		ft_bound(mp, 5);
		ft_bound(mp, 7);

		printSize(mp);
	}
	{


		NAMESPACE::map<std::string, int> mymap;
		print(mymap);

		std::cout << "mymap<" << "std::string" << ", " << "int" <<"> mymap;" << std::endl;

		std::cout << std::endl;
		std::cout << "mymap.max_size(): " << (mymap.max_size() > 10000) << std::endl;
		print(mymap);
		std::cout << std::endl;


		print(mymap);
		mymap.insert(NAMESPACE::pair<std::string, int>("ft", 42));

		print(mymap);
		mymap.insert(NAMESPACE::pair<std::string, int>("one", 1));


		std::cout << "# testing upper/lower_bound" << std::endl;
		NAMESPACE::map<std::string, int>::iterator mit;
		NAMESPACE::map<std::string, int>::iterator it;
		print(mymap);
		it = mymap.lower_bound("aaa");
		print(mymap);
		std::cout << "mymap.lower_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;
		std::cout << std::endl;
		print(mymap);
		it = mymap.lower_bound("one");
		print(mymap);
		std::cout << "mymap.lower_bound(\"one\"): " << it->first << ":" << it->second << std::endl;
		std::cout << std::endl;
		print(mymap);
		it = mymap.lower_bound("oae");
		print(mymap);
		std::cout << "mymap.lower_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;
		std::cout << std::endl;
		print(mymap);
		it = mymap.lower_bound("ft");
		print(mymap);
		std::cout << "mymap.lower_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;
		std::cout << std::endl;
		print(mymap);
		it = mymap.lower_bound("zzz");
		print(mymap);
		
		if (it == mymap.end())
			std::cout << "mymap.lower_bound(\"zzz\"): mymap.end()" << std::endl;
		std::cout << std::endl;
		print(mymap);
		it = mymap.upper_bound("aaa");
		
		print(mymap);
		std::cout << "mymap.upper_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;;
		std::cout << std::endl;
		print(mymap);
		it = mymap.upper_bound("oae");
		print(mymap);
		std::cout << "mymap.upper_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;;
		std::cout << std::endl;
		print(mymap);
		it = mymap.upper_bound("one");
		
		if (it == mymap.end())
			std::cout << "mymap.upper_bound(\"one\"): mymap.end()" << std::endl;
		print(mymap);
		std::cout << std::endl;
		it = mymap.upper_bound("ft");
		print(mymap);
		std::cout << "mymap.upper_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;;
		std::cout << std::endl;
		print(mymap);
		it = mymap.upper_bound("zzz");
		
		if (it == mymap.end())
			std::cout << "mymap.upper_bound(\"zzz\"): mymap.end()" << std::endl;
		print(mymap);
		std::cout << std::endl;

		print(mymap);
		mymap.erase("undefined");
		print(mymap);
		mymap.erase("ft");
		print(mymap);
		std::cout << "# double clear" << std::endl;
		mymap.clear();
		mymap.print_tree();

		print(mymap);
		mymap.clear();
		print(mymap);
		mymap["lol"];
		print(mymap);
		mymap.insert(pair<std::string, int>("xD", 123));
		print(mymap);
		mymap.insert(mymap.end(), pair<std::string, int>("uch", 442));
		print(mymap);
		mymap.insert(mymap.begin(), pair<std::string, int>("uch", 22));
		print(mymap);
		mymap.insert(mymap.end(), pair<std::string, int>("uch", 23));
		print(mymap);
		mymap.insert(pair<std::string, int>("uch", 23));
		print(mymap);
		mymap["lol"] = 8;


		print(mymap);
		map<std::string, int> map2;

		print(mymap);
		print(map2);
		std::cout << "mymap<" << "std::string" << ", " << "int" <<"> mymap2;" << std::endl;
		print(mymap);
		std::cout << "empty line\n";
		print(map2);
		std::cout << "empty line2\n";

		swap(mymap, map2);
		std::cout << "empty line3\n";
		print(mymap);
		std::cout << "empty line4\n";
		print(map2);
		std::cout << "empty line5\n";

		mymap = map2;
		print(mymap);
		print(map2);

		std::cout << "map == map2: " << (mymap == map2) << std::endl;
		print(mymap);
		print(map2);
		std::cout << std::endl;

		mymap.clear();
		print(mymap);
		print(map2);

		mymap["satan"] = 666;
		print(mymap);
		print(map2);
		std::cout << "mymap == map2: " << (mymap == map2) << std::endl;
		print(mymap);
		print(map2);
		std::cout << std::endl;
		std::cout << "mymap <= map2: " << (mymap <= map2) << std::endl;
		print(mymap);
		print(map2);
		std::cout << std::endl;
		std::cout << "mymap >= map2: " << (mymap >= map2) << std::endl;
		print(mymap);
		print(map2);
		std::cout << std::endl;
		std::cout << "mymap > map2: " << (mymap > map2) << std::endl;
		print(mymap);
		print(map2);
		std::cout << std::endl;
		std::cout << "mymap < map2: " << (mymap > map2) << std::endl;
		print(mymap);
		print(map2);
		std::cout << std::endl;
	}
	return (0);
}