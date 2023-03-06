
// char	*ft_join_free(char *s1, char *s2, int flag1, int flag2)
// {
// 	char	*tmp;

// 	tmp = ft_strjoin(s1, s2);
// 	if (!tmp)
// 		_err("malloc");
// 	if (flag1)
// 		free(s1);
// 	if (flag2)
// 		free(s2);
// 	return (tmp);
// }

// size_t	num_(bool *dq, bool *sq, char *tmp)
// {
// 	size_t	num;

// 	num = 0;
// 	while (1)
// 	{
// 		if (*dq)
// 			tmp = strchr(tmp, '\"');
// 		if (*sq)
// 			tmp = strchr(tmp, '\'');
// 		if (tmp == NULL)
// 		{
// 			break ;
// 		}
// 		num++;
// 		tmp++;
// 	}
// 	return (num);
// }

// char	*readline_quate(bool *dq, bool *sq)
// {
// 	char	*new;

// 	if (*dq)
// 		new = readline("dquote>");
// 	else if (*sq)
// 		new = readline("quote>");
// 	return (new);
// }

