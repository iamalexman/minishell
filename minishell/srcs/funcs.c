#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (str1[i] == '\0' && i == 0)
		return (1);
	return (0);
}
