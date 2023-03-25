/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 17:45:18 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global g_global;
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

void	_err_arg(void)
{
	write(2, "Please run it with ./{ executable file name }.\n", 47);
	exit(127);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;
	t_node	*tree;
	t_env	*env;

	(void)argv;
	if (argc != 1)
		_err_arg();
	env = NULL;
	make_lstenv(&env, envp);
	rl_outstream = stderr;
	while (1)
	{
		if(isatty(0))
			rl_event_hook = check_state;
		set_signal();
		line = readline("minishell>");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		token = lexer(&line, env);
		if (token == NULL)
			continue ;
		tree = parser(token, line);
		if (tree == NULL)
			continue ;
		exe_(tree, env);
		tree_free(tree);
		token_free(&token);
		free(line);
	}
	return (0);
}
