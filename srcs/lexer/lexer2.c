/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:16:08 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:03:39 by kyoda            ###   ########.fr       */
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
	if (ft_strncmp(tmp, "||", 2) == 0 || ft_strncmp(tmp, "&&", 2) == 0
		|| ft_strncmp(tmp, ";;", 2) == 0 || ft_strncmp(tmp, "|&", 2) == 0
		|| ft_strncmp(tmp, "&", 1) == 0 || ft_strncmp(tmp, ";", 1) == 0
		|| ft_strncmp(tmp, "(", 1) == 0 || ft_strncmp(tmp, ")", 1) == 0
		|| ft_strncmp(tmp, "|", 1) == 0 || ft_strncmp(tmp, "\n", 1) == 0)
		return (OP);
	return (WORD);
}

void	*lexer_err_free(char **line, t_token **token)
{
	token_free(token);
	free(*line);
	return (NULL);
}

void	check_redirect(t_token *token)
{
	while (1)
	{
		if (token->type == T_EOF)
			break ;
		if (ft_strchr(token->word, '"') || ft_strchr(token->word, '\''))
		{
			token->type = EX_WORD;
		}
		token = token->next;
	}
}
