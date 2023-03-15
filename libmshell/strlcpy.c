/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:26:24 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:55:38 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	if (!src)
		return (0);
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	if (len <= dstsize - 1)
		ft_memmove(dst, src, len + 1);
	else
	{
		ft_memmove(dst, src, dstsize - 1);
		ft_bzero(&dst[dstsize - 1], 1);
	}
	return (len);
}
