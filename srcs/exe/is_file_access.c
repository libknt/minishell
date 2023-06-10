#include "minishell.h"

bool is_file_access(char *str)
{
	struct stat buf;

	if (stat(str, &buf) < 0)
		return (false);
	if (S_ISREG(buf.st_mode))
    {
        if(*str == '.' || *str == '/')
            return (false);
        else
            return (true);
    }
	return (false);
}
