/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:20:34 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:55:28 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;

	len = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	else
		ft_memmove(p, s1, len);
	ft_memset(p + len, '\0', 1);
	return (p);
}
