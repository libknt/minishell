/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 14:24:36 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global global;
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
		rl_event_hook = check_state;
		set_signal();
		line = readline("minishell>");
		if (line == NULL)
			break ;
		printf("-------------------------\n");
		printf("%d\n",__LINE__);
		printf("-------------------------\n");
		fflush(stdout);
		if (*line)
			add_history(line);
		printf("-------------------------\n");
		printf("%d\n",__LINE__);
		printf("-------------------------\n");
		token = lexer(&line, env);
		if (token == NULL)
			continue ;
		printf("-------------------------\n");
		printf("%d\n",__LINE__);
		printf("-------------------------\n");
		tree = parser(token, line);
		if (tree == NULL)
			continue ;
		printf("-------------------------\n");
		printf("%d\n",__LINE__);
		printf("%p ; %p : %p\n",tree ,tree->left,tree->line);
		printf("%s : %s\n",tree->line->token->word,tree->line->next->token->word);
		printf("-------------------------\n");
		exe_(tree, env);
		tree_free(tree);
		token_free(&token);
		free(line);
	}
	return (0);
}
