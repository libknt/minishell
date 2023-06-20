/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:17:23 by keys              #+#    #+#             */
/*   Updated: 2023/06/20 15:31:54 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*seach_path(char **envp)
{
	ssize_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_strdup(&envp[i][5]));
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
			pa = ft_strdup(argv[k]);
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
	pa = seach_path(envp);
	if (!pa)
		return (NULL);
	s = ft_strjoin("/", prompt);
	if (!s)
		_err_malloc();
	argv = ft_split(pa, ':');
	free(pa);
	return (access_check(argv, s));
}
