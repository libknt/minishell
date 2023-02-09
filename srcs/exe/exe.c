/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:58:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/09 18:08:54 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void _err(const char *e)__attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit(1);
}

int	exe(char *prompt)
{
	extern char	**environ;
	pid_t		pid;
	char *argv[] = {prompt, NULL};
	int			waitstatus;

	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		if(access(prompt,X_OK) == 0)
			execve(prompt, argv, environ);
		else{
			prompt = exec_filename(prompt);
			if(prompt != NULL)
				execve(prompt,argv,environ);
		}
		_err("execve");
	}
	else
	{
		wait(&waitstatus);
		return (WEXITSTATUS(waitstatus));
	}
	return 0;
}
