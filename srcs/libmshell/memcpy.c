/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:16:20 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:54:34 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*tmp;

	tmp = dst;
	if (dst == src || n == 0)
		return (dst);
	while (n-- != 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
	}
	return (tmp);
}
