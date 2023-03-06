/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:16:08 by keys              #+#    #+#             */
/*   Updated: 2023/03/01 23:14:13 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t			wordlen(char *prompt, char **line, size_t i);

void	qq_flag(bool *sq, bool *dq, char c)
{
	if (c == '\"')
	{
		if (!(*sq))
			*dq = !*dq;
	}
	else if (c == '\'')
	{
		if (!(*dq))
			*sq = !*sq;
	}
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_metacharacter(char c)
{
	char	*is;

	is = strchr("|&;()<> \t", c);
	if (is == NULL)
		return (false);
	return (true);
}

size_t	is_ope(char *line)
{
	if (strncmp(line, "||", 2) == 0 || strncmp(line, "&&", 2) == 0 ||
		strncmp(line, ";;", 2) == 0 || strncmp(line, "|&", 2) == 0)
		return (2);
	if (strncmp(line, "&", 1) == 0 || strncmp(line, ";", 1) == 0
		|| strncmp(line, "(", 1) == 0 ||
		strncmp(line, ")", 1) == 0 || strncmp(line, "|", 1) == 0
			|| strncmp(line, "\n", 1) == 0)
		return (1);
	return (0);
}

size_t	is_redirect(char *line)
{
	if ((strncmp(line, "<<", 2) == 0) || (strncmp(line, ">>", 2) == 0))
		return (2);
	if ((strncmp(line, "<", 1) == 0) || (strncmp(line, ">", 1) == 0))
		return (1);
	return (0);
}

char	*ft_join_free(char *s1, char *s2, int flag1, int flag2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		_err("malloc");
	if (flag1)
		free(s1);
	if (flag2)
		free(s2);
	return (tmp);
}

size_t	num_(bool *dq, bool *sq, char *tmp)
{
	size_t	num = 0;

	while (1)
	{
		if (*dq)
			tmp = strchr(tmp, '\"');
		if (*sq)
			tmp = strchr(tmp, '\'');
		if (tmp == NULL)
		{
			break ;
		}
		num++;
		tmp++;
	}
	return (num);
}

char	*readline_quate(bool *dq, bool *sq)
{
	char	*new;

	if (*dq)
		new = readline("dquote>");
	else if (*sq)
		new = readline("quote>");
	return (new);
}

void	continue_read(bool *sq, bool *dq, char **line)
{
	char	*new;
	size_t	num;

	num = 0;
	while (1)
	{
		new = readline_quate(dq, sq);
		if (new == NULL)
			break ;
		if (!new[0])
		{
			free(new);
			continue ;
		}
		*line = ft_join_free(*line, "\n", 1, 0);
		*line = ft_join_free(*line, new, 1, 0);
		num = num_(dq, sq, new);
		free(new);
		if (num && (num % 2 == 1))
			return ;
	}
	free(new);
}

bool	is_ok(char *prompt, size_t len)
{
	if (is_blank(prompt[len]) || prompt[len] == '\0' ||
		is_ope(&prompt[len]) || (strncmp(&prompt[len], "<", 1) == 0) ||
		(strncmp(&prompt[len], ">", 1) == 0))
		return (true);
	return (false);
}

size_t	quate_wordlen(bool *dq, bool *sq, size_t i, char **line)
{
	continue_read(sq, dq, line);
	return (wordlen((*line) + i, line, i));
}

bool	quate_flag(char *prompt, size_t *len, bool *dq, bool *sq)
{
	if (prompt[*len] == '\"' || prompt[*len] == '\'')
	{
		qq_flag(sq, dq, prompt[*len]);
		*len += 1;
		return (true);
	}
	return (false);
}

size_t	wordlen(char *prompt, char **line, size_t i)
{
	size_t	len;
	bool	dq;
	bool	sq;

	sq = false;
	dq = false;
	len = 0;
	if (is_ope(prompt))
		return (is_ope(prompt));
	if (is_redirect(prompt))
		return (is_redirect(prompt));
	while (1)
	{
		if (quate_flag(prompt, &len, &dq, &sq))
			continue ;
		if (!dq && !sq)
			if (is_ok(prompt, len))
				break ;
		if ((sq || dq) && prompt[len] == '\0')
			return (quate_wordlen(&dq, &sq, i, line));
		len++;
	}
	return (len);
}

t_token	*token_last(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	token_addback(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (head)
	{
		if (*head)
		{
			tmp = token_last(*head);
			tmp->next = new;
		}
		else
			*head = new;
	}
}

t_token	*new_token(char *str, t_token_type type)
{
	t_token	*new;

	new = calloc(sizeof(t_token), 1);
	if (!new)
		_err("calloc");
	new->type = type;
	new->word = str;
	return (new);
}

t_token_type	find_type(char *tmp)
{
	if (strncmp(tmp, "||", 2) == 0 || strncmp(tmp, "&&", 2) == 0 ||
		strncmp(tmp, ";;", 2) == 0 || strncmp(tmp, "|&", 2) == 0 ||
		strncmp(tmp, "&", 1) == 0 || strncmp(tmp, ";", 1) == 0 ||
		strncmp(tmp, "(", 1) == 0 || strncmp(tmp, ")", 1) == 0 ||
		strncmp(tmp, "|", 1) == 0 || strncmp(tmp, "\n", 1) == 0)
		return (OP);
	return (WORD);
}

t_token	*make_token(char **line)
{
	size_t	len;
	size_t	i;
	t_token	*head;
	t_token	*token;
	char	*word;
	char	*prompt;

	i = 0;
	prompt = *line;
	head = NULL;
	while (1)
	{
		while (is_blank(prompt[i]))
			i++;
		if (prompt[i] == '\0')
			break ;
		len = wordlen(&prompt[i], line, i);
		if (len == 0)
			break ;
		else
		{
			prompt = *line;
			word = strndup(&prompt[i], len);
			if (!word)
				_err("malloc");
			i += len;
			token = new_token(word, find_type(word));
			token_addback(&head, token);
		}
	}
	token = new_token(NULL, T_EOF);
	token_addback(&head, token);
	return (head);
}

t_token	*lexer(char **line,t_env *env)
{
	t_token	*token;

	if (!*line[0])
		return (NULL);
	token = make_token(line);
	// expand(token);
	ex_toke(&token ,env);
	return (token);
}
*/
