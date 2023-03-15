#!bin/bash

assert()
{
	printf '%-30s:' "\"$1\""

	echo -n -e "$1" | bash >cmp 2>&-

	expected=$?

	echo -n -e "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	if [ "$actual" = "$expected" ];then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

cat << EOF | gcc -xc -o a.out -
#include <stdio.h>
int main(){ printf("Hello from a.out\n");}
EOF
assert '/bin/ls'
assert '/bin/pwd'
assert 'echo'
assert 'pwd'
assert 'ls'
assert './a.out'
assert 'echo "test"\n1'
assert 'ls -la > test1'
assert 'cat < Makefile >test2 >test3 >test4 '
assert 'cat test4 >>test5 | cat test4 >>test5
assert 'cat test0'
assert 'ls -la | grep test'
assert 'ls -la test0'
assert 'ls | ls |ls |ls |ls |ls |ls | cat < Makefile'
assert 'find . -name "*c" | xargs cat
