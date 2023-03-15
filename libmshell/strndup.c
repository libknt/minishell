/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:33:34 by keys              #+#    #+#             */
/*   Updated: 2023/03/15 12:24:53 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

char	*strndup(const char *str, size_t n)
{
	size_t	len;
	char	*p;

	len = ft_strlen(str);
	if (len <= n)
		return (ft_strdup(str));
	p = ft_calloc(n + 1, sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, str, n);
	return (p);
}
