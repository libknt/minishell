/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_filename_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:30:10 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/11 21:42:19 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_free(char **dst)
{
	int	i;

	i = 0;
	if (dst)
	{
		while (dst[i])
		{
			free(dst[i]);
			i++;
		}
		free(dst);
	}
}

static size_t	ft_split_size(char const *s, char c)
{
	size_t	size;
	int		flag;

	flag = 0;
	size = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			size++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (size);
}

static size_t	ft_split_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != '\0' && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**ft_get_split(char **dst, char const *s, char c)
{
	int	index;

	index = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!(*s))
			break ;
		dst[index] = ft_substr(s, 0, ft_split_len(s, c));
		if (!dst[index])
			_err_malloc();
		while (*s != c && *s)
			s++;
		index++;
	}
	dst[index] = NULL;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;

	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (ft_split_size(s, c) + 1));
	if (!dst)
		_err_malloc();
	return (ft_get_split(dst, s, c));
}
