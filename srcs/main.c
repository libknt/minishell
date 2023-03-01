/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marai <MasaDevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/02/26 23:18:51 by Marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	bool	flag;
	t_token	*token;
	t_node	*tree;
	// t_env	*env;

	(void)argc;
	(void)argv;
	(void)envp;
	// env = NULL;
	// make_lstenv(&env, envp);
	set_signal();
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell>");
		if (line == NULL)
		{
			printf("Ctr + D\n");
			break ;
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		token = lexer(&line);
		flag = token_error(token);
		if (flag)
		{
			token_free(&token);
			free(line);
			continue ;
		}
		tree = parser(token);
		flag = parse_err(tree);
		if (flag)
		{
			tree_free(tree);
			token_free(&token);
			free(line);
			continue ;
		}
		//test(tree);
		// print_tree(tree);
		//exec_tree(tree);
		exe_(tree);
		// exe(tree);
		tree_free(tree);
		token_free(&token);
		free(line);
		// printf("finish\n");
	}
	// rl_clear_history();
	return (0);
}
