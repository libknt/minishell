/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/02/25 12:10:51 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit(1);
}

int	main(void)
{
	char	*line;
	bool	flag;
	t_token	*token;
	t_node	*tree;

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
		// print_tree(tree);
		// exe(tree);
		tree_free(tree);
		token_free(&token);
		free(line);
		// printf("finish\n");
	}
	// rl_clear_history();
	return (0);
}
