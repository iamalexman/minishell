#include "minishell.h"


void	ft_init_structs(t_arg *arg)
{
	arg->cmd = NULL;
	arg->red = NULL;
	arg->fd = NULL;
	arg->env = NULL;
	arg->errnum = 0;
	arg->num = 0;
}

int ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return 1;
	return 0;
}

//char *ft_gap2_old(char *str, int *i)
//{
//	int j = *i;
//	char *tmp;
//	char *tmp2;
//	char *tmp3;
//
//	while(str[++(*i)])
//	{
//		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' || str[*i + 1] == '\\'))
//			str = ft_slesh(str, i);
//		if (str[*i] == '\"')
//			break ;
//	}
//	tmp = ft_substr(str, 0, j);
//	tmp2 = ft_substr(str, j + 1, *i - j - 1);
//	tmp3 = ft_strdup(str + *i + 1);
//	tmp = ft_strjoin(tmp, tmp2);
//	tmp = ft_strjoin(tmp, tmp3);
//	printf("tmp = %s\n", tmp);
//	free(str);
//	return (tmp);
//}

//char *ft_gap_old(char *str, int *i)
//{
//	int j;
//	char *tmp;
//		char *tmp2;
//		char *tmp3;
//
//	j = *i;
//	while(str[++(*i)])
//		if (str[*i] == '\'')
//			break ;
//		tmp = ft_substr(str, 0, j);
//		tmp2 = ft_substr(str, j + 1, *i - j - 1);
//		tmp3 = ft_strdup(str + *i + 1);
//		tmp = ft_strjoin(tmp, tmp2);
//		tmp = ft_strjoin(tmp, tmp3);
//		printf("tmp = %s\n", tmp);
//		free(str);
//	return (tmp);
//}

//void	ft_space(char *str, int i, t_arg **arg)
//{
//	*arg = ft_args_lst_new(str);
//}

//void	ft_space(char *str, int i, t_arg **arg)
//{
//	*arg = ft_args_lst_new(str);
//}

char *ft_dollar(char *str, int *i, char **env)
{
	int j;
	int k;
	char *tmp;
	char *tmp2;
	int z;

	j = *i;
	z = 0;
	k = -1;
	while(str[++(*i)])
		if (!ifkey(str[*i]))
			break ;
	if (*i == j + 1)
		return (str);
	tmp = ft_substr(str, j + 1, *i - j - 1);
	while (env[++k])
	{
		if (strstr(env[k], tmp)) // change strstr system func to my own
		{
			while(env[k][z] && env[k][z] != '=')
				z++;
			tmp2 = ft_substr(env[k], 0, z);
			if (ft_strcmp(tmp, tmp2) == 0)
				break ;
		}
	}
	tmp2 = ft_substr(env[k], z + 1, ft_strlen(env[k]) - z);
	// change key (delete) on value after '='
	return (str);
}

char *ft_jump(char *str, int *i)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
//	free(str);
	++(*i);
	return (tmp);
}

int		pre_parse(char *str)
{
	// <>, ><, ||, >>>, <<< non valid symbols
	int i;
	char c;

	c = '\0';
	i = -1;
	while(str[++i])
	{
		if (str[i] == '<' && str[i + 1] == '>')
			return (1);
		if (str[i] == '>' && str[i + 1] == '<')
			return (1);
		if (str[i] == '|' && str[i + 1] == '|')
			return (1);
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (1);
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (1);
	}
	return 0;
}

int main(int argc, char **argv, char **env)
{
	t_env	*envp;
//	t_cmd	*cmd;
	t_cmd	*tmp;
//	t_red	*tmp2;
//	t_red	*red;
	t_arg	arg;
	int		i;
	char	*str;
	char	 **array;

	array = NULL;
	str = "\'aaa\'";
//	str = " m |2 fee ";
	i = 0;
	envp = NULL;
//	if (argc != 2)
//		return (0);
	ft_init_structs(&arg);
	env_parse(env, &envp);
//	printf("%s\n\n", argv[1]);
	printf("%s\n\n", str);
	if (pre_parse(str) == 1)
		return (printf("PREPARSE_ERROR\n"));
	else
		parser(str, &arg, env);
//	printf("CMD\n\n");
//	печать команд с аргументами
//	tmp = arg->cmd;
//	while (tmp)
//	{
//		i = -1;
//		while (tmp->cmd[++i])
//			printf("%s\n", tmp->cmd[i]);
//		printf("\n");
//		tmp = tmp->next;
//	}
//	printf("IN\n\n");
//	//печать редиректов ОТКУДА - имя файла, номер команды, одинарный или двойной
//	tmp2 = cmd.in;
//	while (tmp2)
//	{
//		printf("%s\n%d\n%d\n\n", tmp2->name, tmp2->cmd, tmp2->two);
//		tmp2 = tmp2->next;
//	}
//
//	printf("OUT\n\n");
//	//печать редиректов КУДА - имя файла, номер команды, одинарный или двойной
//	tmp2 = cmd.out;
//	while (tmp2)
//	{
//		printf("%s\n%d\n%d\n\n", tmp2->name, tmp2->cmd, tmp2->two);
//		tmp2 = tmp2->next;
//	}
	return 0;
}
