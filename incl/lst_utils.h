/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 09:58:17 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/21 16:07:15 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_UTILS_H
# define LST_UTILS_H

# include "minishell.h"

/* TOKEN */
t_token	*new_elem(char *str, int token_id);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, char *str, int token_id);
int		ft_lstsize(t_token *lst);
void	ft_print_tokens(t_token *token);
int		ft_lstdelnext(t_token *list);
void	ft_lstdelcur(t_token *list);

t_token	*ft_insert_elem(char *str, int token_id, t_token *tmp);

/* ENV */
t_env	*new_env_elem(char *name, char *value);
t_env	*ft_env_last(t_env *env);
void	ft_env_add_back(t_env **env, char *name, char *value);
int		ft_env_delnext(t_env *list);
int		ft_print_env_lst(t_env *env, int n);
char	**env_to_array(t_env *env);
int		ft_envsize(t_env *env);

/* CMDS */
t_cmd	*new_cmd_elem(char **arg, char **redir);
t_cmd	*ft_cmd_last(t_cmd *cmd);
void	ft_cmd_add_back(t_cmd **cmd, char **arg, char **redir);
int		ft_cmd_delnext(t_cmd *list);
void	ft_print_cmd_lst(t_cmd *cmd);
int		cmd_lst_size(t_cmd *cmd);

void	ft_print_tab(char **tab);

#endif
