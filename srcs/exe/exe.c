/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:58:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/20 15:32:17 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	line_size(t_line *line)
{
	size_t	len;

	len = 0;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == CMDLINE)
			len++;
		line = line->next;
	}
	return (len);
}

char	**make_arr(t_node *node)
{
	char	**arr;
	t_line	*line;
	size_t	len;
	size_t	i;

	arr = NULL;
	i = 0;
	line = node->line;
	len = line_size(line);
	printf("len = %ld\n", len);
	arr = malloc(len + 1);
	if (!arr)
		_err("malloc");
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		else if (line->type == CMDLINE)
		{
			arr[i] = line->token->word;
		}
		else
		{
			printf("%s\n", line->token->word);
		}
		line = line->next;
		i++;
	}
	arr[++i] = NULL;
	return (arr);
}

void	print_split(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		printf("sp = %s\n", t[i]);
		i++;
	}
}

int	exe(t_node *node)
{
	char	**argv;

	// extern char	**environ;
	// pid_t		pid;
	// char		*cmd_path;
	// int			waitstatus;
	argv = make_arr(node);
	printf("%s\n",argv[0]);
	printf("%s\n",argv[1]);
	printf("%s\n",argv[2]);
	printf("%s\n",argv[3]);
	printf("%s\n",argv[4]);
	// print_split(argv);
	// printf("fin\n");
	// fflush(stdout);
	// pid = fork();
	// if (pid < 0)
	// 	_err("fork");
	// else if (pid == 0)
	// {
	// 	if (access(argv[0], X_OK) == 0)
	// 		execve(argv[0], argv, environ);
	// 	else
	// 	{
	// 		cmd_path = exec_filename(argv[0]);
	// 		if (cmd_path != NULL)
	// 			execve(cmd_path, argv, environ);
	// 	}
	// 	_err("execve: command not found");
	// }
	// else
	// {
	// 	ft_split_free(argv);
	// 	wait(&waitstatus);
	// 	return (WEXITSTATUS(waitstatus));
	// }
	// (void)argv;
	// ft_split_free(argv);
	// free(argv);
	return (0);
}
