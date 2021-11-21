/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:34:53 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/26 11:33:50 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_UTILS_H
# define STR_UTILS_H

# include "minishell.h"

int		ft_strlen(char *str);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *str);
char	*ft_strndup(char *str, int start, int counter);
char	*ft_charjoin(char *s1, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char c);
char	*ft_tolower(char *str);
char	*ft_strchr(char *str, int c);
int		ft_atoi(char *str);
int		ft_isdigit(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_get_size_tab(char **tab);
char	*ft_itoa(int nb);
char	*ft_strncpy(char *src, char *dest, unsigned int n);
char	*ft_strcpy(char *src, char *dest);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	ft_putnbr_fd(int n, int fd);
int		ft_has_env(char *str);
int		ft_has_squote(char *str);
int		ft_has_null(t_token *list);
int		ft_has_several_env(char *str);
int		ft_has_slash(char *str);
char	*ft_trim_first_arg(char *str);
int		ft_join_remaining(t_token *list);
int		ft_join_remaining_env(t_token *list);
void	ft_putchar_fd(char c, int fd);
t_token	*ft_dup_and_join(t_token *list);
int		ft_is_redir(char *str);
int		ft_env_name_has_space(char *str);
int		ft_has_space(char *str);
int		ft_start_with_slash(char *str);
void	ft_sort_tab(char **env, int size);
int		ft_in_squote(char *line, int *ptr_i);

#endif