/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_filename.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:17:23 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 13:39:22 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	if (!src)
		return (0);
	len = strlen(src);
	if (dstsize == 0)
		return (len);
	if (len <= dstsize - 1)
		memmove(dst, src, len + 1);
	else
	{
		memmove(dst, src, dstsize - 1);
		bzero(&dst[dstsize - 1], 1);
	}
	return (len);
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
	ft_strlcpy(ans, s + start, len + 1);
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	if (!(dst) && src && dstsize == 0)
		return (strlen(src));
	dst_len = strlen(dst);
	if (!src)
		return (dst_len);
	src_len = strlen(src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	if (src_len < dstsize - dst_len)
		memmove(dst + dst_len, src, src_len + 1);
	else
	{
		memmove(dst + dst_len, src, dstsize - dst_len - 1);
		memset(dst + dstsize, '\0', 1);
	}
	return (dst_len + src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	p = malloc(len_s1 + len_s2 + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, len_s1 + 1);
	ft_strlcat(p, s2, len_s1 + len_s2 + 1);
	return (p);
}

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
char	*exec_filename(char *prompt, char **envp)
{
	char	*pa;
	char	*s;
	char	**tmp;
	int		k;

	if (*prompt == '\0')
		return (NULL);
	s = ft_strjoin("/", prompt);
	k = 0;
	pa = seach_path(envp);
	if (!pa)
		return (NULL);
	tmp = ft_split(pa, ':');
	free(pa);
	while (tmp[k])
	{
		pa = tmp[k];
		tmp[k] = ft_strjoin(pa, s);
		free(pa);
		if (access(tmp[k], X_OK) == 0)
		{
			pa = ft_strdup(tmp[k]);
			ft_split_free(tmp);
			free(s);
			return (pa);
		}
		k++;
	}
	free(s);
	ft_split_free(tmp);
	return (NULL);
}
