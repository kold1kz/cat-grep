CFLAGS= -Wall -Wextra -Werror -std=c11
LDFLAGS=-Wall -Wextra -Werror





all: s21_cat test


s21_cat:
	gcc $(CFLAGS) s21_cat.c -o s21_cat

rebuild: clean s21_cat 


clean:
	rm -f s21_cat
	rm -f test
	rm -f *.a *.o
	rm -f *_tests
	rm -f *.info *.gcda *.gcno *.gcov *.swp


	 
#  diff -s prov_c.txt prov_c1.txt

test: s21_cat 

	./s21_cat ../checktests/test0.txt > prov_c.txt
	cat ../checktests/test0.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -b ../checktests/test1.txt > prov_c.txt
	cat -b ../checktests/test1.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -e ../checktests/test2.txt > prov_c.txt
	cat -e ../checktests/test2.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -n ../checktests/test3.txt > prov_c.txt
	cat -n ../checktests/test3.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -s ../checktests/test4.txt > prov_c.txt
	cat -s ../checktests/test4.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -t ../checktests/test5.txt > prov_c.txt
	cat -t ../checktests/test5.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -e ../checktests/test2.txt ../checktests/test3.txt > prov_c.txt
	cat -e ../checktests/test2.txt ../checktests/test3.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -b ../checktests/test2.txt ../checktests/test3.txt > prov_c.txt
	cat -b ../checktests/test2.txt ../checktests/test3.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -n ../checktests/test2.txt ../checktests/test3.txt > prov_c.txt
	cat -n ../checktests/test2.txt ../checktests/test3.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -s ../checktests/test2.txt ../checktests/test3.txt > prov_c.txt
	cat -s ../checktests/test2.txt ../checktests/test3.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	./s21_cat -t ../checktests/test2.txt ../checktests/test3.txt > prov_c.txt
	cat -t ../checktests/test2.txt ../checktests/test3.txt > prov_c1.txt
	diff -s prov_c.txt prov_c1.txt

	