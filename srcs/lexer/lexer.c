/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:16:08 by keys              #+#    #+#             */
/*   Updated: 2023/03/26 14:39:48 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	wordlen(char *prompt, t_data_t *d)
{
	size_t	len;

	d->dq = false;
	d->sq = false;
	len = 0;
	if (is_ope(prompt))
		return (is_ope(prompt));
	if (is_redirect(prompt))
		return (is_redirect(prompt));
	while (1)
	{
		if (quate_flag(prompt, &len, &d->dq, &d->sq))
			continue ;
		if (!d->dq && !d->sq)
			if (is_ok(prompt, len))
				break ;
		if ((d->sq || d->dq) && prompt[len] == '\0')
		{
			_err_syntax("\"");
			return (-1);
		}
		len++;
	}
	return (len);
}

t_token_type	find_type(char *tmp)
{
	if (strncmp(tmp, "||", 2) == 0 || strncmp(tmp, "&&", 2) == 0 || strncmp(tmp,
			";;", 2) == 0 || strncmp(tmp, "|&", 2) == 0 || strncmp(tmp, "&",
			1) == 0 || strncmp(tmp, ";", 1) == 0 || strncmp(tmp, "(", 1) == 0
		|| strncmp(tmp, ")", 1) == 0 || strncmp(tmp, "|", 1) == 0
		|| strncmp(tmp, "\n", 1) == 0)
		return (OP);
	return (WORD);
}

bool	make_token(char **line, t_data_t *d)
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
			d->word = strndup(&d->prompt[d->i], d->len);
			if (!d->word)
				_err_malloc();
			d->i += d->len;
			d->token = new_token(d->word, find_type(d->word));
			token_addback(&d->head, d->token);
		}
	}
	return (false);
}

static void	*lexer_err_free(char **line, t_token **token)
{
	token_free(token);
	free(*line);
	return (NULL);
}

static void	check_redirect(t_token *token)
{
	while (1)
	{
		if (token->type == T_EOF)
			break ;
		if (strchr(token->word, '"') || strchr(token->word, '\''))
		{
			token->type = EX_WORD;
		}
		token = token->next;
	}
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
	memset(&data, 0, sizeof(t_data_t));
	data.prompt = *line;
	if (make_token(line, &data))
		return (lexer_err_free(line, &data.head));
	data.token = new_token(NULL, T_EOF);
	token_addback(&data.head, data.token);
	token = data.head;
	if (token_error(token))
		return (lexer_err_free(line, &token));
	check_redirect(token);
	// expand_token(&token, env);
	return (token);
}
