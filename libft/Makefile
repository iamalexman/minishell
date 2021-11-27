# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkassand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/19 17:17:12 by jkassand          #+#    #+#              #
#    Updated: 2021/11/13 23:00:24 by jkassand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		  ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		  ft_putnbr_fd.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
		  ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlcpy.c \
		  ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
		  ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		  ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c

BSRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS	= $(SRCS:.c=.o)

BOBJS	= $(BSRCS:.c=.o)

NAME	= libft.a

GCC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

%.o: %.c	Makefile libft.h
			$(GCC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			ar rcs $(NAME) $?

all:		$(NAME)

bonus:		$(OBJS) $(BOBJS)
			ar rcs $(NAME) $(OBJS) $(BOBJS)

clean:
			$(RM) $(OBJS) $(BOBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
