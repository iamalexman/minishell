/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:29:07 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 19:24:23 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp_h(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (1);
	}
	return (0);
}

static void	gnl(char **line, t_arg *arg)
{
	char	*end;
	char	*tmp;

	*line = ft_strdup("\0");
	end = ft_strdup("\0\0");
	if (!*line || !end)
		ft_exit(12, "malloc", arg);
	while (*end != '\n')
	{
		read(0, end, 1);
		if (*end == '\n')
			break ;
		tmp = ft_strjoin(*line, end);
		if (!tmp)
		{
			free(end);
			ft_exit(12, "malloc", arg);
		}	
		free(*line);
		*line = tmp;
	}
	free(end);
}

static void	write_file(char *name, int fd, char *line, t_arg *arg)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		ft_exit(errno, name, arg);
	if (write(fd, "\n", 1) == -1)
		ft_exit(errno, name, arg);
}

void	heredoc(char *name, char *limiter, t_arg *arg)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		ft_exit(errno, name, arg);
	i = 1;
	while (i)
	{
		write(1, "> ", 2);
		gnl(&line, arg);
		if (ft_strcmp_h(line, limiter))
			write_file(name, fd, line, arg);
		else
			i = 0;
		free(line);
	}
	close(fd);
}
