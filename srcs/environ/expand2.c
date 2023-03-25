/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:36:02 by marai             #+#    #+#             */
/*   Updated: 2023/03/25 20:49:08 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

ssize_t	vari_end(char *line)
{
	ssize_t	i;

	if (!line)
		return (-1);
	if (*line == '?')
		return (1);
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
		_err_malloc();
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
		if (line[i] == '$' && quote_counter % 2 == 0 && \
			(i == 0 || line[i - 1] != '\\'))
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

	if (*str == '?')
	{
		g_global.exit_status = g_global.exit_status % 255;
		return (ft_itoa(g_global.exit_status));
	}
	while (env)
	{
		if (!strcmp(env->key, str))
		{
			env_value = strdup(env->value);
			if (!env_value)
				_err_malloc();
			return (env_value);
		}
		env = env->next;
	}
	return (NULL);
}
