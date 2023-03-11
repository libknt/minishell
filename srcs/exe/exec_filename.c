/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:17:23 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 00:41:58 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*seach_path(char **envp)
{
	ssize_t	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
			return (strdup(&envp[i][5]));
		i++;
	}
	return (NULL);
}

static char	*access_check(char **argv, char *s)
{
	char	*pa;
	int		k;

	k = 0;
	while (argv[k])
	{
		pa = argv[k];
		argv[k] = ft_strjoin(pa, s);
		if (!argv[k])
			_err_malloc();
		free(pa);
		if (access(argv[k], X_OK) == 0)
		{
			pa = strdup(argv[k]);
			if (!pa)
				_err_malloc();
			ft_split_free(argv);
			free(s);
			return (pa);
		}
		k++;
	}
	free(s);
	ft_split_free(argv);
	return (NULL);
}

char	*exec_filename(char *prompt, char **envp)
{
	char	*pa;
	char	*s;
	char	**argv;

	if (*prompt == '\0')
		return (NULL);
	s = ft_strjoin("/", prompt);
	if (!s)
		_err_malloc();
	pa = seach_path(envp);
	if (!pa)
		_err_malloc();
	argv = ft_split(pa, ':');
	free(pa);
	return (access_check(argv, s));
}
