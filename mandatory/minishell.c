# include "minishell.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return (&((char *)s)[i]);
	return (NULL);
} 

int l;
struct termios	remove_ctlc(void)
{
	//int fd;
	//fd = open("file2",O_CREAT | O_RDWR,777);
	struct termios	terminal;
	struct termios	terminal2;

	tcgetattr(0, &terminal);
	terminal2 = terminal;
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW | TCSAFLUSH, &terminal);
	//tcsetattr(fd, TCSANOW | TCSAFLUSH, &terminal);
	return (terminal2);
}
char	*get_first(char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str && str[i] && str[i] != ' ')
		i++;
	ret = malloc (sizeof (char) * (i + 1));
	i = 0;
	while (str && str[i] && str[i] != ' ')
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

int	get_spaces(char *str)
{
	int		i;
	int		k;
	int		j;
	char	qu;

	j = 0;
	i = 0;
	k = 1;
	qu = 0;
	while (str[i])
	{
		if (((str[i] == ' ' && i != 0 && str[i + 1] && str[i + 1] != 39 && str[i + 1] != 34)
			&& (str[i + 1] != '>' || str[i + 1] != '<' || str[i + 1] != '|')) && k)
			j++;
		if (k && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			j = j + 2;
		if ((str[i] == 39 || str[i] == 34) && k)
		{
			k = 0;
			qu = str[i];
		}
		i++;
		if (!k && str[i] == qu)
		{
			j++;
			i++;
			k = 1;
		}
	}
	return (j + 1);
}

char	*get_arg(char *str, int i, int t)
{
	int		j;
	int		r;
	char	*ret;
	
	j = t;
	r = 0;
	while (++t <= i)
	{
		if (str[t] != ' ')
			r++;
	}
	ret = malloc (sizeof(char) * (r + 1));
	// printf ("%d\n", r);
	r = 0;
	t = j;
	while (++j <= i)
	{
		if (str[j] != ' ')
		{
			ret[r] = str[j];
			r++;
		}
	}
	ret[r] = '\0';
	return (ret);
}

int	check_next_qu(char *str, char c, int i)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_qu(char *str)
{
	int		i;
	int		k;
	int		j;
	char	u;
	char	*tmp;

	k = 0;
	j = 0;
	i = 0;
	u = 0;
	tmp = malloc (ft_strlen(str) - 1);
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == 34))
		{
			if (u && str[i] == u)
				k++;
			else if (!u && check_next_qu(str, str[i], i + 1))
			{
				u = str[i];
				k++;
			}
		}
		if (k < 2)
		{
			if (!u || (u && str[i] != u))
			{
				tmp[j] = str[i];
				j++;
			}
		}
		if (k >= 2)
		{
			k = 0;
			u = 0;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	**edit_qu(char **str)
{
	int		i;
	int		j;
	char	r;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		j = 0;
		r = 0;
		while (str[i][j])
		{
			if ((str[i][j] == 34 || str[i][j] == 39) && !r)
				r = str[i][j];
			else if (r && str[i][j] == r)
			{
				tmp = cpy(tmp, str[i]);
				free (str[i]);
				str[i] = remove_qu(tmp);
				free (tmp);
				break ;
			}
			j++;
		}
		i++;
	}
	return (str);
}

char	*get_var_2(char *str, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	char	*tmp;
	
	i = 0;
	j = 0;
	k = fork();
	if (!k)
		exit (0);
	if (!ft_strncmp(str, "$", ft_strlen(str)))
	{
		ret = ft_itoa(k);
		return (ret);
	}
	k = 0;
	tmp = cpy(tmp, str);
	str = ft_strjoin(tmp, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	while (env[i][j++] != '=');
	ret = malloc (sizeof (char) * (ft_strlen(env[i]) - j + 1));
	while (env[i][j])
		ret[k++] = env[i][j++];
	ret[k] = '\0';
	return (ret);
}

char	*get_var(char *str, char **env, int j)
{
	char	*tmp;
	char	*ret;
	char	*tmp2;
	int		i;
	int		k;

	i = 0;
	tmp = malloc (j + 1);
	while (str[i] && str[i] != '$')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	k = i + 1;
	while (str[i] != 34 && str[i])
	{
		i++;
		j++;
	}
	ret = cpy(ret, tmp);
	tmp2 = malloc (sizeof (char) * j);
	i = 0;
	while (str[k] && (ft_isalnum(str[k]) || str[k] == '$'))
	{
		tmp2[i++] = str[k++];
		if (ft_isdigit(str[k - i]) || str[k - 1] == '$')
			break ;
	}
	tmp2[k] = '\0';
	ret = ft_strjoin(ret, get_var_2(tmp2, env));
	free (tmp2);
	i = k;
	while (str[i++]);
	tmp2 = malloc(i - k);
	i = 0;
	while (str[k])
		tmp2[i++] = str[k++];
	tmp2[i] = '\0';
	ret = ft_strjoin(ret, tmp2);
	return (ret);
}

char	**edit_var(char **ret, char **env)
{
	char	*tmp;
	char	*var;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 1;
	while (ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			if (k && ret[i][j] == 39)
				k = 0;
			else if (!k && ret[i][j] == 39)
				k = 1;
			if (ret[i][j] == 34 && check_next_qu(ret[i], 34, j) && !k)
				k = 0;
			if (k && ret[i][j] == '$')
			{
				ret[i] = get_var(ret[i], env, j);
			}
			j++;
		}
		i++;
	}
	return (ret);
}

char	*sep(char *str)
{
	char	*ret;
	char	q;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	j = 1;
	while (str[i])
	{
		k++;
		if (str[i] == 34 || str[i] == 39)
		{
			if (j)
			{
				q = str[i];
				j = 0;
			}
			else
			j = 1;
		}		
		if (((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i + 1] != '<')) && j)
			k++;
		if (((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) && j)
		{
			k++;
			i++;
		}
		if (str[i] == '|' && j)
			k++;
		i++;
	}
	ret = malloc (sizeof (char) * (k));
	i = 0;
	k = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (j)
			{
				q = str[i];
				j = 0;
			}
			else
			j = 1;
		}		
		if (((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i + 1] != '<') || str[i] == '|') && j)
		{
			ret[k++] = ' ';
			ret[k] = str[i];
			k++;
			ret[k++] = ' ';
			i++;
		}
		if (((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) && j)
		{
			ret[k++] = ' ';
			ret[k] = str[i];
			k++;
			i++;
		}
		ret[k++] = str[i];
		i++;
	}
	ret[k] = '\0';
	return (ret);
}

int	get_t(char *tmp, int t)
{
	while (tmp[++t])
	{
		if (tmp[t] == ' ')
			break ;
	}
	return (t);
}

		// if (((tmp[i] == ' ' && tmp[i + 1] != ' ') || (tmp[i - 1] == '|')) || ((tmp[i - 1] == '>' || tmp[i - 1] == '<' || tmp[i - 1] == '|') && (tmp[i] != ' ' && tmp[i] != '>' && tmp[i] != '<'))
		// 	|| (((tmp[i - 1] == '>' && tmp[i] == '>') || (tmp[i - 1] == '<' && tmp[i] == '<')) && tmp[i + 1] != ' '))
		// {
		// 	if (((tmp[i - 1] == '<' && tmp[i] == '<') || (tmp[i - 1] == '>' && tmp[i] == '>')) && tmp[i + 1] != ' ')
		// 		i++;
		// 	if (!r && i != 0)
		// 	{
		// 		printf ("--------%c+%c\n", tmp[i - 1], tmp[i]);
		// 		ret[k++] = get_arg(tmp, i, t);
		// 		if (t != -1)
		// 			t = get_t(tmp, t);
		// 		else
		// 			t = i;
		// 	}
		// }
char	**get_command(char **env, int fd)
{
	char	*command;
	char	*tmp;
	char	*tmp2;
	char	**ret;
	int		i;
	int		k;
	char	r;
	int		t;

	k = 0;
	i = 0;
	t = -1;
	r = 0;
	
	tmp = readline("minishell=>");
	if (!tmp)
		return (NULL);
	add_history(tmp);
	write (fd, "\n", 1);
	write (fd, tmp, ft_strlen(tmp));
	ret = malloc (sizeof(char*) * (get_spaces(tmp) + 1));
	tmp2 = cpy(tmp2, tmp);
	free (tmp);
	tmp = sep(tmp2);
	free (tmp2);
	while (tmp[i])
	{
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			if (r && tmp[i] == r)
				r = 0;
			else
				r = tmp[i];
		}
		if ((tmp[i] == ' ' && tmp[i + 1] != ' '))
		{
			ret[k++] = get_arg(tmp, i, t);
			t = i;
			i++;
		}
		if (!tmp[i])
			break ;
		i++;
	}
	// k = -1;
	// while (tmp[++k])
	// 	printf ("%c-\n", tmp[k]);
	if (i - t - 1 > 0 && tmp[i - 1] != ' ')
	{
		ret[k++] = get_arg(tmp, i, t);
	}
	ret[k] = NULL;
	ret = edit_var(ret, env);
	ret = edit_qu(ret);
	free (tmp);
	return (ret);
}

char	**get_ret(char **pr, int i)
{
	static int	j = -1;
	int			k;
	char		**ret;

	ret = malloc (sizeof (char *) * (i - j + 1));
	k = 0;
	while (++j < i && pr[j])
	{
		ret[k] = cpy (ret[k], pr[j]);
		k++;
	}
	ret[k] = NULL;
	if (!pr[j])
		j = -1;
	return (ret);
}

char	***split_pr(char **pr)
{
	int		i;
	int		t;
	int		k;
	char	***ret;

	i = 0;
	k = 0;
	t = 0;
	if (!pr)
		return (NULL);
	while (pr[i])
	{
		if (!(ft_strncmp(pr[i], "|", ft_strlen(pr[i]))))
			k++;
		i++;
	}
	ret = malloc (sizeof (char **) * (k + 2));
	i = 0;
	k = 0;
	while (pr[i])
	{
		if (!(ft_strncmp(pr[i], "|", ft_strlen(pr[i]))))
		{
			ret[k] = get_ret(pr, i);
			k++;
		}
		i++;
	}
	ret[k++] = get_ret(pr, i);
	ret[k] = NULL;
	return (ret);
}

void	child_exec(char ***splited, char *path, int t, struct termios terminal2, char **env)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
	if(!(strcmp(splited[t][0],"export")))
		ft_export(env,splited[t]);
	else if(!(ft_strncmp(ft_strrchr(path,'/'),"/echo",ft_strlen("/echo"))))
		ft_echo(splited[t]);
	else if(!(ft_strncmp(ft_strrchr(path,'/'),"/pwd",ft_strlen("/pwd"))))
		ft_pwd(splited[t]);
	else if(!(ft_strncmp(ft_strrchr(path,'/'),"/env",ft_strlen("/env"))))
		ft_print_env(env);
	else
		execve(path, splited[t], env);
	exit(0);
}

int	remove_path_2(char *str)
{
	if (str[0] == '/' || str[0] == '.')
		return (1);
	return (0);
}

char	*remove_pwd(char **env, int i)
{
	char	*ret;
	int		k;

	k = 3;
	ret = malloc (sizeof(char) * (ft_strlen(env[i]) - 2));
	while(env[i][++k])
	{
		ret[k - 4] = env[i][k];
	}
	ret[k - 4] = '\0';
	return (ret);
}

char	*get_new_path(char **env, char *cmd)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = -1;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			break ;
		i++;
	}
	tmp = remove_pwd(env, i);
	i = 0;
	j = 0;
	ret = malloc (sizeof (char) * (ft_strlen(cmd) + ft_strlen(tmp) + 1));
	while (cmd[i])
	{
		if (i == 0 && cmd[i] == '.' && cmd[i + 1] == '/')
		{
			while (tmp[++k])
			{
				ret[j] = tmp[k];
				j++;
			}
			i++;
		}
		if (i == 0 && cmd[i] == '.' && cmd[i + 1] == '.' && cmd[i + 2] == '/')
		{
			while (tmp[++k])
			{
				ret[j] = tmp[k];
				j++;
			}
			while (ret[--j] != '/')
				ret[j] = '\0';
			j++;
			i = i + 2;
		}
		if (cmd[i])
			ret[j++] = cmd[i];
		i++;
	}
	ret[j] = '\0';
	if (!access(ret, F_OK))
		return (ret) ;
	free (ret);
	return (NULL);
}

int check_command(char **env, char *path, char ***splited, int t, int *fdd, int stdout, int fd)
{
	if (fd)
	{
		if (splited[t + 1])
			dup2(fdd[1], 1);
		else
			dup2(stdout, 1);
	}
	if(!(strcmp(splited[t][0],"export")))
	{
		if (fd)
			ft_export(env,splited[t]);
	}
	else if(!(strcmp(splited[t][0],"unset")))
	{
		if(fd)
			ft_unset(splited[t],env);
	}	
	else if(!(ft_strncmp(splited[t][0],"echo",ft_strlen("echo"))))
	{
		if (fd)
			ft_echo(splited[t]);
	}
	else if(!(ft_strncmp(splited[t][0],"pwd",ft_strlen("pwd"))))
	{
		if (fd)
			ft_pwd(splited[t]);
	}
	else if(!(ft_strncmp(splited[t][0],"cd",ft_strlen("cd"))))
	{
		if (fd)
			ft_cd(splited[t],env);
	}
	else if(!(ft_strncmp(splited[t][0],"env",ft_strlen("env"))))
	{
		if (fd)
			ft_print_env(env);
	}
	else
		return (1);
	return (0);
}

int	exec(int fd, char **env, struct termios terminal2)
{
	int		*r;
	int		k;
	int		t;
	int		stdout;
	int		stdin;
	int		pi;
	int		st = 1;
	char	**pr;
	int		fdd[2];
	char	***splited;
	char	*command;
	char	*path;

	path = malloc (1);
	pr = get_command(env, fd);
	splited = split_pr(pr);
	t = 0;
	pi = 1;
	stdin = dup(0);
	stdout = dup(1);
	// while (pr[++r])
	// {
	// 	printf ("%s\n", pr[r]);
	// 	free (pr[r]);
	// }
	// puts ("yooo");
	if (!splited)
	{
		write (1, "\033[1A\033[11Cexit\n", 14);
		return (0);
	}
	t = -1;
	while (splited[++t])
		t = t;
	r = malloc (sizeof (int) * (t));
	t = 0;
	while (splited[t])
	{
		// sleep (1);
		if (splited[pi])
			pipe(fdd);
		free (path);
		path = get_path(env, splited[t][0]);
		// printf ("%s\n", path);
		if (remove_path_2(splited[t][0]))
		{
			free (path);
			path = get_new_path(env, splited[t][0]);
		}
		if (!path && ft_strncmp("export", splited[t][0], ft_strlen(splited[t][0])) && ft_strncmp("unset", splited[t][0], ft_strlen(splited[t][0])))
		{
			printf ("minishell=> %s: command not found\n", splited[t][0]);
			get_glo(0);
		}
		r[t] = fork();
		if (check_command(env, path, splited, t, fdd, stdout, r[t]))
		{
			// write (2, "yoo\n", 4);
			if (!r[t])
			{
				if (splited[pi])
				{
					dup2(fdd[1], 1);
					close(fdd[0]);
					close(fdd[1]);
				}
				else
					dup2(stdout, 1);
				child_exec(splited, path, t, terminal2, env);
			}
		}
		else if (!r[t])
		{
			// write (2, "koo\n", 4);
			close(fdd[0]);
			close(fdd[1]);
			exit (0);
		}
		if (!splited[pi])
		{
			get_glo(1);
			remove_ctlc();
		}
		if (splited[pi])
		{
			dup2(fdd[0], 0);
			close(fdd[0]);
			close(fdd[1]);
			dup2(stdout, 1);
		}
		else
			dup2(stdin, 0);
		t++;
		pi++;
	}
	t = -1;
	while (r[++t])
		waitpid(r[t], NULL, 0);
	free (pr);
	t = 0;
	k = 0;
	while (splited[k])
	{
		t = 0;
		while(splited[k][t])
		{
			free (splited[k][t]);
			t++;
		}
		free (splited[k]);
		k++;
	}
	free (splited);
	dup2(stdout, 1);
	dup2(stdin, 0);
	return (1);
}

// int	exec(int fd, char **env, struct termios terminal2)
// {
// 	int		r;
// 	int		k;
// 	int		t;
// 	int		stdout;
// 	int		stdin;
// 	int		pi;
// 	int		st = 1;
// 	char	**pr;
// 	int		fdd[2];
// 	char	***splited;
// 	char	*command;
// 	char	*path;

// 	path = malloc (1);
// 	pr = get_command(env, fd);
// 	splited = split_pr(pr);
// 	t = 0;
// 	pi = 1;
// 	stdin = dup(0);
// 	stdout = dup(1);
// 	r = -1;
// 	// while (pr[++r])
// 	// {
// 	// 	printf ("%s\n", pr[r]);
// 	// 	free (pr[r]);
// 	// }
// 	// puts ("yooo");
// 	if (!splited)
// 	{
// 		write (1, "\033[1A\033[11Cexit\n", 14);
// 		return (0);
// 	}
// 	while (splited[t])
// 	{
// 		// sleep (1);
// 		if (splited[pi])
// 			pipe(fdd);
// 		free (path);
// 		path = get_path(env, splited[t][0]);
// 		// printf ("%s\n", path);
// 		if (remove_path_2(splited[t][0]))
// 		{
// 			free (path);
// 			path = get_new_path(env, splited[t][0]);
// 		}
// 		if (!path && ft_strncmp("export", splited[t][0], ft_strlen(splited[t][0])))
// 		{
// 			printf ("minishell=> %s: command not found\n", splited[t][0]);
// 			get_glo(0);
// 		}
// 		r = fork();	
// 		if (!r)
// 		{
// 			if (splited[pi])
// 			{
// 				dup2(fdd[1], 1);
// 				close(fdd[0]);
// 				close(fdd[1]);
// 			}
// 			else
// 				dup2(stdout, 1);
// 			child_exec(splited, path, t, terminal2, env);
// 		}
// 		else if (!splited[pi])
// 		{
// 			get_glo(1);
// 			waitpid(r, NULL, 0);
// 			remove_ctlc();
// 		}
// 		if (splited[pi])
// 		{
// 			dup2(fdd[0], 0);
// 			close(fdd[0]);
// 			close(fdd[1]);
// 			dup2(stdout, 1);
// 		}
// 		else
// 			dup2(stdin, 0);
// 		t++;
// 		pi++;
// 	}
// 	free (pr);
// 	r = 0;
// 	t = 0;
// 	while (splited[r])
// 	{
// 		t = 0;
// 		while(splited[r][t])
// 		{
// 			free (splited[r][t]);
// 			t++;
// 		}
// 		free (splited[r]);
// 		r++;
// 	}
// 	free (splited);
// 	dup2(stdout, 1);
// 	dup2(stdin, 0);
// 	return (1);
// }

// int	exec(int fd, char **env, struct termios terminal2)
// {
// 	int		r;
// 	int		k;
// 	char	**pr;
// 	char	*command;
// 	// char	**paths;
// 	char	*path;
// 	path = malloc (1);

// 	pr = get_command(env, fd);
// 	free (path);
// 	if (pr)
// 	{
// 		path = get_path(env, pr[0]);
// 		if (!path)
// 		{
// 			printf ("minishell=> %s: command not found\n", pr[0]);
// 			get_glo(0);
// 		}
// 		r = fork();	
// 		if (!r)
// 		{
// 			//g_globle.i = 0;
// 			tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
// 			// if(strcmp("echo",pr[0]) == 0)
// 			// {
// 			// 	ft_echo(pr);
// 			// }
// 			// else if(strcmp("pwd",pr[0]) == 0)
// 			// 	ft_pwd();
// 			// else if(strcmp("cd",pr[0]) == 0)
// 			// 	ft_cd(pr);
// 			// else
// 				execve(path, pr, NULL);
// 			exit(0);
// 		}
// 		else
// 		{
// 			//g_globle.i = 1;
// 			get_glo(1);
// 			waitpid(r, NULL, 0);
// 			remove_ctlc();
// 			//sleep(10);
// 		}
// 		r = -1;
// 		while (pr[++r])
// 			free (pr[r]);
// 		free (pr);
// 	}
// 	else
// 	{
// 		tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
// 		get_tt();
// 		//printf("\bexit\n");
// 		return (0);
// 	}
// 	return (1);
// }


void	get_env(char **env)
{
	int i;
	char	*tmp;
	int k;
	char *t;

	i = -1;
	while(env[++i])
	{
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			tmp = cpy (tmp, "SHLVL=");
			t = ft_strrchr(env[i], '=');
			t++;
			k = atoi(t);
			k++;
			tmp = ft_strjoin(tmp, ft_itoa(k));
			env[i] = cpy (env[i], tmp);
		}
		env[i] = cpy (env[i], env[i]);
	}
}
// char **get_env(char **env)
// {
// 	int i;
// 	int g;
// 	int k;
// 	char *t;
// 	char *l;
// 	i = -1;
// 	while(env[++i])
// 	{
// 		//printf("%s\n",env[i]);
// 		if(ft_strncmp(env[i],"SHLVL",5) == 0)
// 		{
// 			t = ft_strrchr(env[i],'=');
// 			t++;// printf("{%s}\n",t);
// 			k = atoi(t);
// 			k++;
// 			g = 0;
// 			// while (env[i][g])
// 			// {
// 			// 	if(env[i][g] == '=')
// 			// 	{
// 			// 		env[i][g+1] = *(ft_itoa(k));
// 			// 		break;
// 			// 	}
// 			// 	g++;
// 			// }	
// 			strcpy(env[i],"SHLVL=");
// 			l = ft_itoa(k);
// 			// while(env[i][g] != '=')
// 			// 	g++;
// 			// g++;
// 			// k = 0;
// 			// while(l[k])
// 			// 	env[i][g++] = l[k++];
// 			// env[i][g] ='\0';
// 			strcat(env[i], l);
// 			//ft_strjoin(env[i],ft_itoa(k));
// 			printf ("%s\n", env[i]);
// 		}
// 	}
// 	return (env);
// }

int	main(int ac, char **av, char **env)
{
	int	i;
	int		r;
	int k;
	t_main mmm;
	char	**pr;
	char	*command;
	char	*path;
	char	**env2;
	int		fd;
	struct termios terminal2;

	l = 1;
	path = malloc (1);
	fd = get_history();
	get_env(env);
	// get_env(env);
	// get_env(env);
	// i = 0;
	// while(env[i])
	// {
	// 	printf("%s\n",env[i]);
	// 	i++;
	// }
	//ft_export(env);
	terminal2 = remove_ctlc();
	signal(SIGINT, ft_sig);
	signal(SIGQUIT,ft_sig);
	r = 1;
	//waitpid(l, NULL, 0);
	k = 1;
	while (k)
	{
		//g_globle.i = 0;
		get_glo(0);
		k = exec(fd, env, terminal2);
	}
	if(k == 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal2);
		exit(0);
	}
	free (path);
}
