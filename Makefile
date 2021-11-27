# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkassand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 18:12:03 by jkassand          #+#    #+#              #
#    Updated: 2021/11/27 01:24:42 by jkassand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= minishell.c heredoc.c pre_open.c cmd_utils.c pipe_utils.c \
			  free_arg.c pipex.c child.c \
			  v_empty.c v_free_cmd_red_env.c v_built_utils.c \
			  args_size.c cmd_add.c cmd_clean.c dollar.c env_funcs.c \
			  env_to_array.c \
			  funcs.c lib_funcs.c parser.c pre_parser.c red_funcs.c \
			  s_signals.c \
			  s_builtins.c s_builtins2.c s_builtins3.c s_shlvl.c

OBJS		= $(SRCS:.c=.o)

LIBDIR		= libft

LIBFT_LIB	= $(LIBDIR)/libft.a

LIB			= -L$(LIBDIR) -lft

NAME		= minishell

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -I

RDLN		= -lreadline -L ~/.brew/Cellar/readline/8.1.1/lib \
			  -I~/.brew/Cellar/readline/8.1.1/include

RM			= rm -f

%.o: %.c	Makefile minishell.h
			$(CC) $(CFLAGS)$(LIBDIR) -c $< -o $@

$(NAME):	$(LIBFT_LIB) $(OBJS)
			$(CC) $(CFLAGS)$(LIBDIR) $(OBJS) -o $(NAME) $(LIB) $(RDLN)

all:		$(NAME)

$(LIBFT_LIB):	tools ;

tools:
			make -C $(LIBDIR)

clean:		
			make clean -C $(LIBDIR)
			$(RM) $(OBJS) $(BOBJS)

fclean:		clean 
			make fclean -C $(LIBDIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re tools
