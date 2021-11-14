#include "minishell.h"

void	ft_init_structs(t_arg **arg)
{
	*arg = malloc(sizeof(t_arg*));
	(*arg)->cmd = NULL;
	(*arg)->red = NULL;
}

int ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return 1;
	return 0;
}

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

char *ft_slesh(char *str, int *i) //не нужна для / но пока используется в ft_gap2
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
//	free(str);
	++(*i);
//	printf("tmp = %s\n", tmp);
	return (tmp);
}

char *ft_gap2(char *str, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	while(str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = ft_slesh(str, i);
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
//	printf("tmp = %s\n", tmp);
	free(str);
	return (tmp);
}

char *ft_gap(char *str, int *i)
{
	int j;
	char *tmp;
	char *tmp2;
	char *tmp3;

	j = *i;
	while(str[++(*i)])
		if (str[*i] == '\'')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
//	printf("tmp = %s\n", tmp);
	free(str);
	return (tmp);
}

int		pre_parse(char *str)
{
	// <>, ><, ||, >>>, <<< non valid symbols
	int i;

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

t_arg	*ft_delimeter(char *str, int *i, t_arg *arg)
{
	int j;

	j = 0;
	while(str[j])
	{
		if (str[j] == ' ')
			arg = ft_space(str, i, arg);
		j++;
	}
	return (arg);
}

void	ft_redirect(char *str, t_red *red, int i)
{
	//	<, >, <<, >>
}

void	parser(char *str, t_arg *arg, char **env)
{
	//     "", '', \, $, |, >, >>, < ' '
	int i;

//	*arg = malloc(sizeof(t_arg*));
//	(*arg)->cmd = NULL;
//	(*arg)->red = NULL;
	arg = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i);
//		if (str[i] == '\\')
//			str = ft_slesh(str, &i);
		if (str[i] == '\"')
			str = ft_gap2(str, &i);
		if (str[i] == '$')
			str = ft_dollar(str, &i, env);
//		if (str[i] == ' ')
//			str = ft_space(str, &i, arg);
		if (str[i] == '|')
			arg = ft_delimeter(str, &i, arg);
		if (str[i] == '<' || str[i] == '>')
			ft_redirect(str, arg->red, arg->red->cmd);
//		i++;
	}
	if (str[i] == '\0')
		arg = ft_delimeter(str, &i, arg);
}

int main(int argc, char **argv, char **env)
{
	t_env	*envp;
//	t_cmd	*cmd;
//	t_cmd	*tmp;
//	t_red	*tmp2;
//	t_red	*red;
	t_arg	*arg;
	int		i;

	i = -1;
	arg = NULL;
	envp = NULL;
//	if (argc != 2)
//		return (0);
	ft_init_structs(&arg);
	env_parse(env, &envp);
	printf("%s\n", argv[1]);
	if (pre_parse(argv[1]) == 1)
		return (printf("PREPARSE_ERROR\n"));
	else
		parser(argv[1], arg, env);
	while(arg)
	{
		printf("%s\n", arg->cmd->cmd[0]);
		arg->cmd = arg->cmd->next;
	}
	printf("CMD\n\n");
	//печать команд с аргументами
//	tmp = arg.cmd;
//	while (tmp)
//	{
//		i = -1;
//		while (tmp->cmd[++i])
//			printf("%s\n", tmp->cmd[i]);
//		printf("\n");
//		tmp = tmp->next;
//	}
//	printf("%s\n", argv[1]);
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
