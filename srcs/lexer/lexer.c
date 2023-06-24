/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:16:08 by keys              #+#    #+#             */
/*   Updated: 2023/06/24 21:31:12 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	make_token(char **line, t_data_t *d)
{
	while (1)
	{
		while (is_blank(d->prompt[d->i]))
			d->i++;
		if (d->prompt[d->i] == '\0')
			break ;
		d->len = wordlen(&d->prompt[d->i], d);
		if (d->len == -1)
			return (true);
		else if (d->len == 0)
			break ;
		else
		{
			d->prompt = *line;
			d->word = ft_strndup(&d->prompt[d->i], d->len);
			if (!d->word)
				_err_malloc();
			d->i += d->len;
			d->token = new_token(d->word, find_type(d->word));
			token_addback(&d->head, d->token);
		}
	}
	return (false);
}

t_token	*lexer(char **line, t_env *env)
{
	t_data_t	data;
	t_token		*token;

	(void)env;
	if (!*line[0])
	{
		free(*line);
		return (NULL);
	}
	token = NULL;
	ft_memset(&data, 0, sizeof(t_data_t));
	data.prompt = *line;
	if (make_token(line, &data))
		return (lexer_err_free(line, &data.head));
	data.token = new_token(NULL, T_EOF);
	token_addback(&data.head, data.token);
	token = data.head;
	if (token_error(token))
		return (lexer_err_free(line, &token));
	check_redirect(token);
	return (token);
}
