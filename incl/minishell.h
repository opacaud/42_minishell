/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 09:58:14 by cboutier          #+#    #+#             */
/*   Updated: 2021/11/01 09:27:45 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "structures.h"
# include "lst_utils.h"
# include "str_utils.h"

# define READ 0
# define WRITE 1

int		g_exit_status;

/* ARG_UTILS */
t_token	*ft_go_forward(t_token *list);
int		ft_count_arg(t_token *list, t_token *tmp, int counter);
t_token	*ft_go_to_arg_zero(t_token *list, char **arg);

/* CD_UTILS */
int		ft_is_in_env(t_env *env);
void	update_pwd_env(char *old, t_env *env, char *pwd, int i);
int		ft_update_pwd(char *old, t_env *env);
void	chdir_err(char **tab);

/* CHECK PATH */
char	**ft_get_path(t_env *env);
int		check_path(t_env *env, char *str, char **res);
int		ft_free_tab(char **tab);
char	**ft_split(char *s, char c);

/* FIRST TOKEN */
t_token	*make_first_pipe(char *line, int *ptr_i);
t_token	*make_first_chevron(char *line, int *ptr_i);
t_token	*make_first_quote(char *line, int *ptr_i);
int		ft_in_squote(char *line, int *ptr_i);
char	*ft_scan_env(char *str, char *line, int *ptr_i, t_env *env);
t_token	*make_first_env(char *line, int *ptr_i, t_env *env);
t_token	*ft_make_first_token(char *line, int *ptr_i, t_env *env);
int		ft_count_till_sep_env(char *line, int *ptr_i);
char	*ft_scan_env(char *str, char *line, int *ptr_i, t_env *env);

/* */
int		is_env_sep(char *line, int i);
int		is_sep(char *line, int i);
int		ft_which_token(char *str);
char	*ft_getstr_env_arg(char *line, int *ptr_i);
char	*ft_getstr_quote(char *line, int *ptr_i, char quote);
void	ft_add_unknown_tokens(t_token *list, char *line, int *ptr_i);
void	ft_add_unknown_tokens2(t_token *list, char *line, int *ptr_i, \
char *str);
void	ft_add_tokens2(t_token *list, char *line, int *ptr_i);
void	ft_add_tokens(t_token *list, char *line, int *ptr_i);
char	*ft_trim_first(t_token *list);
void	ft_scan_dquote(t_token *list);
int		is_quote_closed(char *str);
char	*ft_delete_quotes(char *str, int token_id);
char	*ft_res_without_quotes(int counter, char *str, char quote);
char	**lst_to_array(t_token *list);
int		ft_has_several_env(char *str);
char	*ft_getenv(char *str, t_env *env);
int		ft_count_till_egal(char *str);

/* CLEAN TOKENS */
void	ft_expand_path_with_env(t_token *list, t_env *env);
int		ft_clean_tokens(t_token *list, t_env *env);
void	ft_final_lap(t_token *list);
t_token	*ft_s_in_dquotes(t_token *list, t_token *real_first);
t_token	*ft_s_in_dquotes2(t_token *list, int *i);
char	*ft_isolate_non_quotes(t_token *list, int *i);
void	ft_clean_tokens_loop1(t_token *list);
t_token	*ft_clean_tokens_loop1_2(t_token *list);
void	ft_clean_tokens_loop1_3(t_token *list);
void	ft_clean_tokens_loop2(t_token *list, t_token *first);
void	ft_clean_tokens_loop3(t_token *list);
void	ft_clean_tokens_loop4(t_token *list, t_env *env);
void	ft_clean_tokens_loop4_2(t_token *list, t_env *env);
void	ft_clean_tokens_loop5(t_token *list, t_token *first, t_env *env);
void	ft_clean_tokens_loop5_2(t_token *list, t_env *env, int *joined);
void	ft_clean_tokens_loop6(t_token *list, t_token *first);
int		ft_clean_tokens_loop6_2(t_token *list, t_token *first);
int		ft_clean_tokens_loop6_3(t_token *first);
void	ft_clean_tokens_loop7(t_token *list);
void	ft_clean_tokens_loop8(t_token *list);
void	ft_clean_tokens_loop9(t_token *list);
void	ft_clean_tokens_loop9_2(t_token *list);
void	ft_clean_tokens_loop9_3(t_token *list, char *tmp1);

char	*ft_clean_env_value(char *str);
void	ft_env_in_dq_trad(t_token *list);

/* BUILTINS */
int		is_builtin(char *str);
int		ft_cd(t_token *list, t_env *env);
void	cd_home(t_env *env);
int		cd_home2(t_env *env, char **tab);
void	cd_old_pwd(t_env *env);

int		get_pwd(void);
int		ft_has_only_n(char *str);
t_token	*ft_second_echo_loop(t_token *list);
t_token	*ft_echo2(t_token *list, t_token **tmp, t_env *env);
t_token	*echo(t_token *list, t_env *env);
t_token	*ft_echo_n(t_token *list, int *n);
int		ft_echo(t_token *list, t_env *env);
int		ft_env(t_env **env, t_token *list, t_cmd *cmd);
void	ft_env2(t_env *env, char **tab_token, int *i);
void	ft_env_invalid_option(char **tab_token);
int		ft_env_name_has_space(char *str);
int		ft_export_env(t_env **env, char **tab_token, int i);
void	ft_export_env2(char **tab_token, t_env **env, int *i, char *name);
int		ft_unset_env(t_env *env, char **tab_token);
int		ft_check_export_name(char *tab_token);
int		ft_check_export_name2(char *tab_token);
void	ft_env_join(t_token *list, int *joined);
int		ft_calculate_pos(char *tab_token);
int		ft_check_name(char *name);
int		ft_export_error(char *tab_token, char *trimmed_tab);
int		ft_unset_error(char *tab_token, char *trimmed_tab);
int		print_file_error(char *str);
void	ft_execve_error(t_cmd *cmd, int file);
int		print_errno(t_cmd *cmd);
int		fork_failed_err(int **pipefds, int file, t_cmd *cmd, pid_t *pid);
int		heredoc_error(t_cmd *cmd);

int		ft_error_redir(t_cmd *cmd, int i);
int		reset_redir(t_cmd *cmd, int file);
int		ft_has_redir(char **redir);

t_env	*create_env_lst(char **envp);
char	*ft_find_env_value(char *str);
char	*ft_find_env_name(char *str, t_env *env);
char	*ft_find_env_name2(char *str, char *res, int repere);
int		ft_change_env(t_token *list, char *str);
t_token	*ft_change_env2(t_token *list, char *str);
t_token	*ft_change_env3(t_token *list, t_token *first, char *str, int *i);
void	ft_change_env_value(char *name, char *value, t_env *env);
t_token	*ft_split_export_egal(t_token *list);
t_env	*ft_update_shlvl(t_env **env);
t_env	*ft_shlvl(t_env *env);

int		ft_exit(t_token *list, t_cmd *cmd);
void	close_fds(int file, t_cmd *cmd);
void	close_backup_exit(t_cmd *cmd);
int		ambiguous_redir(t_cmd *cmd);

/* EXEC */
int		ft_count_pipes(t_token *list);
int		ft_count_chevrons(t_token *list);

t_token	*ft_fill_arg_redir(t_token *list, char **arg, char **redir, t_cmd *cmd);
t_token	*ft_fill_arg(t_token *list, char ***arg, int *i);
t_cmd	*create_cmds(t_token *list);
char	**ft_create_arg(t_token *list);
char	**ft_second_check_arg(t_token *list, char **arg, char **redir);
t_token	*ft_second_check_arg2(t_token *list, char **redir, int j);
int		ft_is_a_cmd(char *str, t_env **env);
int		ft_pipes(t_token *list, t_env *env, t_cmd *cmd);

/* SIMPLE CMDS */
int		ft_simple_cmd(t_cmd *cmd, t_token *list, t_env **env);
char	**ft_create_redir(t_token *list);

void	ft_clean_cmd(t_cmd *cmd);
void	ft_clean_cmd2(char **arg, char **res);
int		ft_redir_in_simple(t_cmd *cmd, int i);
int		ft_redir_out_simple(t_cmd *cmd, int i);
int		reset_redir(t_cmd *cmd, int file);
int		ft_set_backupstd(t_cmd *cmd);
void	reset_if_no_arg(t_cmd *cmd);
int		perform_redirs(t_cmd *cmd);
int		ft_has_heredoc(char **redir);
int		heredoc_open(t_cmd *cmd, int fd);
int		ft_redir_heredoc2(t_cmd *cmd, char *line, int i);
int		ft_redir_heredoc(t_cmd *cmd, int i);

void	exec_builtin(t_cmd *cmd, t_token *list, t_env **env, int file);
int		ft_has_dash(char *str);
int		ft_count_spaces(char **str);
int		ft_get_size_tab(char **tab);

/* SIGNAL */
void	signal_handler(int signal);
void	signal_handler2(int signal);
void	ft_exit_empty_line(void);

/* FREE */
void	ft_free_token_list(t_token *list);
void	ft_free_cmd_list(t_cmd *cmd);
void	ft_free_everything(t_token *list, t_cmd *cmd, char *line);
void	ft_free_env_list(t_env *env);
void	*free_str(char *str);
void	ft_close_free_pipefds(int file, t_cmd *cmd);
void	ft_free_tab_pipes(t_cmd *cmd, pid_t *pid);
int		ft_free_int_tab(int **tab);
void	ft_free_pipefds(t_cmd *cmd);

int		set_g_exit_status(int n, char *str);
int		dup2_failed(void);
int		cmd_not_found(t_cmd *cmd, int file);
t_token	*cmd_failed(char *str);
int		fork_failed(void);
int		check_path_failed(int file, t_cmd *cmd, t_cmd *first);
void	execve_failed(int file, t_cmd *cmd, pid_t *pid);

int		ft_check_name(char *name);

int		ft_cmd_with_pipes(t_cmd *cmd, t_env **env, t_token *list); ////
void	ft_create_nb_pipes(t_cmd *cmd, int nb_pipes, char **our_env_array);
void	ft_env_array_in_cmd(t_cmd *cmd, char **our_env_array);

void	close_me(int fd);

/* PIPES */
void	ft_env_array_in_cmd(t_cmd *cmd, char **our_env_array);
t_token	*ft_end_of_loop_pipes(t_token *list, char *path, t_cmd *cmd);
t_token	*ft_go_ahead_end_loop(t_token *list, t_cmd **cmd, int *i);
int		ft_pipe_loop(t_cmd *first, t_env *env, t_token *list, t_cmd *cmd);
int		ft_pipes(t_token *list, t_env *env, t_cmd *cmd);
int		ft_redir_in(t_cmd *cmd, int i);
int		ft_redir_out(t_cmd *cmd, int i);
void	ft_redir_in_or_heredoc_pipes(t_cmd *cmd, int *i, int *file, int *ret);
int		perform_redirs_pipes2(int *file, t_cmd *cmd, int *i, int ret);
int		perform_redirs_pipes(t_cmd *cmd);
int		ft_dup_pipefds(int i, int nb_pipes, int **pipefds);
int		ft_create_pipe(int i, int nb_pipes, int **pipefds);
int		**ft_calloc_pipefds(int nb_pipes);
int		ft_pipefds_in_cmd(t_cmd *cmd);
void	ft_parent_waiting(pid_t *pid, int nb_pipes, t_cmd *first);
int		ft_child_handle_redir(int nb_pipes, t_cmd *first, \
int **pipefds, t_cmd *cmd);
void	child_exec(t_cmd *cmd, t_cmd *first, int *file, t_token *list);
int		ft_check_path(t_cmd **cmd, t_env *env, t_token *list, int *i);
void	ft_heredoc_in_pipes(t_cmd *cmd);
int		ft_where_is_env(char *line, int i);
void	ft_get_env_in_heredoc(int *j, char *line, t_cmd *cmd, int fd);
void	ft_env_in_heredoc(char *line, int fd, t_cmd *cmd);
void	ft_env_in_cmd(t_env *env, t_cmd *cmd);
void	ft_launch(t_token *list, t_env *env, char *line, char **our_env_array);
void	ft_prelaunch(char *line, t_env *env, char **our_env_array);

#endif