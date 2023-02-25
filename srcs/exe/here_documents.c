/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_documents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:40:25 by keys              #+#    #+#             */
/*   Updated: 2023/02/25 19:53:13 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 1
#define READ 0

// void	ft_putchar_fd(char c, int fd)
// {
// 	write(fd, &c, 1);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	size_t	len;

// 	len = 0;
// 	if (!s)
// 		return ;
// 	len = ft_strlen(s);
// 	if (len <= INT_MAX)
// 		write(fd, s, len);
// 	else
// 	{
// 		write(fd, s, INT_MAX);
// 		ft_putstr_fd(&s[INT_MAX], fd);
// 	}
// }

int	here_doc_exe(char *end)
{
	char	*line;
	int		rw[2];

	// char	*file;
	// int		fd;
	// file = "file.txt";
	// printf("%s end\n", end);
	// fflush(stdout);
	pipe(rw);
	while (1)
	{
		// fd = open(file, O_WRONLY | O_APPEND);
		line = readline("here-document>");
		if (line == NULL)
			_err("bash: warning: here-document at line 41 delimited by end-of-file (wanted `EOF')");
		if (!line[0])
		{
			// write(rw[WRITE], line, strlen(line));
			// write(rw[WRITE], "\n", 1);
			dprintf(rw[1], "%s\n", line);
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
		// if (strncmp(line, end, 3) == 0)
		// 	break ;
		// dprintf(fd, "%s\n", line);
		dprintf(rw[1], "%s\n", line);
		// write(rw[WRITE], line, strlen(line));
		// write(rw[WRITE], "\n", 1);
		free(line);
	}
	close(rw[WRITE]);
	// close(fd);
	// line = readline("here-document>");
	// write(fd, line, strlen(line));
	// free(line);
	printf("line = %s\n", line);
	fflush(stdout);
	line = get_next_line(rw[READ]);
	printf("line = %s\n", line);
	fflush(stdout);
	return (rw[READ]);
	// return (1);
}

void	here_documents(t_node *node)
{
	t_line	*line;
	int		rw_read;

	// char	*str;
	line = node->line;
	// str = NULL;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		else if (line->type == REDIRECT)
		{
			if (strncmp(line->token->word, "<<", 2) == 0)
			{
				line = line->next;
				here_doc_exe(line->token->word);
				rw_read = here_doc_exe(line->token->word);
				(void)rw_read;
				// read(rw_read, str, 1000);
				// write(0, str, strlen(str));
				// close(rw_read);
				break ;
			}
			line = line->next;
			continue ;
		}
		line = line->next;
	}
}
