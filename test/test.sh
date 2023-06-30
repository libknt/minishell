#!/bin/bash
cp ../minishell ./
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

cat <<EOF | gcc -xc -o exit42 -
int main() { return 42; }
EOF

print_desc() {
	echo -e $YELLOW"$1"$RESET
}

cleanup() {
	rm -f cmp out a.out print_args exit42 infinite_loop no_exec_perm no_read_perm minishell perm.out
}

assert() {
	COMMAND="$1"
	shift
	printf '%-60s:' "[$COMMAND]"
	# exit status
	echo -n -e "$COMMAND" | bash >cmp 2>&-
	expected=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
	done
	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	actual=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".out"
	done

	echo -n -e "COMMAND\n"  >> result
	echo -n -e "$COMMAND\n" >> result
	echo -n -e "RESULT\n"	>> result
	diff cmp out >> result && echo -e -n "  diff $OK" || echo -e -n "  diff $NG"

	if [ "$actual" = "$expected" ]; then
		echo -e -n "  status $OK"
	else
		echo -e -n "  status $NG, expected $expected but got $actual"
	fi
	for arg in "$@"
	do
		echo -n "  [$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
		rm -f "$arg"".cmp" "$arg"".out"
	done
	echo
}

# # Empty line (EOF)
# assert ''

# # Absolute path commands without args 
# assert '/bin/pwd'
# assert '/bin/echo'
# assert '/bin/ls'

# # Search command path without args
# assert 'pwd'
# assert 'echo'
# assert 'ls'
# assert './a.out'

# # no such command
# assert 'a.out'
# assert 'nosuchfile'

# ## command not found
# assert '""'
# # assert '.' # . is a builtin command in bash
# assert '..'

# ## is a directory
# assert './'
# assert '/'
# assert '/etc'
# assert '/etc/'
# assert '////'

# ## Permission denied
# echo "int main() { }" | gcc -xc -o no_exec_perm -
# chmod -x no_exec_perm
# assert 'no_exec_perm'
# assert './no_exec_perm'
# echo "int main() { }" | gcc -xc -o no_read_perm -
# chmod -r no_read_perm
# assert 'no_read_perm'
# assert './no_read_perm'

# mkdir -p /tmp/a /tmp/b
# echo "int main() { return 1; }" | gcc -xc -o /tmp/a/simple_test -
# echo "int main() { return 2; }" | gcc -xc -o /tmp/b/simple_test -

# print_desc "/tmp/a /tmp/b both with permission"
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

# print_desc "/tmp/a /tmp/b both without permission"
# chmod -x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

# print_desc "a with permission, b without permission"
# chmod +x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

# print_desc "a without permission, b with permission"
# chmod -x /tmp/a/simple_test; chmod +x /tmp/b/simple_test;
# assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
# assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

# # Tokenize
# ## unquoted word
# assert 'ls /'
# assert 'echo hello    world     '
# assert 'nosuchfile\n\n'

# ## single quote
# assert "./print_args 'hello   world' '42Tokyo'"
# assert "echo 'hello   world' '42Tokyo'"
# assert "echo '\"hello   world\"' '42Tokyo'"

# ## double quote
# assert './print_args "hello   world" "42Tokyo"'
# assert 'echo "hello   world" "42Tokyo"'
# assert "echo \"'hello   world'\" \"42Tokyo\""

# ## combination
# assert "echo hello'      world'"
# assert "echo hello'  world  '\"  42Tokyo  \""

# # Redirect
# ## Redirecting output
# assert 'echo hello >hello.txt' 'hello.txt'
# assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

# ## Redirecting input
# assert 'cat <Makefile'
# echo hello >f1
# echo world >f2
# echo 42Tokyo >f3
# assert 'cat <f1<f2<f3'
# rm -f f1 f2 f3
# assert 'cat <hoge'

# ## Appending Redirected output
# assert 'pwd >>pwd.txt' 'pwd.txt'
# assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

# # Here Document
# assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
# assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
# assert 'cat <<EOF\nhello\nworld'
# assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
# assert 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
# assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
# assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
# export EOF="eof"
# assert 'cat <<$EOF         \neof\n$EOF\nEOF'
# assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'

# # Pipe
# assert 'cat Makefile | grep minishell'
# assert 'cat | cat | ls\n\n'

# # Expand Variable
# assert 'echo $USER'
# assert 'echo $USER$PATH$TERM'
# assert 'echo "$USER  $PATH   $TERM"'

# # Special Parameter $?
# assert 'echo $?'
# assert 'invalid\necho $?\necho $?'
# assert 'exit42\necho $?\necho $?'
# assert 'exit42\n\necho $?\necho $?'

# # Signal handling
# echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

# # # Signal to shell processes
# # print_desc "SIGTERM to SHELL"
# # (sleep 0.01; pkill -SIGTERM bash;
# #  sleep 0.01; pkill -SIGTERM minishell) &
# # assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

# # print_desc "SIGQUIT to SHELL"
# # (sleep 0.01; pkill -SIGQUIT bash; # SIGQUIT should not kill the shell
# #  sleep 0.01; pkill -SIGTERM bash;
# #  sleep 0.01; pkill -SIGQUIT minishell; # SIGQUIT should not kill the shell
# #  sleep 0.01; pkill -SIGTERM minishell) &
# # assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

# # print_desc "SIGINT to SHELL"
# # (sleep 0.01; pkill -SIGINT bash; # SIGINT should not kill the shell
# #  sleep 0.01; pkill -SIGTERM bash;
# #  sleep 0.01; pkill -SIGINT minishell; # SIGINT should not kill the shell
# #  sleep 0.01; pkill -SIGTERM minishell) &
# # assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

# # ## Signal to child processes
# # print_desc "SIGTERM to child process"
# # (sleep 0.01; pkill -SIGTERM infinite_loop;
# #  sleep 0.01; pkill -SIGTERM infinite_loop) &
# # assert './infinite_loop'

# # print_desc "SIGINT to child process"
# # (sleep 0.01; pkill -SIGINT infinite_loop;
# #  sleep 0.01; pkill -SIGINT infinite_loop) &
# # assert './infinite_loop'

# # print_desc "SIGQUIT to child process"
# # (sleep 0.01; pkill -SIGQUIT infinite_loop;
# #  sleep 0.01; pkill -SIGQUIT infinite_loop) &
# # assert './infinite_loop'

# # print_desc "SIGUSR1 to child process"
# # (sleep 0.01; pkill -SIGUSR1 infinite_loop;
# #  sleep 0.01; pkill -SIGUSR1 infinite_loop) &
# # assert './infinite_loop'

# # Manual Debug
# # $ ./minishell
# # $ 
# # 1. Ctrl-\ 
# # 2. Ctrl-C
# # 3. Ctrl-D

# # $ ./minishell
# # $ hogehoge
# # 1. Ctrl-\ 
# # 2. Ctrl-C
# # 3. Ctrl-D

# # $ ./minishell
# # $ cat <<EOF
# # >
# # 1. Ctrl-\ 
# # 2. Ctrl-C
# # 3. Ctrl-D

# # $ ./minishell
# # $ cat <<EOF
# # > hoge
# # > fuga
# # 1. Ctrl-\ 
# # 2. Ctrl-C
# # 3. Ctrl-D

# Builtin
# ## exit
# assert 'exit'
# assert 'exit 42'
# assert 'exit ""'
# assert 'exit hello'
# assert 'exit 42Tokyo'
# assert 'exit 1 2'

# ## export
# print_desc "Output of 'export' differs, but it's ok."
# assert 'export' # order of variables, default variables differs...
# assert 'export | grep nosuch | sort'
# assert 'export nosuch\n export | grep nosuch | sort'
# assert 'export nosuch=fuga\n export | grep nosuch | sort'
# assert 'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
# assert 'export [invalid]'
# assert 'export [invalid_nosuch]\n export | grep nosuch | sort'
# assert 'export [invalid]=nosuch\n export | grep nosuch | sort'
# assert 'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
# assert 'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
# assert 'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
# assert 'export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort'

# ## unset
# export hoge fuga=fuga
# assert 'unset'
# assert 'unset hoge'
# assert 'unset fuga'
# assert 'unset nosuch'
# assert 'unset [invalid]'
# assert 'unset hoge fuga'
# assert 'unset hoge nosuch fuga'
# assert 'unset fuga \n export | echo $fuga'
# assert 'unset [invalid] fuga \n echo $fuga'

# ## env
# print_desc "Output of 'env' differs, but it's ok."
# assert 'env' # order of variables, default variables differs...
# assert 'env | grep hoge | sort'

# ## cd
# assert 'cd'
# assert 'cd .'
# assert 'cd ..'
# assert 'cd ///'
# assert 'cd /tmp'
# assert 'cd /tmp/'
# assert 'cd /tmp///'
# assert 'cd /../../../././.././'
# assert 'cd src'
# assert 'unset HOME\ncd'

# assert 'cd \n echo $PWD'
# assert 'cd \n echo $PWD'
# assert 'cd .\n echo $PWD'
# assert 'cd ..\n echo $PWD'
# assert 'cd ///\n echo $PWD'
# assert 'cd /tmp\n echo $PWD'
# assert 'cd /tmp/\n echo $PWD'
# assert 'cd /tmp///\n echo $PWD'
# assert 'cd /../../../././.././\n echo $PWD'
# assert 'cd src\n echo $PWD'
# assert 'unset HOME\ncd \n echo $PWD'

# ## echo
# assert 'echo'
# assert 'echo hello'
# assert 'echo hello "    " world'
# assert 'echo -n'
# assert 'echo -n hello'
# assert 'echo -n hello world'
# assert 'echo hello -n'

# ## pwd
# assert 'pwd'
# assert 'cd\npwd'
# assert 'cd src\npwd'
# assert 'cd /etc\npwd'
# assert 'cd . \n pwd \n echo $PWD $OLDPWD'
# assert 'cd . \n pwd \n echo $PWD $OLDPWD'
# assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
# assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
# assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
# assert 'unset PWD\npwd\ncd /etc\npwd'

# ## export attribute
# assert 'unset PWD \n cd \n echo $PWD \ncd /tmp\necho $PWD'
# assert 'unset PWD\ncd\necho $OLDPWD\ncd /tmp\necho $OLDPWD'
# assert 'unset PWD\ncd\nexport|grep PWD\ncd /tmp\nexport|grep PWD'
# assert 'unset PWD\ncd\nenv|grep PWD\ncd /tmp\nenv|grep PWD'


# # cleanup
# assert 'cat <<EOF\nhello\nworld'


# Empty line (EOF)
assert ''

# Absolute path commands without args 
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

## command not found
assert '""'
# assert '.' # . is a builtin command in bash
assert '..'

## is a directory
assert './'
assert '/'
assert '/etc'
assert '/etc/'
assert '////'

## Permission denied
echo "int main() { }" | gcc -xc -o no_exec_perm -
chmod -x no_exec_perm
assert 'no_exec_perm'
assert './no_exec_perm'
echo "int main() { }" | gcc -xc -o no_read_perm -
chmod -r no_read_perm
assert 'no_read_perm'
assert './no_read_perm'

mkdir -p /tmp/a /tmp/b
echo "int main() { return 1; }" | gcc -xc -o /tmp/a/simple_test -
echo "int main() { return 2; }" | gcc -xc -o /tmp/b/simple_test -

print_desc "/tmp/a /tmp/b both with permission"
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "/tmp/a /tmp/b both without permission"
chmod -x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "a with permission, b without permission"
chmod +x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "a without permission, b with permission"
chmod -x /tmp/a/simple_test; chmod +x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

# Tokenize
## unquoted word
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

## single quote
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"

## double quote
assert './print_args "hello   world" "42Tokyo"'
assert 'echo "hello   world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""

## combination
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirected output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

## Here Document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
export EOF="eof"
assert 'cat <<$EOF         \neof\n$EOF\nEOF'
assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'

# Pipe
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'

# Expand Variable
assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER  $PATH   $TERM"'

# Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'

# Signal handling
echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

# ## Signal to shell processes
# print_desc "SIGTERM to SHELL"
# (sleep 0.01; pkill -SIGTERM bash;
#  sleep 0.01; pkill -SIGTERM minishell) &
# assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

# print_desc "SIGQUIT to SHELL"
# (sleep 0.01; pkill -SIGQUIT bash; # SIGQUIT should not kill the shell
#  sleep 0.01; pkill -SIGTERM bash;
#  sleep 0.01; pkill -SIGQUIT minishell; # SIGQUIT should not kill the shell
#  sleep 0.01; pkill -SIGTERM minishell) &
# assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

# print_desc "SIGINT to SHELL"
# (sleep 0.01; pkill -SIGINT bash; # SIGINT should not kill the shell
#  sleep 0.01; pkill -SIGTERM bash;
#  sleep 0.01; pkill -SIGINT minishell; # SIGINT should not kill the shell
#  sleep 0.01; pkill -SIGTERM minishell) &
# assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

# ## Signal to child processes
# print_desc "SIGTERM to child process"
# (sleep 0.01; pkill -SIGTERM infinite_loop;
#  sleep 0.01; pkill -SIGTERM infinite_loop) &
# assert './infinite_loop'

# print_desc "SIGINT to child process"
# (sleep 0.01; pkill -SIGINT infinite_loop;
#  sleep 0.01; pkill -SIGINT infinite_loop) &
# assert './infinite_loop'

# print_desc "SIGQUIT to child process"
# (sleep 0.01; pkill -SIGQUIT infinite_loop;
#  sleep 0.01; pkill -SIGQUIT infinite_loop) &
# assert './infinite_loop'

# print_desc "SIGUSR1 to child process"
# (sleep 0.01; pkill -SIGUSR1 infinite_loop;
#  sleep 0.01; pkill -SIGUSR1 infinite_loop) &
# assert './infinite_loop'

# Manual Debug
# $ ./minishell
# $ 
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D

# Builtin
## exit
assert 'exit'
assert 'exit 42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'

## export
print_desc "Output of 'export' differs, but it's ok."
assert 'export' # order of variables, default variables differs...
assert 'export | grep nosuch | sort'
assert 'export nosuch\n export | grep nosuch | sort'
assert 'export nosuch=fuga\n export | grep nosuch | sort'
assert 'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
assert 'export [invalid]'
assert 'export [invalid_nosuch]\n export | grep nosuch | sort'
assert 'export [invalid]=nosuch\n export | grep nosuch | sort'
assert 'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
assert 'export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort'

## unset
export hoge fuga=fuga
assert 'unset'
assert 'unset hoge'
assert 'unset fuga'
assert 'unset nosuch'
assert 'unset [invalid]'
assert 'unset hoge fuga'
assert 'unset hoge nosuch fuga'
assert 'unset fuga \n export | echo $fuga'
assert 'unset [invalid] fuga \n echo $fuga'

## env
print_desc "Output of 'env' differs, but it's ok."
assert 'env' # order of variables, default variables differs...
assert 'env | grep hoge | sort'

## cd
assert 'cd'
assert 'cd .'
assert 'cd ..'
assert 'cd ///'
assert 'cd /tmp'
assert 'cd /tmp/'
assert 'cd /tmp///'
assert 'cd /../../../././.././'
assert 'cd src'
assert 'unset HOME\ncd'

assert 'cd \n echo $PWD'
assert 'cd \n echo $PWD'
assert 'cd .\n echo $PWD'
assert 'cd ..\n echo $PWD'
assert 'cd ///\n echo $PWD'
assert 'cd /tmp\n echo $PWD'
assert 'cd /tmp/\n echo $PWD'
assert 'cd /tmp///\n echo $PWD'
assert 'cd /../../../././.././\n echo $PWD'
assert 'cd src\n echo $PWD'
assert 'unset HOME\ncd \n echo $PWD'

## echo
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'

## pwd
assert 'pwd'
assert 'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd'
assert 'cd . \n pwd \n echo $PWD $OLDPWD'
assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
assert 'unset PWD\npwd\ncd /etc\npwd'

## export attribute
assert 'unset PWD \n cd \n echo $PWD \ncd /tmp\necho $PWD'
assert 'unset PWD\ncd\necho $OLDPWD\ncd /tmp\necho $OLDPWD'
assert 'unset PWD\ncd\nexport|grep PWD\ncd /tmp\nexport|grep PWD'
assert 'unset PWD\ncd\nenv|grep PWD\ncd /tmp\nenv|grep PWD'


## expand
assert 'echo $PATH'
assert 'echo $PATH $PATH'
assert 'echo $PATH $PATH $PATH'
assert "echo '\$PATH'"
assert 'echo "$PATH"'

## chmod
cat <<EOF | gcc -xc -o perm.out -
#include <stdio.h>
int main() { printf("hello from chmod\n"); }
EOF

assert 'chmod 000 perm.out\nperm.out'
assert 'chmod 000 perm.out\n./perm.out'
assert 'chmod 111 perm.out\nperm.out'
assert 'chmod 111 perm.out\n./perm.out'
assert 'chmod 222 perm.out\nperm.out'
assert 'chmod 222 perm.out\n./perm.out'
assert 'chmod 333 perm.out\nperm.out'
assert 'chmod 333 perm.out\n./perm.out'
assert 'chmod 444 perm.out\nperm.out'
assert 'chmod 444 perm.out\n./perm.out'
assert 'chmod 555 perm.out\nperm.out'
assert 'chmod 555 perm.out\n./perm.out'
assert 'chmod 666 perm.out\nperm.out'
assert 'chmod 666 perm.out\n./perm.out'
assert 'chmod 777 perm.out\nperm.out'
assert 'chmod 777 perm.out\n./perm.out'
assert 'chmod 000 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 000 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 111 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 111 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 222 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 222 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 333 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 333 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 444 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 444 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 555 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 555 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 666 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 666 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 777 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 777 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 077 perm.out\nperm.out'
assert 'chmod 077 perm.out\n./perm.out'
assert 'chmod 077 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 077 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 177 perm.out\nperm.out'
assert 'chmod 177 perm.out\n./perm.out'
assert 'chmod 177 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 177 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 277 perm.out\nperm.out'
assert 'chmod 277 perm.out\n./perm.out'
assert 'chmod 277 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 277 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 377 perm.out\nperm.out'
assert 'chmod 377 perm.out\n./perm.out'
assert 'chmod 377 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 377 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 477 perm.out\nperm.out'
assert 'chmod 477 perm.out\n./perm.out'
assert 'chmod 477 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 477 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 577 perm.out\nperm.out'
assert 'chmod 577 perm.out\n./perm.out'
assert 'chmod 577 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 577 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 677 perm.out\nperm.out'
assert 'chmod 677 perm.out\n./perm.out'
assert 'chmod 677 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 677 perm.out\ncd ..\n./test/perm.out'

assert 'chmod 707 perm.out\nperm.out'
assert 'chmod 707 perm.out\n./perm.out'
assert 'chmod 707 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 707 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 717 perm.out\nperm.out'
assert 'chmod 717 perm.out\n./perm.out'
assert 'chmod 717 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 717 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 727 perm.out\nperm.out'
assert 'chmod 727 perm.out\n./perm.out'
assert 'chmod 727 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 727 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 737 perm.out\nperm.out'
assert 'chmod 737 perm.out\n./perm.out'
assert 'chmod 737 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 737 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 747 perm.out\nperm.out'
assert 'chmod 747 perm.out\n./perm.out'
assert 'chmod 747 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 747 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 757 perm.out\nperm.out'
assert 'chmod 757 perm.out\n./perm.out'
assert 'chmod 757 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 757 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 767 perm.out\nperm.out'
assert 'chmod 767 perm.out\n./perm.out'
assert 'chmod 767 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 767 perm.out\ncd ..\n./test/perm.out'

assert 'chmod 770 perm.out\nperm.out'
assert 'chmod 770 perm.out\n./perm.out'
assert 'chmod 770 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 770 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 771 perm.out\nperm.out'
assert 'chmod 771 perm.out\n./perm.out'
assert 'chmod 771 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 771 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 772 perm.out\nperm.out'
assert 'chmod 772 perm.out\n./perm.out'
assert 'chmod 772 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 772 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 773 perm.out\nperm.out'
assert 'chmod 773 perm.out\n./perm.out'
assert 'chmod 773 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 773 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 774 perm.out\nperm.out'
assert 'chmod 774 perm.out\n./perm.out'
assert 'chmod 774 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 774 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 775 perm.out\nperm.out'
assert 'chmod 775 perm.out\n./perm.out'
assert 'chmod 775 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 775 perm.out\ncd ..\n./test/perm.out'
assert 'chmod 776 perm.out\nperm.out'
assert 'chmod 776 perm.out\n./perm.out'
assert 'chmod 776 perm.out\ncd ..\ntest/perm.out'
assert 'chmod 776 perm.out\ncd ..\n./test/perm.out'


assert 'ls'
assert 'cd /bin\nls'
assert 'cd /bin\n/bin/ls'
assert '/ls'
assert '//ls'
assert '///ls'
assert '////ls'
assert '/////ls'

assert '.'
assert './'
assert './.'
assert '././.'
assert './././.'
assert '..'
assert '../'
assert '../.'
assert '.././.'
assert '../././.'
assert '...'
assert '.../'
assert '.../.'
assert '..././.'
assert '.../././.'
assert '....'
assert '..../'
assert '....'
assert '....'
assert '/'
assert '/.'
assert '/./.'
assert '/bin'
assert '/bin/'
assert '/bin/ls'
assert '/bin/ls/'
## ○No such file or directory ✗command not found　に行きたい 
assert './aaa'


cleanup
