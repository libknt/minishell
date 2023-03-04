#include "minishell.h"
/*
char	**env_sort(char *envp[])
{
	ssize_t i;
	ssize_t	j;
	char	*temp;

	i = 0;
	while(envp[i])
	{
		j = i;
		while(envp[j])
		{
			if(0 < strcmp(envp[i], envp[j]))
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

char	**make_env_args(t_env *env)
{
	ssize_t	i;
	ssize_t	num;
	char	**envp;

	num = 0
	while(env)
	{
		num++;
		env = env->next;
	}
	envp = malloc(sizeof(t_env *) * num);
	i = 0;
	while(i < num)
	{	
				
		i++;
	}

}

void	export(char *argv[], t_env **env)
{
	ssize_t	i;
	char	**envp;
	t_env	*env_node;

	if (!argv[1])
	{
		envp = make_env_args(*env);
		envp = env_sort(env);
		printf("declare -x ");
		printf("%s\n", envp[i]);
		return ;
	}

	i = 1;
	while(argv[i])
	{
		env_node = new_lstenv(argv[i]);
		if(!env_node)
			_err("env node error\n");
		ft_addback(env, env_node);
		i++;
	}
}
		
*/
			
		
