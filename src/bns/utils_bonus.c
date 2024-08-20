/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 05:29:49 by sabansac          #+#    #+#             */
/*   Updated: 2024/08/20 05:43:36 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*check_access(char *cmd, char **paths)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	tmp = NULL;
	cmd_path = NULL;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (paths[i++])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		if (cmd_path)
			free(cmd_path);
	}
	return (NULL);
}

void	get_paths(t_pipex *pipex, char **envp)
{
	pipex->paths = NULL;
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp && ft_strncmp(*envp, "PATH=", 5) == 0)
	{
		pipex->paths = ft_split(*envp + 5, ':');
		if (!(pipex->paths))
			error_exit("Paths", pipex);
	}
}

static void	handle_command_not_found(char **cmd_args, t_pipex *pipex)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd(": Command not found\n", 2);
	free_tab(cmd_args);
	clean_pipex(pipex);
	exit(127);
}

static void	execute_command(char *cmd_path, char **cmd_args,
							char **envp, t_pipex *pipex)
{
	execve(cmd_path, cmd_args, envp);
	if (cmd_path)
		free(cmd_path);
	free_tab(cmd_args);
	error_exit("Execve", pipex);
}

void	execv_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		error_exit("Split", pipex);
	if (!cmd_args[1] && ft_strncmp(cmd_args[0], "sleep", 5) == 0)
	{
		ft_putstr_fd("usage: sleep seconds\n", 2);
		free_tab(cmd_args);
		exit(1);
	}
	cmd_path = check_access(cmd_args[0], pipex->paths);
	if (!cmd_path)
	{
		if (ft_strchr(cmd_args[0], '/') || ft_strchr(cmd_args[0], '.'))
		{
			free_tab(cmd_args);
			error_exit(cmd, pipex);
		}
		handle_command_not_found(cmd_args, pipex);
	}
	execute_command(cmd_path, cmd_args, envp, pipex);
}
