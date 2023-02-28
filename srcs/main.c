/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/02/28 14:21:49 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit(1);
}

void print_env1(t_env *env)
{
	while(1)
	{
		if(env == NULL)
			break;
		printf("%s\t:\t%s\n\n\n",env->key,env->value);
		env= env->next;
	}

}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	bool	flag;
	t_token	*token;
	t_node	*tree;
	t_env	*env;

	(void)argc;
	(void)argv;
	// (void)envp;
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
		if(!line[0])
		{
			free(line);
			continue;
		}
		if (*line)
			add_history(line);
		token = lexer(&line);
		// print_t(token);
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
		exe_(tree);
		tree_free(tree);
		token_free(&token);
		free(line);
	}
	return (0);
}
