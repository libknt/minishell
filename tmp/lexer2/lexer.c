/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:16:08 by keys              #+#    #+#             */
/*   Updated: 2023/03/04 22:37:22 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ssize_t			wordlen(char *prompt);

// ssize_t	wordlen(char *prompt)
// {
// 	size_t	len;
// 	bool	dq;
// 	bool	sq;

// 	sq = false;
// 	dq = false;
// 	len = 0;
// 	if (is_ope(prompt))
// 		return (is_ope(prompt));
// 	if (is_redirect(prompt))
// 		return (is_redirect(prompt));
// 	while (1)
// 	{
// 		if (quate_flag(prompt, &len, &dq, &sq))
// 			continue ;
// 		if (!dq && !sq)
// 			if (is_ok(prompt, len))
// 				break ;
// 		if ((sq || dq) && prompt[len] == '\0')
// 			return (-1);
// 		len++;
// 	}
// 	return (len);
// }

// t_token_type	find_type(char *tmp)
// {
// 	if (strncmp(tmp, "||", 2) == 0 || strncmp(tmp, "&&", 2) == 0 || strncmp(tmp,
// 			";;", 2) == 0 || strncmp(tmp, "|&", 2) == 0 || strncmp(tmp, "&",
// 			1) == 0 || strncmp(tmp, ";", 1) == 0 || strncmp(tmp, "(", 1) == 0
// 		|| strncmp(tmp, ")", 1) == 0 || strncmp(tmp, "|", 1) == 0
// 		|| strncmp(tmp, "\n", 1) == 0)
// 		return (OP);
// 	return (WORD);
// }

// int	make_token(char **line, t_data_t *d)
// {
// 	size_t	i;

// 	i = 0;
// 	while (1)
// 	{
// 		while (is_blank(d->prompt[i]))
// 			i++;
// 		if (d->prompt[i] == '\0')
// 			break ;
// 		d->len = wordlen(&d->prompt[i]);
// 		if (d->len == -1)
// 			return (-1);
// 		else if (d->len == 0)
// 			break ;
// 		else
// 		{
// 			d->prompt = *line;
// 			d->word = strndup(&d->prompt[i], d->len);
// 			if (!d->word)
// 				_err("malloc");
// 			i += d->len;
// 			d->token = new_token(d->word, find_type(d->word));
// 			token_addback(&d->head, d->token);
// 		}
// 	}
// 	return (0);
// }

// t_token	*lexer(char **line, t_env *env)
// {
// 	t_token		*token;
// 	int			flag;
// 	t_data_t	data;

// 	data.prompt = *line;
// 	data.head = NULL;
// 	if (!*line[0])
// 		return (NULL);
// 	flag = make_token(line, &data);
// 	if (flag == -1)
// 	{
// 		_err_syntax("\"");
// 		return (NULL);
// 	}
// 	data.token = new_token(NULL, T_EOF);
// 	token_addback(&data.head, data.token);
// 	token = data.head;
// 	// expand(token);
// 	ex_toke(&token, env);
// 	return (token);
// }
