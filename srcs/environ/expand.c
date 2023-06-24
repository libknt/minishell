/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:36:02 by marai             #+#    #+#             */
/*   Updated: 2023/06/24 16:27:00 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	make_expand(char *expanded, char *line, t_env *env)
{
	ssize_t	end;
	char	*str;
	char	*env_value;

	end = vari_end(line);
	str = ft_calloc(end + 1, sizeof(char));
	if (str == NULL)
		_err_malloc();
	ft_strlcpy(str, line, end + 1);
	env_value = find_env(str, env);
	if (env_value != NULL)
	{
		ft_strncat(expanded, env_value, ft_strlen(env_value));
		free(env_value);
	}
	free(str);
	return (end);
}

char	*vari_expand(char *line, t_env *env)
{
	ssize_t	expanded_len;
	size_t	i;
	ssize_t	quote_counter;
	char	*expanded;

	expanded_len = vari_expand_len(line, env);
	expanded = ft_calloc(expanded_len + 1, sizeof(char));
	if (!expanded)
		_err_malloc();
	i = 0;
	quote_counter = 0;
	while (i < ft_strlen(line))
	{
		if (line[i] == '\'')
			quote_counter++;
		if (line[i] == '$' && quote_counter % 2 == 0 && \
			(i == 0 || line[i - 1] != '\\'))
			i += make_expand(expanded, &line[i + 1], env);
		else
			ft_strncat(expanded, &line[i], 1);
		i++;
	}
	free(line);
	return (expanded);
}

static void	expand_quote_utils(char *line, char *line2, char *last)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	diff;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]) && ft_isspace(line[i + 1]))
			i++;
		if (is_quote(line[i]))
		{
			last = ft_strchr(&line[i + 1], line[i]);
			diff = last - &line[i];
			ft_strlcpy(&line2[j], &line[i + 1], last - &line[i]);
			i += diff;
			j += diff - 2;
		}
		else
			line2[j] = line[i];
		i++;
		j++;
	}
}

char	*expand_quote(char *line)
{
	ssize_t	len;
	char	*line2;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	line2 = ft_calloc(len + 1, sizeof(char));
	if (!line2)
		_err_malloc();
	expand_quote_utils(line, line2, NULL);
	free(line);
	return (line2);
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
		tmp->word = vari_expand(tmp->word, env);
		tmp->word = expand_quote(tmp->word);
		tmp = tmp->next;
	}
}
