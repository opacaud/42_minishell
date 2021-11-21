/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_w_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboutier <cboutier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:08:37 by cboutier          #+#    #+#             */
/*   Updated: 2021/10/29 16:17:01 by cboutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_child(t_env **env, t_cmd *cmd, char *path, int file)
{
	char	**our_env_array;
	int		ret;

	ret = 0;
	our_env_array = NULL;
	if (cmd->arg[0][0] != '/' && !ft_isdigit(cmd->arg[0])
		&& cmd->arg[0][0] != '.')
		ret = check_path(*env, cmd->arg[0], &path);
	if (ret != 1)
	{
		path = ft_strdup(cmd->arg[0]);
		if (ft_strcmp(path, "./minishell") == 0)
		{
			*env = ft_update_shlvl(env);
			our_env_array = env_to_array(*env);
		}
		if (execve(path, cmd->arg, our_env_array) == -1)
			ft_execve_error(cmd, file);
	}
	if (path && cmd && cmd->arg)
		if (execve(path, cmd->arg, our_env_array) == -1
			&& ft_strcmp(path, "./minishell") != 0)
			exit(cmd_not_found(cmd, file));
	close_backup_exit(cmd);
}

int	ft_parent(pid_t pid, t_cmd *cmd, int file)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_exit_status = (WEXITSTATUS(status));
	if (file != -10)
	{
		reset_redir(cmd, file);
		close_me(file);
	}
	return (g_exit_status);
}

int	ft_fork_simple(t_env **env, t_cmd *cmd, char *path, int file)
{
	pid_t	pid;

	pid = fork();
	g_exit_status = 123456789;
	if (ft_has_heredoc(cmd->redir))
		g_exit_status = 147258369;
	if (pid == -1)
		return (-11);
	if (pid == 0)
		ft_child(env, cmd, path, file);
	else
		return (ft_parent(pid, cmd, file));
	return (0);
}

int	ft_simple_exec(t_cmd *cmd, t_token *list, t_env **env, int file)
{
	char	*path;
	int		ret;

	path = NULL;
	ret = 0;
	if (!cmd->arg || !cmd->arg[0])
		return (0);
	if (is_builtin(cmd->arg[0]))
		exec_builtin(cmd, list, env, file);
	else if (ft_strcmp(cmd->arg[0], " ") != 0 && *env)
	{
		if (ft_strlen(cmd->arg[0]) > 0 && cmd->arg[0]
			&& ft_strncmp(cmd->arg[0], "./", 2) != 0 && cmd->arg[0][0] != '/')
		{
			if (check_path(*env, cmd->arg[0], &path) != 1)
				return (cmd_not_found(cmd, file));
			free(path);
		}
		ret = ft_fork_simple(env, cmd, path, file);
		if (ret == -11)
			return (fork_failed());
	}
	return (0);
}

int	ft_simple_cmd(t_cmd *cmd, t_token *list, t_env **env)
{
	int		file;

	file = -10;
	cmd->backup_stdin = -1;
	cmd->backup_stdout = -1;
	if (!cmd)
		return (0);
	ft_set_backupstd(cmd);
	if (ft_count_pipes(list) == 0 && ft_count_chevrons(list) > 0)
		file = perform_redirs(cmd);
	if (file == -1)
		return (-3);
	if (ft_get_size_tab(cmd->arg) > 0 && ft_strcmp(cmd->arg[0], " ") != 0)
		ft_simple_exec(cmd, list, env, file);
	else
		reset_if_no_arg(cmd);
	if (file != -10)
		close_me(file);
	close(cmd->backup_stdin);
	close(cmd->backup_stdout);
	return (g_exit_status);
}
