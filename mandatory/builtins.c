/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 04:30:33 by mfagri            #+#    #+#             */
/*   Updated: 2022/05/21 22:00:34 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
int     ft_check_n(const char *s1, const char *s2)
{
    size_t i;
    i = 0;
    if ((!s1 || !s2))
        return (1);
	if (s1[i] == '-')
	{
		i++;
		while (s1[i])
		{
			if (s1[i] != 'n')
				return 1;
			i++;
		}
		return (0);
	}
    return (1);
}
int ft_echo(char **pr)
{
	int		i;
	int		n_option;
	//int cpt;

	

	i = 1;
	n_option = 0;
	//cpt = 0;
	while (pr[i] && ft_check_n(pr[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (pr[i])
	{
		ft_putstr_fd(pr[i],1);
		if (pr[i + 1] && pr[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (1);
}
void ft_pwd()
{
	char s[100000];
	getcwd(s, sizeof(s));
	printf("%s\n",s);
	return ;
}

void ft_cd(char **pr)
{
	int i;
	
	i = chdir(pr[1]);
	printf("%d\n",i);
}
void ft_print_env(char **env)
{
	int i;
	
	i = 0;
	while(env[i])
	{
		ft_putstr_fd(env[i],1);
		write(1,"\n",1);
		i++;
	}
	return ;
}
int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122)
		|| (c >= 65 && c <= 90))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
int ft_do_nothing(char **arg)
{
	int j;
	int a;
	int n;
	a = 0;
	n = 0;
	j = 0;
	while (arg[1][j])
	{
		if(!(ft_isalpha(arg[1][j])) && (arg[1][j] != '_'))
		{
			break;
		}
		if(ft_isalpha(arg[1][j]))
		{
			a++;
		}
		if(arg[1][j] == '_')
			n++;
		j++;
	}
	if(n == 1 && a == 0)
	{
		return 1;
	}
	return 0;
}
char **add_new(char **arg,char **env)
{
	int i;
	char *name;
	char *value;
	char *p;
	char **ret;
	char *f;
	int j;
	i = 0;

	while(env[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	f = malloc(1);
	p = malloc(1);
	p[0] = '\0';
	f[0] = '\0';
	i = 0;
	while (arg[1][i] != '=')
		i++;
	name = malloc(i + 1);
	i =-1;
	while (arg[1][++i] != '=')
		name[i] = arg[1][i];
	name[i] = '\0'; 
		// printf("\n%s\n",name);
	value = malloc(ft_strlen(arg[1]) - i + 1);
	j = 0;
	i++;
	if(arg[1][i] == '=')
		i++;
	while(arg[1][i])
		value[j++] = arg[1][i++];
	value[i] = '\0';
	// printf("\n%s\n",value);
	f = ft_strjoin(f,name);
	f = ft_strjoin(f,"=");
	f = ft_strjoin(f,value);
	i = -1;
	while(env[++i])
	{
		if(!ft_strncmp(env[i],name,ft_strlen(name)))
		{
			// j = 123456;
			// ret[i] = cpy (ret[i], f);
			++i;
		}
		else
			ret[i] = cpy (ret[i], env[i]);	
	}
	ret[i] = cpy (ret[i], f);
	++i;
	ret[i] = NULL;
	return(ret);
}
char **add_to_env(char **arg,char **env)
{
	int i;
	char *name;
	char *value;
	char *p;
	char **ret;
	char *f;
	int j;
	i = 0;

	while(env[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	f = malloc(1);
	p = malloc(1);
	p[0] = '\0';
	f[0] = '\0';
	i = 0;
	while (arg[1][i] != '+')
		i++;
	name = malloc(i + 1);
	i =-1;
	while (arg[1][++i] != '+')
		name[i] = arg[1][i];
	name[i] = '\0'; 
		// printf("\n%s\n",name);
	value = malloc(ft_strlen(arg[1]) - i + 1);
	j = 0;
	i++;
	if(arg[1][i] == '=')
		i++;
	while(arg[1][i])
		value[j++] = arg[1][i++];
	value[i] = '\0';
	// printf("\n%s\n",value);
	f = ft_strjoin(f,name);
	f = ft_strjoin(f,"=");
	f = ft_strjoin(f,value);
	i = -1;
	while(env[++i])
	{
		if(!ft_strncmp(env[i],name,ft_strlen(name)))
		{
			j = 123456;
			p = ft_strjoin(p,env[i]);
			p = ft_strjoin(p,value);
		}
		else
			ret[i] = cpy (ret[i], env[i]);	
	}
	if(j != 123456)
	{
		ret[i] = cpy (ret[i], f);
		i++;
	}
	ret[i] = NULL;
	return(ret);
}
char **check_arg_export(char **arg,char **env)
{
	int i;
	int j;
	int k;
	j = 0;
	i = 1;
	if(!(ft_isalpha(arg[i][j])) && arg[1][j] != '_')
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (NULL);
	}
	while(arg[i][j])
	{
		if((ft_isalpha(arg[i][j])) || arg[i][j] == '_')
		{
			j++;
		}
		else
			break;
	}
	if(ft_do_nothing(arg))
		return(NULL);
	else
		if(arg[i][j] == '+')
		{
			if(arg[i][j+1] == '+')
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(arg[1], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return(NULL);
			}
			env = add_to_env(arg,env);
		}
		else if (arg[i][j] == '=')
			env = add_new(arg,env);
	i = 0;
	while(env[i])
		printf("%s\n",env[i++]);
	return(env);
}
char **ft_export(char **env,char **arg)
{
	int i;
	int j;
	int k;
	char **t;
	char **ret;
	i = 0;
	i = 0;
	while(env[i])
		i++;
	t = malloc(sizeof(char *) * (i + 1));
	ret = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(env[i])
	{
		j = 0 ;
		k = 0;
		while(env[j])
		{
			if(ft_strncmp(env[i],env[j],ft_strlen(env[i])) > 0)
				k++;
			j++; 
		}
		t[k] = cpy(t[k], env[i]);
		ret[i] = cpy(ret[i], env[i]);
		i++;
	}
	t[k + 1] = NULL;
	ret[i + 1] = NULL;
	i = 0;
	if(!arg[1])
	{
		while(t[i])
		{
			if (t[i][0])
				write (1, "declare -x ", 12);
			j = 0;
			while (t[i][j])
			{
				write(1, &t[i][j], 1);
				if(t[i][j] == '=')
					write (1, "\"", 1);
				j++;
			}
			write (1, "\"", 1);
			write (1, "\n", 1);
			i++;
		}
	}
	else
		ret = check_arg_export(arg,env);
	return (ret);
}