/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:40:25 by keys              #+#    #+#             */
/*   Updated: 2023/02/26 12:12:16 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 1
#define READ 0

int	here_doc_exe(char *end)
{
	char	*line;
	int		rw[2];

	pipe(rw);
	while (1)
	{
		line = readline("here-document>");
		if (line == NULL)
			_err("bash: warning: here-document at line 41 delimited by end-of-file (wanted `EOF')");
		if (!line[0])
		{
			// dprintf(rw[1], "%s\n", line);
			// dprintf(fd, "%s\n", line);
			free(line);
			line = NULL;
			continue ;
		}
		if (strcmp(line, end) == 0)
		{
			free(line);
			break ;
		}
		// dprintf(fd, "%s\n", line);
		dprintf(rw[WRITE], "%s\n", line);
		free(line);
	}
	close(rw[WRITE]);
	// close(fd);
	// line = readline("here-document>");
	// write(fd, line, strlen(line));
	// free(line);
	// line = get_next_line(rw[READ]);
	return (rw[READ]);
}

void	here_documents(t_node *node)
{
	t_line	*line;
	int		rw_read;
	char	buf[255];

	// int		fd0;
	// int		fd1;
	// char	*buf;
	line = node->line;
	// fd0 = fcntl(0, F_DUPFD, 10);
	// fd1 = fcntl(1, F_DUPFD, 10);
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		else if (line->type == REDIRECT)
		{
			if (strncmp(line->token->word, "<<", 2) == 0)
			{
				line = line->next;
				rw_read = here_doc_exe(line->token->word);
				// buf = get_next_line(rw_read);
				read(rw_read, buf, 255);
				fwrite(buf, 1, strlen(buf), stdout);
				printf("\n");
				close(rw_read);
			}
			line = line->next;
			continue ;
		}
		line = line->next;
	}
	// dup2(fd0,0);
	// dup2(fd1,1);
}
