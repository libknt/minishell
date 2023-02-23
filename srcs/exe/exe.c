/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:58:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/23 22:52:55 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_redirect(int oldfd, t_node *node)
{
	int		fd;
	t_line	*line;

	line = node->line;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == REDIRECT)
		{
			fd = open(line->next->token->word, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
			if (oldfd != fd)
			{
				dup2(fd, oldfd);
				close(fd);
			}
			line = line->next;
		}
		line = line->next;
	}
}

int	exe(t_node *node)
{
	char		**argv;
	extern char	**environ;
	pid_t		pid;
	char		*cmd_path;
	int			waitstatus;

	argv = make_arr(node);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		_redirect(1,node);
		if (access(argv[0], X_OK) == 0)
			execve(argv[0], argv, environ);
		else
		{
			cmd_path = exec_filename(argv[0]);
			if (cmd_path != NULL)
				execve(cmd_path, argv, environ);
		}
		_err("execve: command not found");
	}
	else
	{
		wait(&waitstatus);
		free(argv);
		return (WEXITSTATUS(waitstatus));
	}
	return (0);
}
