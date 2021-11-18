#include "minishell.h"

char *ft_cmd_gap2(char *str, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	while(str[++(*i)])
	{
//		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' || str[*i + 1] == '\\'))
//			str = ft_jump(str, i);
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
//	printf("tmp = %s\n", tmp);
//	free(str);
	return (tmp);
}

char *ft_cmd_gap(char *str, int *i)
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
//		printf("tmp = %s\n", tmp);
//		free(str);
	return (tmp);
}

void	ft_add_cmd(char *str, int *i, t_cmd *cmd, int *num)
{
	int	k;

	k = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
	{
		if (str[k] == '\'')
			ft_gap(str, i);
		else if (str[k] == '\"')
			ft_gap2(str, i);
		else
			(*i)++;
	}
	cmd->cmd[*num] = ft_substr(str, k, *i - k);
	(*num)++;
	cmd->cmd[*num] = NULL;
}

void	ft_cmd_redirect(char *str, int *i, t_arg *arg, int n)
{
	t_red	*red;
	int		k;

	red = malloc(sizeof(t_red));
	red->limiter = NULL;
	red->two = 0;
	red->cmd = n;
	red->next = NULL;
	red->in = 0;
	if (str[(*i)++] == '<')
		red->in = 1;
	if (str[*i] == '<' || str[*i] == '>')
	{
		red->two = 1;
		(*i)++;
	}
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] && str[*i] != '|' && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>')
	{
		k = *i;
		while (str[*i] && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>' && str[*i] != '|')
		{
			if (str[*i] == '\'')
				ft_gap(str, i);
			else if (str[*i] == '\"')
				ft_gap2(str, i);
			else
				(*i)++;
		}
		red->name = ft_substr(str, k, *i - k);
	}
	ft_red_add_back(&arg->red, red);
}

void	ft_add_data(int *i, char *str, t_arg *arg, int n)
{
	t_cmd	*cmd;
	int		num;
	int		j;

	cmd = arg->cmd;
	j = 0;
	while (j++ < n)
		cmd = cmd->next;
	j = 0;
	num = 0;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] == ' ')
			(*i)++;
		else if (str[*i] == '<' || str[*i] == '>')
			ft_cmd_redirect(str, i, arg, n);
		else
			ft_add_cmd(str, i, cmd, &num);
	}
}

void	ft_clean_quotes(char **str)
{
	int i;

	i = 0;
	while(*str[i])
	{
		if (*str[i] == '\'')
			ft_cmd_gap(*str, &i);
		else if (*str[i] == '\"')
			ft_cmd_gap2(*str, &i);
		else
			i++;
	}
}

void	ft_clean_cmd(t_cmd **cmd)
{
	int		i;

	while (*cmd)
	{
		i = 0;
		while ((*cmd)->cmd[i])
		{
			ft_clean_quotes(&(*cmd)->cmd[i]);
			i++;
		}
		*cmd = (*cmd)->next;
	}
}

void	parser(char *str, t_arg *arg, char **env)
{
	int		i;
	int		n;
	t_cmd	*tmp;
	t_red	*tmp2;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		while(str[i] && str[i] != '|')
		{
			tmp = ft_make_node(str, &i);
			ft_node_add_back(&arg->cmd, tmp);
		}
		if (!str[i])
			break ;
		else
			i++;
	}
	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			n++;
		}
		else
			ft_add_data(&i, str, arg, n);
	}
	ft_clean_cmd(&arg->cmd);

	tmp = arg->cmd;
	while(tmp)
	{
		i = 0;
		while(tmp->cmd[i])
		{
			printf("%s\n", tmp->cmd[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
	i = 0;
//	tmp2 = arg->red;
//	while(tmp2)
//	{
//		printf("name: %s\n", tmp2->name);
//		printf("limiter: %s\n", tmp2->limiter);
//		printf("cmd: %d\n", tmp2->cmd);
//		printf("in: %i\n", tmp2->in);
//		printf("two: %d\n\n", tmp2->two);
//
//		tmp2 = tmp2->next;
//	}
	arg->errnum = 0;
}
