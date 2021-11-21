/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 09:49:37 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:23:22 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

typedef enum e_symbols
{
	S_QUOTE = 1,
	D_QUOTE,
	S_LESS,
	D_LESS,
	S_GREATER,
	D_GREATER,
	PIPE,
	ARG,
	ENV,
	END_OF_ARG,
}	t_symbols;

typedef struct s_token
{
	char			*str;
	int				token_id;
	int				env_in_dq_trad;
	struct s_token	*next;

}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**arg;
	char			**redir;
	int				backup_stdout;
	int				backup_stdin;
	int				nb_pipes;
	char			**our_env_array;
	int				**pipefds;
	pid_t			*pid;
	t_env			*env;
	char			*path;
	struct s_cmd	*next;
}	t_cmd;

#endif
