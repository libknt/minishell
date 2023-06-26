/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahito <masahito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:28:29 by masahito          #+#    #+#             */
/*   Updated: 2023/06/27 00:42:00 by masahito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

bool	is_skip(char c, int *status)
{
	if (c == '\'' && *status == NO_QUOTE)
		*status = SINGLE_QUOTE;
	else if (c == '\'' && *status == SINGLE_QUOTE)
		*status = NO_QUOTE;
	else if (c == '"' && *status == NO_QUOTE)
		*status = DOUBLE_QUOTE;
	else if (c == '"' && *status == DOUBLE_QUOTE)
		*status = NO_QUOTE;
	else
		return (false);
	return (true);
}

size_t	env_len(char *line)
{
	size_t i = 0;
	
	while(i < ft_strlen(line) && !is_quote(line[i]) && !ft_isspace(line[i]) && line[i] != ';')

		i++;
	return (i);
}

size_t	add_char(char **str, char *line)
{
	if (!str || !*str)
		return 0;
	*str = ft_strjoin_free(*str, ft_strndup(line, 1));
	return (1);
}

static char	*find_environ(char *str, t_env *env)
{
	char	*env_value;

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
			if (env->value)
			{
				env_value = ft_strdup(env->value);
				if (!env_value)
					_err_malloc();
			}
			else
				env_value = NULL;
			free(str);
			return (env_value);
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
