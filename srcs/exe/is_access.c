/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:45:28 by keys              #+#    #+#             */
/*   Updated: 2023/07/01 13:02:59 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *str)
{
	struct stat	buf;

	if (stat(str, &buf) != 0)
		return (0);
	return (S_ISDIR(buf.st_mode));
}

static int	is_file_accessible_utils(char *str, struct stat buf)
{
	if (ft_strchr(str, '/') != 0)
	{
		if (!(buf.st_mode & S_IXUSR))
		{
			_err_permission(str);
			return (true);
		}
		if (!(buf.st_mode & S_IRUSR))
			return (false);
		if (!(buf.st_mode & S_IWUSR))
			return (false);
		return (false);
	}
	else
	{
		_err_cmd_not_found(str);
		return (true);
	}
	return (true);
}

int	is_file_accessible(char *str)
{
	struct stat	buf;

	if (stat(str, &buf) < 0)
	{
		if (ft_strchr(str, '/') != 0)
		{
			_err_no_such_file(str);
			return (true);
		}
		return (false);
	}
	if (S_ISREG(buf.st_mode))
	{
		return (is_file_accessible_utils(str, buf));
	}
	return (false);
}
