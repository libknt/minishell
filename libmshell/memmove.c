/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:17:08 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:54:38 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;
	size_t			i;

	if (len == 0 || dst == src)
		return (dst);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		tmp_dest = (unsigned char *)dst;
		tmp_src = (unsigned char *)src;
		i = len - 1;
		while (len-- > 0)
		{
			tmp_dest[i] = tmp_src[i];
			i--;
		}
	}
	return (dst);
}
