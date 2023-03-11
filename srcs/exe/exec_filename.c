/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:17:23 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 16:04:55 by kyoda            ###   ########.fr       */
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
		free(pa);
		if (access(argv[k], X_OK) == 0)
		{
			pa = strdup(argv[k]);
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
	int		k;

	if (*prompt == '\0')
		return (NULL);
	s = ft_strjoin("/", prompt);
	k = 0;
	pa = seach_path(envp);
	if (!pa)
		return (NULL);
	argv = ft_split(pa, ':');
	free(pa);
	return (access_check(argv, s));
}
