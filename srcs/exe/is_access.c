#include "minishell.h"

int is_directory(const char *str) {
    struct stat buf;

    if (stat(str, &buf) != 0)
        return 0;
    return S_ISDIR(buf.st_mode);
}


int is_file_accessible(char *str) {
	struct stat buf;

	if (stat(str, &buf) < 0)
		return false;
	if (S_ISREG(buf.st_mode)) {
        if(*str == '.' || *str == '/')
        {
			if (!(buf.st_mode & S_IXUSR)){
				_err_permission(str);
				return true;
			}
			if (!(buf.st_mode & S_IRUSR))
				return false;
			if (!(buf.st_mode & S_IWUSR))
				return false;
			return (false);
		}
        else
		{
			_err_cmd_not_found(str);
            return (true);
		}
		return true;
	}
	return false;
}
