#include "minishell.h"


void	ft_gap2(char *str, int *i)
{
	int		j;

	j = *i;
	while(str[j++])
	{
		if (str[j] == '\"')
		{
			*i = j + 1;
			break ;
		}
		else if (str[j] == '\0')
			*i += 1;
	}
}

void	ft_gap(char *str, int *i)
{
	int		j;

	j = *i;
	while(str[j++])
	{
		if (str[j] == '\'')
		{
			*i = j + 1;
			break ;
		}
		else if (str[j] == '\0')
			*i += 1;
	}
}

void	ft_dollar_parse(char *str, int *i)
{
	if (str[(*i)++] == '?')
		(*i)++;
	while(str[*i] && str[*i] != '|' && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\'')
			ft_gap(str, i);
		if (str[*i] == '\"')
			ft_gap2(str, i);
		else
		*i += 1;
	}
}

void	ft_redirect(char *str, int *i)
{
	(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
		(*i)++;
	while(str[*i] == ' ')
		(*i)++;
	while(str[*i] && str[*i] != '|' && str[*i] != ' ' && str[*i] != '<' && str[*i] != '>')
	{
		if (str[*i] == '\'')
			ft_gap(str, i);
		if (str[*i] == '\"')
			ft_gap2(str, i);
		else
			*i += 1;
	}
}
