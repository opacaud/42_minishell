# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/30 09:24:58 by cboutier          #+#    #+#              #
#    Updated: 2021/10/29 16:20:48 by cboutier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	= srcs

NAMES		= main.c check_path.c \
			make_first_token.c create_tokens.c \
			quotes1.c quotes2.c \
			ft_split.c \
			str_utils1.c str_utils2.c str_utils3.c str_utils4.c str_utils5.c \
			str_utils6.c str_utils7.c \
			lst_utils1.c lst_utils2.c \
			minishell.c \
			clean_tokens1.c clean_tokens2.c clean_tokens3.c clean_tokens4.c \
			clean_tokens5.c \
			lst_to_array.c \
			cd.c cd_utils.c pwd.c echo.c echo2.c echo_utils.c \
			create_env.c \
			env_lst_utils1.c env_lst_utils2.c \
			env_utils1.c env_utils2.c env_utils3.c env_utils4.c \
			exit.c \
			pipes.c pipefds.c exec_in_pipes.c \
			cmd_utils.c cmd_lst_utils.c \
			create_cmd.c clean_cmd.c \
			simple_cmd_w_redir.c redir_pipes.c\
			signal.c \
			free1.c free2.c\
			itoa.c \
			set_g_exit_status.c \
			define_tokens.c \
			join.c \
			exec.c \
			set_redir.c \
			s_in_dquotes.c \
			export_unset.c \
			error.c error2.c \
			create_redir.c create_arg.c check_arg.c \
			arg_utils.c \
			syntax_check.c \
			reset_redir.c \
			heredoc.c heredoc_env.c \
			prgm_utils.c \


SRCS		= $(addprefix $(SRCS_DIR)/, $(NAMES))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 #-fsanitize=address

INCLUDES	= -I incl/

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

RM			= rm -f

.c.o:
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -lreadline -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all re clean fclean
