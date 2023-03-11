/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:36:02 by marai             #+#    #+#             */
/*   Updated: 2023/03/11 14:52:52 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s) && *s != '=')
			return (false);
		s++;
	}
	return (true);
}

ssize_t	vari_end(char *line)
{
	ssize_t	i;

	if (!line)
		return (-1);
	i = 0;
	if (isdigit(line[i]))
		return (1);
	if (!is_alpha_under(line[i]))
		return (0);
	i++;
	while (line[i])
	{
		if (!is_alpha_num_under(line[i]))
			return (i);
		i++;
	}
	return (i);
}

ssize_t	find_env_len(char *str, t_env *env)
{
	while (env)
	{
		if (!strcmp(env->key, str))
		{
			return (strlen(env->value));
		}
		env = env->next;
	}
	return (0);
}

ssize_t	calc_expand_len(char *line, t_env *env, ssize_t len)
{
	ssize_t	end;
	char	*str;

	end = vari_end(line);
	str = calloc(end + 1, sizeof(char));
	if (str == NULL)
		return (-1);
	ft_strlcpy(str, line, end + 1);
	len = len - end + find_env_len(str, env) - 1;
	free(str);
	return (len);
}
ssize_t	vari_expand_len(char *line, t_env *env)
{
	ssize_t	i;
	ssize_t	len;
	ssize_t	quote_counter;

	i = 0;
	quote_counter = 0;
	len = strlen(line);
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\'')
			quote_counter++;
		if (line[i] == '$' && quote_counter % 2 == 0 && (i == 0 || line[i
				- 1] != '\\'))
		{
			i++;
			len = calc_expand_len(&line[i], env, len);
			if (len < 0)
				return (len);
		}
		i++;
	}
	return (len);
}

char	*find_env(char *str, t_env *env)
{
	char	*env_value;

	while (env)
	{
		if (!strcmp(env->key, str))
		{
			env_value = strdup(env->value);
			return (env_value);
		}
		env = env->next;
	}
	return (NULL);
}

ssize_t	make_expand(char *expanded, char *line, t_env *env)
{
	ssize_t	end;
	char	*str;
	char	*env_value;

	end = vari_end(line);
	str = calloc(end + 1, sizeof(char));
	if (str == NULL)
		_err("calloc error\n");
	ft_strlcpy(str, line, end + 1);
	env_value = find_env(str, env);
	if (env_value != NULL)
		strncat(expanded, env_value, strlen(env_value));
	free(env_value);
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
	expanded = calloc(expanded_len + 1, sizeof(char));
	if (!expanded)
		_err("calloc");
	i = 0;
	quote_counter = 0;
	while (i < strlen(line))
	{
		if (line[i] == '\'')
			quote_counter++;
		if (line[i] == '$' && quote_counter % 2 == 0 && (i == 0 || line[i
				- 1] != '\\'))
			i += make_expand(expanded, &line[i + 1], env);
		else
			strncat(expanded, &line[i], 1);
		i++;
	}
	free(line);
	return (expanded);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"' || c == '`');
}

char	*expand_quote(char *line)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	len;
	ssize_t	diff;
	char	*line2;
	char	*last;

	if (!line)
		return (NULL);
	len = strlen(line);
	line2 = calloc(len + 1, sizeof(char));
	if (!line2)
		_err("calloc\n");
	i = 0;
	j = 0;
	while (line[i])
	{
		while (isspace(line[i]) && isspace(line[i + 1]))
			i++;
		if (is_quote(line[i]))
		{
			last = strchr(&line[i + 1], line[i]);
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
	free(line);
	return (line2);
}

void	expand_token(t_token **token, t_env *env)
{
	t_token	*tmp;

	tmp = *token;
	while (1)
	{
		if (tmp->type == T_EOF)
			break ;
		tmp->word = vari_expand(tmp->word, env);
		tmp->word = expand_quote(tmp->word);
		tmp = tmp->next;
	}
}
