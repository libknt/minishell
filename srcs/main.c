/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/02/11 08:55:53 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit(1);
}

void	print_t(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (!(tmp))
			break ;
		printf("w =%s;t=%d;p=%p\n", tmp->word, tmp->type, tmp->next);
		tmp = tmp->next;
	}
}

int	main(void)
{
	char	*prompt;
	t_token *token;

	rl_outstream = stderr;
	while (1)
	{
		prompt = readline("minishell>");
		if (prompt == NULL)
			break ;
		if (!prompt[0])
			continue ;
		token = lexer(&prompt);
		// print_t(token);
		exe(token);
		if (*prompt)
			add_history(prompt);
		free(prompt);
	}
	exit(0);
}
