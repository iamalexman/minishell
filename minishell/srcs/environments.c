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

int	ft_env_lstsize(t_env *envp)
{
	t_env	*tmp;
	int		i;
	i = 0;
	tmp = envp;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	env_list_to_array(t_env *envp, char ***env)
{
	int		i;
	int		len;
	char	**tmp;

	if (*env)
	{
		free(*env);
		*env = NULL;
	}
	len = ft_env_lstsize(envp);
	if (!len)
		return (1);
	*env = malloc(sizeof(char*) * (len + 1));
	if (!*env)
		return (1);
	i = -1;
	while(++i < len)
	{
		(*env)[i] = ft_strdup(envp->key);
		if (*envp->sep)
		{
			tmp = ft_strjoin((*env)[i], envp->sep);
			free((*env)[i]);
			(*env)[i] = *tmp;
		}
		if (*envp->value)
		{
			tmp = ft_strjoin((*env)[i], envp->value);
			free((*env)[i]);
			(*env)[i] = *tmp;
		}
		envp = envp->next;
	}
	(*env)[i] = NULL;
	return (0);
}

