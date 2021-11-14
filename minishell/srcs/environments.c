#include "minishell.h"

static t_env	*ft_env_lst_new(char *env)
{
	t_env	*node;
	int i;

	i = 0;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	while(env[i])
	{
		if (env[i] == '=')
		{
			node->key = ft_substr(env, 0, i);
			node->sep = ft_strdup("=");
			node->value = ft_substr(env, i + 1, ft_strlen(env));
			node->next = NULL;
		}
		i++;
	}
	return (node);
}

static t_env	*ft_env_lst_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	ft_env_lst_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst)
	{
		tmp = ft_env_lst_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	env_parse(char **env, t_env **envp)
{
	t_env 	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_env_lst_new(env[i]);
		ft_env_lst_add_back(envp, tmp);
		i++;
	}
}

