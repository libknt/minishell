/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/02/10 16:15:17 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;

	rl_outstream = stderr;
	while (1)
	{
		prompt = readline("minishell>");
		if (prompt == NULL)
			break ;
		if (*prompt)
			add_history(prompt);
		lexer(prompt);
		exe(prompt);
		free(prompt);
	}
	exit(0);
}
