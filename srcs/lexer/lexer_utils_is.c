/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_is.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:12:35 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 10:54:03 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

// static bool	is_metacharacter(char c)
// {
// 	char	*is;

// 	is = ft_strchr("|&;()<> \t", c);
// 	if (is == NULL)
// 		return (false);
// 	return (true);
// }

size_t	is_ope(char *line)
{
	if (ft_strncmp(line, "||", 2) == 0 || ft_strncmp(line, "&&", 2) == 0 \
	|| ft_strncmp(line, ";;", 2) == 0 || ft_strncmp(line, "|&", 2) == 0)
		return (2);
	if (ft_strncmp(line, "&", 1) == 0 || ft_strncmp(line, ";", 1) == 0 \
	|| ft_strncmp(line, "(", 1) == 0 || ft_strncmp(line, ")", 1) == 0 \
	|| ft_strncmp(line, "|", 1) == 0 || ft_strncmp(line, "\n", 1) == 0)
		return (1);
	return (0);
}

size_t	is_redirect(char *line)
{
	if ((ft_strncmp(line, "<<", 2) == 0) || (ft_strncmp(line, ">>", 2) == 0))
		return (2);
	if ((ft_strncmp(line, "<", 1) == 0) || (ft_strncmp(line, ">", 1) == 0))
		return (1);
	return (0);
}

bool	is_ok(char *prompt, size_t len)
{
	if (is_blank(prompt[len]) || (prompt[len] == '\0') \
	|| is_ope(&prompt[len]) || (ft_strncmp(&prompt[len], "<", 1) == 0) \
	|| (ft_strncmp(&prompt[len], ">", 1) == 0))
		return (true);
	return (false);
}
