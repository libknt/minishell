/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:02:27 by keys              #+#    #+#             */
/*   Updated: 2023/02/09 17:04:12 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisell.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;

	len = strlen(s1);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	else
		memmove(p, s1, len);
	memset(p + len, '\0', 1);
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ans;

	if (!s)
		return (NULL);
	if (strlen(s) <= start || !len)
		return (ft_strdup(""));
	if (strlen(s + start) < len)
		len = strlen(s + start);
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	strlcpy(ans, s + start, len + 1);
	return (ans);
}

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
		{
			ft_split_free(dst);
			return (NULL);
		}
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
		return (NULL);
	return (ft_get_split(dst, s, c));
}
