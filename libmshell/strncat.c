
#include "libmshell.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s2 < n)
		ft_strlcpy(&s1[len_s1], s2, len_s2 + 1);
	else
		ft_strlcpy(&s1[len_s1], s2, n + 1);
	return (s1);
}
