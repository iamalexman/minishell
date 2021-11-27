/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:27:46 by jkassand          #+#    #+#             */
/*   Updated: 2021/11/27 01:27:51 by jkassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	part1(char **str, t_arg *arg)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	*str = readline("minishell$ ");
	if (*str == NULL)
	{
		write(1, "\033[Aminishell$ exit\n", \
				ft_strlen("\033[Aminishell$ exit\n"));
		rl_redisplay();
		ft_exit(0, NULL, arg);
	}
	if ((*str)[0])
		add_history(*str);
	if (empty_str(*str))
	{
		free(*str);
		return (1);
	}
	return (0);
}

void	part2(char *str, t_arg *arg)
{
	int		fd;

	parser(str, arg);
	set_built(arg->cmd);
	ft_env_list_to_array(arg->envp, &arg->env, arg);
	red_to_cmd(arg->red, arg->cmd);
	if (!pre_open(arg))
	{
		arg->num = count_cmd(arg->cmd);
		if (arg->num > 1)
			ft_pipe(arg);
		if (arg->num == 1 && arg->cmd->built)
		{
			fd = dup_built(arg->cmd, arg);
			arg->errnum = run_built(arg->cmd, arg);
			redup_built(fd, arg);
		}
		else if (arg->num != 1 || arg->cmd->cmd[0])
			pipex(arg);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_arg	arg;
	char	*str;

	(void)argv;
	ft_init_structs(&arg);
	if (argc != 1)
		ft_exit(1, NULL, &arg);
	env_parse(env, &arg.envp, &arg);
	ft_shlvl_check(&arg);
	while (1)
	{
		if (part1(&str, &arg))
			continue ;
		if (pre_parse(str) == 1)
		{
			write(2, "minishell: syntax error near unexpected token\n", 46);
			arg.errnum = 258;
		}
		else
			part2(str, &arg);
		free_str(&arg, str);
	}
	ft_exit(arg.errnum, NULL, &arg);
}
