
#ifndef TRUEAFALSEB_HPP
#define TRUEAFALSEB_HPP
namespace ft
{
	template <bool Const, typename A, typename B>
	struct TrueAFalseB {};

	template <typename A, typename B>
	struct TrueAFalseB<true, A, B>
	{ typedef A type; };

	template <typename A, typename B>
	struct TrueAFalseB<false, A, B>
	{ typedef B type; };
}

#endif
