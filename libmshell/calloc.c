/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:11:38 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:53:24 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (SIZE_MAX / count < size)
		return (NULL);
	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	p = malloc(count * size);
	if (!p)
		return (NULL);
	else
		ft_bzero(p, count * size);
	return (p);
}
