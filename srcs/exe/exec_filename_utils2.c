/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_filename_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:30:10 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/12 20:59:12 by keys             ###   ########.fr       */
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
		_err_malloc();
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
		_err_malloc();
	ft_strlcpy(ans, s + start, len + 1);
	return (ans);
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
		_err_malloc();
	ft_strlcpy(p, s1, len_s1 + 1);
	ft_strlcat(p, s2, len_s1 + len_s2 + 1);
	return (p);
}
