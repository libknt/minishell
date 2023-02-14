/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:58:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 09:12:39 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	tokensize(t_token *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
void	print_spl(char **argv)
{
	int	i;

	i = 0;
	printf("-------------------------------------\n");
	while (1)
	{
		if (argv[i] == NULL)
			break ;
		printf("%s\n", argv[i]);
		i++;
	}
	printf("-------------------------------------\n");
}
// t_token	*tmp;

// tmp = token;
// while (tmp)
// {
// 	if (!(tmp->next))
// 		break ;
// 	tmp = tmp->next;
// }
// return (tmp);

char	**make_arr(t_token *t)
{
	char	**arr;
	size_t	i;
	size_t	size;

	i = 0;
	size = tokensize(t);
	arr = malloc(sizeof(char **) * size);
	if (!arr)
		_err("malloc");
	while (1)
	{
		if (t->type == TK_EOF)
			break ;
		arr[i] = strdup(t->word);
		if (!arr[i])
		{
			ft_split_free(arr);
			_err("malloc");
		}
		i++;
		t = t->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	exe(t_token *token)
{
	extern char	**environ;
	pid_t		pid;
	char		**argv;
	char		*cmd_path;
	int			waitstatus;

	argv = make_arr(token);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		if (access(argv[0], X_OK) == 0)
			execve(argv[0], argv, environ);
		else
		{
			cmd_path = exec_filename(argv[0]);
			if (cmd_path != NULL)
				execve(cmd_path, argv, environ);
		}
		_err("execve");
	}
	else
	{
		ft_split_free(argv);
		wait(&waitstatus);
		return (WEXITSTATUS(waitstatus));
	}
	ft_split_free(argv);
	return (0);
}
