/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:16:08 by keys              #+#    #+#             */
/*   Updated: 2023/02/11 08:01:03 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qq_flag(bool *sq,bool *dq ,char c)
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
void	continue_read(bool *sq,bool *dq, char *prompt, char **line)
{
	char	*new;
	size_t	num;
	char	*tmp;

	if (prompt)
		num = 0;
	num = 0;
	if (*dq)
	{
		while (1)
		{
			new = readline("dq>");
			if (new == NULL)
				break ;
			if (!new[0])
				continue ;
			*line = ft_join_free(*line, new, 1, 0);
			tmp = new;
			while (1)
			{
				tmp = strchr(tmp, '\"');
				if (tmp == NULL)
					break ;
				num++;
				tmp++;
			}
			if (num && (num % 2 == 1))
			{
				return ;
			}
			// if (*new)
			// 	add_history(new);
			free(new);
		}
		free(new);
	}
	else if(*sq)
	{
		while (1)
		{
			new = readline("sq>");
			if (new == NULL)
				break ;
			if (!new[0])
				continue ;
			*line = ft_join_free(*line, new, 1, 0);
			tmp = new;
			while (1)
			{
				tmp = strchr(tmp, '\'');
				if (tmp == NULL)
					break ;
				num++;
				tmp++;
			}
			if (num && (num % 2 == 1))
			{
				return ;
			}
			// if (*new)
			// 	add_history(new);
			free(new);
		}
		free(new);
	}

}

size_t	wordlen(char *prompt, char **line, size_t i)
{
	size_t	len;
	// bool	*qq;
	bool dq;
	bool sq;

	printf("line =%s\n", *line);
	sq =false;
	dq =false;
	printf("ppp =%s\n", prompt);
	// qq = calloc(1, sizeof(bool));
	// if (!qq)
	// 	_err("bool");
	len = 0;
	if (is_ope(prompt))
		return (is_ope(prompt));
	while (1)
	{
		printf("<%c>", prompt[len]);
		printf("%d,%d;\n",sq,dq);
		fflush(stdout);
		if (prompt[len] == '\"' || prompt[len] == '\'')
		{
			qq_flag(&sq,&dq, prompt[len]);
			len++;
			continue ;
		}
		if (!dq && !sq)
		{
			if (is_blank(prompt[len]) || prompt[len] == '\0'
				|| is_ope(&prompt[len]))
				break ;
		}
		if ((sq || dq) && prompt[len] == '\0')
		{
			continue_read(&sq,&dq, prompt, line);
			// free(qq);
			// return (1);
			// printf("line = %ld\n",i);
			printf("linesss = %s\n", (*line) + i);
			return (wordlen((*line) + i, line, i));
			// return (i);
		}
		len++;
	}
	// free(qq);
	return (len);
}
/*
size_t	wordlen(char *line)
{
	size_t	len;
	bool	*qq;

	qq = calloc(1, sizeof(bool));
	if (!qq)
		_err("bool");
	len = 0;
	if (is_ope(line))
		return (is_ope(line));
	while (1)
	{
		if ((qq[0] || qq[1]) && line == '\0')
		{
			continue_read(qq, &line);
			return (len);
		}
		if (*line == '\"' || *line == '\'')
		{
			qq_flag(qq, *line);
			len++;
			line++;
			continue ;
		}
		if (!qq[0] && !qq[1])
		{
			if (is_blank(*line) || *line == '\0' || is_ope(line))
				break ;
		}
		line++;
		len++;
	}
	free(qq);
	return (len);
}
*/
// void	make_token(t_token *token, t_token *new)
// {
// 	if(!new)
// 		_err("new_token malloc");

// }

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
	if (tmp)
		return (WORD);
	return (WORD);
}

t_token	*lexer(char **line)
{
	size_t	len;
	size_t	i;
	t_token	*token;
	char	*word;
	char	*prompt;

	i = 0;
	prompt = *line;
	token = NULL;
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
			// printf("%ld :%s:\n", len,word);
			i += len;
			token = new_token(word, find_type(word));
			printf("%p: %d: %s\n", token->next, token->type, token->word);
			// make_token(&token, new_token(word, find_type(word)));
		}
		// len = word(prompt);
		// if(len == 0)
		// 	break ;
		// else{
		// 	// set
		// }
	}
	return (NULL);
}
