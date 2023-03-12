/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:15:28 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:54:42 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	ch;

	tmp = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
		*tmp++ = ch;
	return (s);
}
