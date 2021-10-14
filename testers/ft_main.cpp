/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:35:52 by mbani             #+#    #+#             */
/*   Updated: 2021/10/14 11:13:58 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <time.h>
#if NS
#include "../headers/Vector.hpp"
#include "../headers/stack.hpp"
#else
#include <vector>
#include <stack>
namespace ft = std;
#endif

	// helper functions 
bool mypredicate (int i, int j)
	{return (i==j);}

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }


void print_vector(ft::vector<int>::iterator ft_it_b, ft::vector<int>::iterator ft_it_e)
{
	std::cout << "ft  :: ";
	for(; ft_it_b != ft_it_e ; ++ft_it_b)
	 {
		std:: cout << *ft_it_b << " ";
	 }
	std::cout << std::endl;
}

int main(void)
{
	clock_t start = clock();
	
    	std::cout << "	======================>\033[1;31m init and iterators tests \033[0m<============================ " << std::endl;
	// Creating vects of diffrent types

	ft::vector<int> ft_vect_int; // call default constructor 
	ft::vector<int> vect_1(10, 5); // call fill constructor
	ft::vector<char> ft_vect_char(5, 'a');
	ft::vector<float> ft_vect_float;ft::vector<int>::iterator ft_it;
	ft::vector<char>::iterator ft_it_char(ft_vect_char.begin());
	ft::vector<int>::const_iterator ft_itc(vect_1.end());

	(void)ft_it_char;
	// std_it = ft_itc;
	ft_itc = ft_it;

	// *ft_itc = 8;
	// *std_itc = 8;

	// std::cout << (ft_itc == ft_it) << std::endl;
	// std::cout << (ft_itc != ft_it) << std::endl << std::endl;

	for(int i = 0; i < 10; ++i)
		ft_vect_int.push_back(i);
	ft::vector<int> ft_vect_int1(ft_vect_int.begin(), ft_vect_int.end()); // call range constructor 

	ft_it = ft_vect_int1.begin();
	for(ft_it = ft_vect_int1.begin(); ft_it != ft_vect_int1.end(); ++ft_it)
		std::cout << *ft_it << std::endl;


	std::cout << "	======================>\033[1;31m member functions tests \033[0m<============================ " << std::endl;

	std::cout << ft_vect_int.max_size() << std::endl;

	ft::vector<int> ft_vect_int2; 
	for(int i = 0; i < 100; i += 20)
		ft_vect_int2.push_back(i);
	std::cout << "Capacity: " << ft_vect_int2.capacity() << std::endl;
	
	print_vector(ft_vect_int2.begin(), ft_vect_int2.end());

	ft_vect_int2.reserve(50);

	std::cout << "Capacity: " << ft_vect_int2.capacity() << std::endl;
	
	print_vector(ft_vect_int2.begin(), ft_vect_int2.end());
	try
	{
	// ft_vect_int2.reserve(4611686018427387999);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	std::cout << "Capacity:  " << ft_vect_int2.capacity() << std::endl;

	ft_vect_int1[8] = 19;
	std::cout << ft_vect_int1[8] << std::endl;
	
	ft_vect_int1[0] = 100;
	std::cout << ft_vect_int1.back() << std::endl;

	ft::vector<int> ft_new(25, 0);
	
	std::cout << "vect 2 Capacity : " << ft_vect_int2.capacity() << std::endl;

	ft_new.assign(ft_vect_int2.begin(), ft_vect_int2.end());

	std::cout << "Capacity:  : " << ft_new.capacity() << std::endl;
	std::cout << "Size: " << ft_new.size() << std::endl;

	print_vector(ft_new.begin(), ft_new.end());

	ft_new.assign(10, 0);

	print_vector(ft_new.begin(), ft_new.end());
	
	std::cout << "Capacity:  : " << ft_new.capacity() << std::endl;
	std::cout << "Size: " << ft_new.size() << std::endl;
	
	ft_new.assign(20, 1);
	
	print_vector(ft_new.begin(), ft_new.end());
	
	std::cout << "Capacity:  : " << ft_new.capacity() << std::endl;
	std::cout << "Size: " << ft_new.size() << std::endl;

	ft::vector<int> ft_new1(10, 0);

	// ft_new1.reserve(100);
	for (int i = 0; i < 2; ++i)
		ft_new1.push_back(i);
	print_vector(ft_new1.begin(), ft_new1.end());
	std::cout << "Capacity:  : " << ft_new1.capacity() << std::endl;
	std::cout << "Size: " << ft_new1.size() << std::endl;

	ft::vector<int> ft_new2;
	std::cout << std::endl;
	ft::vector<int>::iterator ft_it2(ft_new2.begin());
	

	ft_new2.insert(ft_it2, 900);
	ft_it2++;
	std::cout << std::endl;
	ft_it2 = ft_new2.begin();
	ft_new2.insert(ft_it2, 100);
	ft_it2 = ft_new2.begin();
	ft_new2.insert(ft_it2, 10);
	ft_it2 = ft_new2.begin();
	ft_new2.insert(ft_it2, 20);
	// ft_it2--;
	ft_it2 = ft_new2.end();
	// ft_it2++;
	std::cout << *(ft_new2.insert(ft_it2, 800))<< std::endl;
	print_vector(ft_new2.begin(), ft_new2.end());
	std::cout << "ft capacity : " << ft_new2.capacity() << std::endl;
	std::cout << "ft size :" << ft_new2.size() << std::endl << std::endl;

	print_vector(ft_new2.begin(), ft_new2.end());
	ft_it2 = ft_new2.begin();
	// ft_it2--;

	ft_new2.insert(ft_it2, 1, 55);
		print_vector(ft_new2.begin(), ft_new2.end());
	ft_it2 = ft_new2.begin();
	ft_it2++;
	ft_new2.insert(ft_it2, 190);
	print_vector(ft_new2.begin(), ft_new2.end());
	std::cout << "ft capacity :  " << ft_new2.capacity() << std::endl;
	std::cout << "ft size :      " << ft_new2.size() << std::endl << std::endl;
	

	ft::vector<int> ft_new3(1, 0);
	ft_new3.reserve(10);
	ft_new3.push_back(10);
	ft_new3.push_back(20);
	ft_new3.push_back(30);
	ft_new3.push_back(40);
	ft_new3.insert(ft_new3.begin(), ft_new2.begin(), ft_new2.end());

	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl << std::endl;

	// std::cout << *(ft_new3.erase(ft_new3.end()  - 3)) << std::endl;
	std::cout << *(ft_new3.erase(ft_new3.begin() + 3, ft_new3.end())) << std::endl;

	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl << std::endl;

	std::cout << "iter " << ft_new3.end() - ft_new3.begin() << std::endl;

	ft::vector<int> ft_new4(20, 0);
	ft_new4 = ft_new3;
	std::cout << "print new4" << std::endl << std::endl;
	print_vector(ft_new4.begin(), ft_new4.end());
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;






	ft_new3.push_back(3333);
	ft_new3.push_back(20);
	ft_new3.push_back(30);
	ft_new3.push_back(3333);
	ft_new3.swap(ft_new4);
	std::cout << std::endl;
	print_vector(ft_new4.begin(), ft_new4.end());
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;
	std::cout << "print new3" << std::endl << std::endl;
	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl;

	ft_new4.clear();
	print_vector(ft_new4.begin(), ft_new4.end());
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;
	
	std::cout << std::endl;
	print_vector(ft_new3.begin(), ft_new3.end());
	print_vector(ft_new2.begin(), ft_new2.end());
	ft::swap(ft_new3, ft_new2);
	std::cout << std::endl;
	print_vector(ft_new3.begin(), ft_new3.end());
	print_vector(ft_new2.begin(), ft_new2.end());
	std::cout <<  "ft size :" << ft_new3.size() << "\nft capacity : " << ft_new3.capacity() << std::endl;
	ft_new3.resize(12, 10);
	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout <<  "ft size :" << ft_new3.size() << "\nft capacity : " << ft_new3.capacity() << std::endl;
	ft_new3.resize(13, 6);
	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft size :" << ft_new3.size() << "\nft capacity : " << ft_new3.capacity() << std::endl;

std::cout << "	======================>\033[1;31m Non-member functions tests \033[0m<============================ " << std::endl << std::endl;
	ft::vector<int> foo (3,200);
	ft::vector<int> bar (3,300);

	if (foo == bar)
		std::cout << "equal\n";
	if (foo != bar)
		std::cout << "not equal \n";
	if (foo < bar)
		std::cout << "foo is less than bar" << std::endl;
	if (foo <= bar)
		std::cout << "foo is less than or equal bar" << std::endl;
	if (bar > foo)
		std::cout << "bar is greater than foo" << std::endl;
	if (foo >= bar)
		std::cout << "foo is greater than or equal bar" << std::endl;

	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n"<< std::endl;
  char foo1[]="Apple";
  char bar1[]="apartment";

  std::cout << std::boolalpha;

  std::cout << "Comparing foo1 and bar1 lexicographically (foo1<bar1):\n";

  std::cout << "Using default comparison (operator<): ";
  std::cout << ft::lexicographical_compare(foo1,foo1+5,bar1,bar1+9);
  std::cout << '\n';

  std::cout << "Using mycomp as comparison object: ";
  std::cout << ft::lexicographical_compare(foo1,foo1+5,bar1,bar1+9,mycomp);
  std::cout << std::endl;

std::cout << "	======================>\033[1;31m iteartors && rev_iterators arithmetic operations tests \033[0m<============================ " << std::endl << std::endl;
	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft::size  :" <<ft_new3.size() << " ft::capacity  :" << ft_new3.capacity() << std::endl<< std::endl;

	ft::vector<int>::iterator ft_it3(ft_new3.begin());

	std::cout << *(4 + ft_it3) << std::endl;
	std::cout << *ft_it3++ << std::endl;
	std::cout << *(ft_it3 + 2) << std::endl;	
	std::cout << *ft_it3 << std::endl;
	std::cout << *(ft_it3 += 1) << std::endl;	
	std::cout << *ft_it3 << std::endl;

	
	std::cout << std::endl;
	ft_it3 = ft_new3.end();
	--ft_it3;
	ft_it3--;
	std::cout << *ft_it3-- << std::endl;
	std::cout << *(ft_it3 - 6) << std::endl;	
	std::cout << *ft_it3 << std::endl;
	std::cout << *(ft_it3 -= 9) << std::endl;	
	std::cout << *ft_it3 << std::endl;
	ft_it3 = ft_new3.begin();
	std::cout << (ft_new3.end() - ft_it3) << std::endl;
	
	std::cout << std::endl;
	std::cout << (ft_it3 < ft_new3.end()) << std::endl;
	std::cout << (ft_it3 > ft_new3.end()) << std::endl;
	std::cout << (ft_it3 <= ft_new3.end()) << std::endl;
	std::cout << (ft_it3 >= ft_new3.end()) << std::endl;
	std::cout << *(ft_it3.base()) << std::endl;
	std::cout << ft_it3[4] << std::endl;


	std::cout << std::endl;
	ft::vector<int>::reverse_iterator ft_rit3(ft_new3.end() - 1);
	std::cout << *ft_rit3 << std::endl;
	ft_rit3 = ft_new3.rbegin();
	std::cout << *ft_rit3 << std::endl;	
	std::cout << *(ft_rit3 + 8) << std::endl;
	++ft_rit3;
	ft_rit3++;
	std::cout << *ft_rit3 << std::endl;
	ft_rit3 += 5;
	std::cout << *ft_rit3 << std::endl;
	std::cout << *(ft_rit3 - 1) << std::endl;	
	std::cout << *ft_rit3-- << std::endl;
	std::cout << *--ft_rit3 << std::endl;
	std::cout << *ft_rit3 << std::endl;
	std::cout << *(ft_rit3 -= 5) << std::endl;

	
	std::cout << std::endl;

	ft_rit3 = ft_new3.rend();
	std::cout << ft_rit3[1] << std::endl;


	
	std::cout << *(ft_new3.rend() - 2) << std::endl;
	ft::vector<int>::const_reverse_iterator ft_crit3(ft_new3.end() - 1);

	std::cout << *ft_crit3 << std::endl;

	// *std_crit3 = 8;
	// *ft_crit3 = 8;

	std::cout << std::endl;

	std::cout << (ft_rit3 < ft_new3.rend()) << std::endl;
	std::cout << (ft_rit3 <= ft_new3.rend()) << std::endl;
	std::cout << (ft_rit3 > ft_new3.rend()) << std::endl;
	std::cout << (ft_rit3 >= ft_new3.rend()) << std::endl;
	std::cout << (ft_rit3 != ft_new3.rend()) << std::endl;
	std::cout << (ft_rit3 == ft_new3.rend()) << std::endl;

	ft_rit3 = ft_new3.rbegin();
	std::cout << *(8 + ft_rit3) << std::endl;

	std::cout << ft_new3.rbegin() - ft_new3.rend() << std::endl;


	std::cout.precision(10);
	std::cout << std::fixed <<  float(clock() - start)/CLOCKS_PER_SEC  << std::endl;


	std::cout << "	======================>\033[1;31m STACK tests \033[0m<============================ " << std::endl << std::endl;

	ft::stack<int> st;
	ft::stack<int> st2(st);
	st.push(10);
	st.push(20);
	st.push(30);
	st.push(40);

	for(size_t i = 0; i < st.size(); ++i)
	{
		std::cout << st.top() << std::endl;
	}

	std::cout << st2.empty() << std::endl;

	st.pop();
	st.pop();
	st.pop();
	
	st.push(200);
	st.push(300);
	st.push(400);

	for(size_t i = 0; i < st.size(); ++i)
		std::cout << st.top()<< std::endl;

	// std::cout << std::endl;

	std::cout << " equal " << (st2 == st) << std::endl;

	std::cout << " diff " << (st2 != st) << std::endl;

	std::cout << " >>>> "<<(st2 > st) << std::endl;
	std::cout << " >= " << (st2 >= st) << std::endl;
	std::cout << (st2 < st) << std::endl;
	std::cout << (st2 <= st) << std::endl;

	std::cout << (st > st2) << std::endl;
	std::cout << (st >= st2) << std::endl;
	std::cout << (st < st2) << std::endl;
	std::cout << (st <= st2) << std::endl;
	system("leaks a.out");
}
