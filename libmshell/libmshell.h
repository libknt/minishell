/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmshell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:56:19 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:00:38 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMSHELL_H
# define LIBMSHELL_H

# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_split_free(char **dst);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *str, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
long	ft_atol(const char *nptr);
int		ft_isalpha(int c);
int		ft_isspace(int c);

#endif
