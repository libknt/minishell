/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:45:33 by keys              #+#    #+#             */
/*   Updated: 2023/03/05 21:43:19 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addline(t_token *token, t_line **line, t_line *new, int type)
{
	while (1)
	{
		if (token->type == T_EOF || token->type == OP)
			break ;
		if (find_redirect(token))
		{
			type = 1;
			new = newline(token, REDIRECT);
		}
		else if (type == 1)
		{
			type = 0;
			new = newline(token, FILENAME);
		}
		else
		{
			new = newline(token, CMDLINE);
		}
		line_addback(line, new);
		token = token->next;
	}
}

t_line	*make_line(t_token *token)
{
	t_line	*line;
	t_line	*new;

	line = NULL;
	if (token->type == OP)
		return (newline(token, PIPE));
	else
		addline(token, &line, NULL, 0);
	new = newline(NULL, T_EOF_R);
	line_addback(&line, new);
	return (line);
}
