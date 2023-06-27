/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:36:02 by marai             #+#    #+#             */
/*   Updated: 2023/06/27 13:52:47 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*ans;

	if (!str1 || !str2)
	{
		free(str1);
		free(str2);
		_err_malloc();
		return (NULL);
	}
	ans = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (ans);
}

char	*expand(char *line, t_env *env)
{
	size_t	i;
	char	**str;
	char	*first;
	int		status;

	i = 0;
	first = ft_strdup("");
	if (!first)
		_err_malloc();
	str = &first;
	status = NO_QUOTE;
	while (line && i < ft_strlen(line))
	{
		if (!str || !*str)
			_err_malloc();
		if (is_skip(line[i], &status))
			i++;
		else if (line[i] == '$' && status != SINGLE_QUOTE)
			i += expand_env(str, &line[i], env);
		else
			i += add_char(str, &(line[i]));
	}
	free(line);
	return (*str);
}

char	*expand_quote(char *line)
{
	size_t	i;
	char	**str;
	char	*first;
	int		status;

	i = 0;
	first = ft_strdup("");
	if (!first)
		_err_malloc();
	str = &first;
	status = NO_QUOTE;
	while (line && i < ft_strlen(line))
	{
		if (!str || !*str)
			_err_malloc();
		if (is_skip(line[i], &status))
			i++;
		else
			i += add_char(str, &(line[i]));
	}
	free(line);
	return (*str);
}

char	*expand_all_env(char *line, t_env *env)
{
	size_t	i;
	char	**str;
	char	*first;

	i = 0;
	first = ft_strdup("");
	if (!first)
		_err_malloc();
	str = &first;
	while (line && i < ft_strlen(line))
	{
		if (line[i] == '$' && (i == 0 || line[i - 1] != '\\'))
			i += expand_env(str, &line[i], env);
		else
			i += add_char(str, &(line[i]));
	}
	free(line);
	return (*str);
}

void	expand_token(t_token **token, t_env *env, bool f)
{
	t_token	*tmp;

	tmp = *token;
	while (1)
	{
		if (tmp->type == T_EOF)
			break ;
		if (f)
		{
			f = false;
			if (ft_strchr(tmp->word, '"') || ft_strchr(tmp->word, '\''))
			{
				(*tmp->ex_heredoc_flag) = true;
			}
			tmp->word = expand_quote(tmp->word);
			tmp = tmp->next;
			continue ;
		}
		else if (is_heredoc_flag(tmp->word))
			f = true;
		tmp->word = expand(tmp->word, env);
		tmp = tmp->next;
	}
}
