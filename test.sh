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
