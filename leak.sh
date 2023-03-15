#!bin/bash

func()
{
	while [ 1 ]
	do
	leaks -q minishell
	sleep 2
	done
}

func
