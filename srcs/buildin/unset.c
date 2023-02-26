/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 07:41:39 by keys              #+#    #+#             */
/*   Updated: 2023/02/26 16:17:58 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// t_env	*find_variable(t_env *env, char *key)
// {
// 	t_env	*variable;
// 	t_env	*tmp;
// 	size_t	len;

// 	tmp = env;
// 	len = ft_strlen(key);
// 	while (1)
// 	{
// 		if (!ft_strncmp(tmp->key, key, len))
// 			break ;
// 		else if (!tmp->next)
// 			return (NULL);
// 		else
// 			tmp = tmp->next;
// 	}
// 	return (tmp);
// }

// void	unset_exception(t_data *data, t_env *variable)
// {
// 	t_env	*tmp;

// 	if ((!variable->prev))
// 	{
// 		data->env = variable->next;
// 	}
// 	else
// 	{
// 	}
// 	free(variable->key);
// 	free(variable->value);
// 	free(variable);
// }

// void	unset_variable(t_data *data, t_env *variable)
// {
// 	t_env	*prev;
// 	t_env	*next;
// 	t_env	*tmp;

// 	if (!variable->prev)
// 	{
// 		data->env = variable->next;
// 		data->env->prev = NULL;
// 	}
// 	else if (!variable->next)
// 		variable->prev->next = NULL;
// 	else
// 	{
// 		prev = variable->prev;
// 		next = variable->next;
// 		prev->next = next;
// 		next->prev = prev;
// 	}
// 	free(variable->key);
// 	free(variable->value);
// 	free(variable);
// }

// void	ft_unset(t_data *data, char *key)
// {
// 	t_env	*variable;

// 	variable = find_variable(data->env, key);
// 	if (!variable)
// 		return ;
// 	else
// 		unset_variable(data, variable);
// }
