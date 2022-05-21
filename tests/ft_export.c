/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:10:26 by mfagri            #+#    #+#             */
/*   Updated: 2022/05/21 20:17:51 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	int		j;
	char	*a;

	i = strlen(s1) + strlen(s2);
	j = 0;
	k = 0;
	a = malloc(i + 1);
	if (a == 0)
		return (0);
	while (s1 && s1[j] != '\0')
	{
		a[j] = s1[j];
		j++;
	}
	while (s2 && s2[k] != '\0')
		a[j++] = s2[k++];
	a[j] = '\0';
	if (s1)
		free (s1);
	return (a);
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
		printf("\n%s\n",name);
	value = malloc(ft_strlen(arg[1]) - i + 1);
	j = 0;
	i++;
	if(arg[1][i] == '=')
		i++;
	while(arg[1][i])
		value[j++] = arg[1][i++];
	value[i] = '\0';
	printf("\n%s\n",value);
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
		ret[i] = cpy (ret[i], env[i]);	
	}
	if(j != 123456)
	{
		ret[i] = cpy (ret[i], f);
		i++;
	}
	ret[i] = NULL;
	i = 0;
	while(ret[i])
		printf("%s\n",ret[i++]);
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
		return(NULL);
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
				printf("error\n");
				return(NULL);
			}
			env = add_to_env(arg,env);
		}
		else if (arg[i][j] == '=')
			printf("new\n");
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
			if(strncmp(env[i],env[j],strlen(env[i])) > 0)
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