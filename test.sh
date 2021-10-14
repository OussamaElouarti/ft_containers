g++ -std=c++98   ft_main.cpp -D NS=0 && ./a.out > std_tst
rm a.out
g++ -std=c++98   ft_main.cpp -D NS=1 && ./a.out > ft_tst
rm a.out
diff std_tst ft_tst
rm ft_tst std_tst