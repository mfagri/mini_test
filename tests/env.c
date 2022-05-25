#include "../mandatory/minishell.h"

void	test(char **env)
{
		int	i;
	int	j;

	i = -1;
	while (env[++i])
		i = i;
	env[i] = cpy (env[i], "yooooo");
	env[i + 1] = NULL;
	i = -1;
	while (env[++i])
		printf ("%s\n", env[i]);
}
int	main(int ac, char **av, char **env)
{
	test(env);
	system("leaks a.out");
}
