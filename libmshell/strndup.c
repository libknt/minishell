/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:33:34 by keys              #+#    #+#             */
/*   Updated: 2023/06/23 12:09:08 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

char	*ft_strndup(const char *str, size_t n)
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
