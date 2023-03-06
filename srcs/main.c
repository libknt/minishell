/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/03/06 11:07:53 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;
void	print_env1(t_env *env)
{
	while (1)
	{
		if (env == NULL)
			break ;
		printf("%s\t:\t%s\n\n\n", env->key, env->value);
		env = env->next;
	}
}

void	_err_arg(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	// if (strncmp(&argv[1][strlen(argv[1]) - 3], ".sh", 3) == 0)
	// 	write(1, ".sh files are not executable\n", 29);
	// else
	// 	write(1, "cannot execute binary file\n", 27);
	write(2, "Please run it with ./{ executable file name }.\n", 47);
	exit(127);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;
	t_node	*tree;
	t_env	*env;

	if (argc != 1)
		_err_arg(argc, argv);
	env = NULL;
	make_lstenv(&env, envp);
	// print_env1(env);
	set_signal();
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell>");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (strcmp(line, "echo $?") == 0)
		{
			printf("%d\n", exit_status);
			free(line);
			continue ;
		}
		token = lexer(&line, env);
		if (token == NULL)
			continue ;
		tree = parser(token, line);
		if (tree == NULL)
			continue ;
		exe_(tree);
		tree_free(tree);
		token_free(&token);
		free(line);
	}
	return (0);
}
