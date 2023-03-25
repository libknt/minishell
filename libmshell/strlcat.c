/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:27:22 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:55:34 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	if (!(dst) && src && dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	if (!src)
		return (dst_len);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	if (src_len < dstsize - dst_len)
		ft_memmove(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memmove(dst + dst_len, src, dstsize - dst_len - 1);
		ft_memset(dst + dstsize, '\0', 1);
	}
	return (dst_len + src_len);
}
