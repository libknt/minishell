/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:12:45 by marai             #+#    #+#             */
/*   Updated: 2023/03/12 19:54:27 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

static int	ft_calcdigit(int tmp)
{
	int	digit;

	digit = 0;
	if (tmp == 0)
		return (1);
	while (tmp)
	{
		tmp /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	int		digit;
	int		sign;
	char	*dst;

	sign = 1;
	digit = ft_calcdigit(n);
	if (n < 0)
	{
		digit++;
		sign = -1;
	}
	dst = malloc(sizeof(char) * (digit + 1));
	if (dst == NULL)
		return (NULL);
	dst[digit] = '\0';
	if (n == 0)
		dst[0] = '0';
	while (n)
	{
		dst[--digit] = sign * (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		dst[0] = '-';
	return (dst);
}
