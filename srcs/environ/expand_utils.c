/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:28:29 by masahito          #+#    #+#             */
/*   Updated: 2023/06/28 11:10:18 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

size_t	env_len(char *line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line) && !is_quote(line[i])
		&& (is_alpha_num_under(line[i]) || line[i] == '?'))
		i++;
	return (i);
}

size_t	add_char(char **str, char *line)
{
	if (!*str || !line)
		return (0);
	*str = ft_strjoin_free(*str, ft_strndup(line, 1));
	return (1);
}

static char	*make_env_key(t_env *env)
{
	char	*env_value;

	if (env->value)
		env_value = ft_strdup(env->value);
	else
		env_value = ft_strdup("");
	if (!env_value)
		_err_malloc();
	return (env_value);
}

static char	*find_environ(char *str, t_env *env)
{
	if (!ft_strcmp(str, "?"))
	{
		g_global.exit_status = g_global.exit_status % 255;
		free(str);
		return (ft_itoa(g_global.exit_status));
	}
	while (env)
	{
		if (!ft_strcmp(env->key, str))
		{
			free(str);
			return (make_env_key(env));
		}
		env = env->next;
	}
	free(str);
	return (ft_strdup(""));
}

size_t	expand_env(char **str, char *line, t_env *env)
{
	size_t	len;

	len = env_len(&line[1]);
	*str = ft_strjoin_free(*str, find_environ(ft_strndup(&line[1], len), env));
	len++;
	return (len);
}
