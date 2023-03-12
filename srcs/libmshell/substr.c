/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:26:49 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:55:49 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ans;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start || !len)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ans = malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, s + start, len + 1);
	return (ans);
}
