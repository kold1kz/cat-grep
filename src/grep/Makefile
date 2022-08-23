CFLAGS= -Wall -Wextra -Werror -std=c11
LDFLAGS=-Wall -Wextra -Werror





all: s21_grep test

s21_grep:
	gcc $(CFLAGS) ../grep/s21_grep.c -o s21_grep



rebuild: clean s21_grep


clean:

	rm -f s21_grep
	rm -f test
	rm -f *.a *.o
	rm -f *_tests
	rm -f *.info *.gcda *.gcno *.gcov *.swp


	 
#  diff -s prov.txt prov1.txt

test: s21_grep

	./s21_grep asd ../checktests/test0.txt > prov.txt
	grep asd ../checktests/test0.txt > prov1.txt
	diff -s prov.txt prov1.txt

	./s21_grep "^[a-f]" ../checktests/test1.txt > prov.txt
	grep "^[a-f]" ../checktests/test1.txt > prov1.txt
	diff -s prov.txt prov1.txt

	./s21_grep asd ../checktests/test0.txt ../checktests/test4.txt > prov.txt
	grep asd ../checktests/test0.txt ../checktests/test4.txt > prov1.txt
	diff -s prov.txt prov1.txt

	./s21_grep "^[a-f]" ../checktests/test1.txt ../checktests/test5.txt > prov.txt
	grep "^[a-f]" ../checktests/test1.txt ../checktests/test5.txt > prov1.txt
	diff -s prov.txt prov1.txt

	./s21_grep -v the ../checktests/test2.txt > prov.txt
	grep -v the ../checktests/test2.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -v the ../checktests/test2.txt ../checktests/test3.txt > prov.txt
	grep -v the ../checktests/test2.txt ../checktests/test3.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -i license ../checktests/test2.txt > prov.txt
	grep -i license ../checktests/test2.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -i license ../checktests/test2.txt ../checktests/test3.txt > prov.txt
	grep -i license ../checktests/test2.txt ../checktests/test3.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -c license ../checktests/test2.txt > prov.txt
	grep -c license ../checktests/test2.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -c license ../checktests/test2.txt ../checktests/test3.txt > prov.txt
	grep -c license ../checktests/test2.txt ../checktests/test3.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -e asd -e fi ../checktests/test0.txt > prov.txt
	grep -e asd -e fi ../checktests/test0.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -e asd -e fi ../checktests/test0.txt ../checktests/test4.txt > prov.txt
	grep -e asd -e fi ../checktests/test0.txt ../checktests/test4.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -l asd ../checktests/test0.txt > prov.txt
	grep -l asd ../checktests/test0.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -l asd ../checktests/test0.txt ../checktests/test4.txt > prov.txt
	grep -l asd ../checktests/test0.txt ../checktests/test4.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -n asd ../checktests/test0.txt > prov.txt
	grep -n asd ../checktests/test0.txt > prov1.txt
	diff -s prov.txt prov1.txt
	
	./s21_grep -n asd ../checktests/test0.txt ../checktests/test4.txt > ../cat/prov.txt
	grep -n asd ../checktests/test0.txt ../checktests/test4.txt > prov1.txt
	diff -s ../cat/prov.txt prov1.txt
