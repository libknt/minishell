/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/07/01 13:01:38 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

static void	_err_arg(void)
{
	write(2, "Please run it with ./{ executable file name }.\n", 47);
	exit(127);
}

static void	func_readline(t_env **env, char *line, t_token *token, t_node *tree)
{
	while (1)
	{
		if (isatty(0))
			rl_event_hook = check_state;
		set_signal();
		line = readline("minishell>");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		token = lexer(&line, *env);
		if (token == NULL)
			continue ;
		expand_token(&token, *env, false);
		tree = parser(token, line);
		if (tree == NULL)
			continue ;
		exe_(tree, env);
		tree_free(tree);
		token_free(&token);
		free(line);
	}
}

static void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	int			i;

	(void)argv;
	if (argc != 1)
		_err_arg();
	env = NULL;
	make_lstenv(&env, envp);
	rl_outstream = stderr;
	func_readline(&env, NULL, NULL, NULL);
	free_env(env);
	i = g_global.exit_status % 255;
	return (i);
}
