/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:01:20 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/10 13:01:57 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
typedef strcut s_h t_h;

strcut s_h{
	char *e;
	t_h *next;
}

bool	is_heredoc(t_line *line)
{
	if (line->type == REDIRECT)
	{
		if (strncmp(line->token->word, "<<", 2) == 0)
			return (true);
	}
	return (false);
}

char	*rename(char *x)
{
	char	*file;

	x[0] = 'x';
	file = ft_strjoin(".", x);
	if (file == NULL)
		_err("malloc");
	free(x);
	return (file);
}

int	open_heredocfile(void)
{
	int		fd;
	char	*x;

	x = strdup(".x.heredoc");
	if (x == NULL)
		_err("malloc");
	while (1)
	{
		fd = open(x, O_EXCL | O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
		{
			x = rename(x);
			continue ;
		}
		else
			break ;
	}
	return (fd);
}

t_h  *new_heredoc(char *e)
{
	t_h *h;

	h = calloc(sizeof(t_h),1);
	if(!h)
		_err("malloc");
	h->e = strdup("e");
	if(!h->e)
		_err("malloc");
	h->next = NULL;
	return h;
}

t_h *heredoc_last(t_h *head)
{
	while(1)
	{
		if(head->next == NULL)
			break;
		head = head->next;
	}
	return head;
}

void heredoc_addback(t_h **head,t_h *new)
{
	t_h *last;

	if(head)
	{
		if(*head)
		{
			last = heredoc_last(*head);
			last->next = new;
		}
		else
			*head = new;
	}
}

void	heredoc_eof(t_line *line,t_h *head)
{
	t_h *new;

	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (is_heredoc(line))
		{
			line = line->next;
			new = new_heredoc(line->token->word);
			heredoc_addback(&head,new);
		}
		line = line->next;
	}
}

void _err_heredoc(char *m)
{
	printf("%s: warning: here-document at line 3 delimited by end-of-file (wanted `EOF')\n",m);
}

void	heredoc_start(int fd,t_h *head)
{
	char *line;
	while(1)
	{
		line = readline(">");
		if(line == NULL)
			_err_heredoc("minishell");
		if(strncmp(head->e,line) == 0)
		{
			if(head->next == NULL)
				break;
			else
				head = head->next;
		}
		dprintf(fd, "%s\n", line);
	}

}

int	heredoc(t_node *node)
{
	int	fd;
	t_h *head;

	head = NULL;
	heredoc_eof(node->line,head);
	if(head ==NULL)
		return 0;
	fd = open_heredocfile();
	heredoc_start(fd,head);
	dup2(fd,0);
	close(fd);
}
