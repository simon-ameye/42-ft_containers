
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iterator> 

#include "../map.hpp"
#include "../map_iterator.hpp"
#include "../map_reverse_iterator.hpp"
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
	return (0);
}