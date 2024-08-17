/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:30:50 by sbansacc          #+#    #+#             */
/*   Updated: 2024/08/17 10:46:19 by sabansac         ###   ########.fr       */
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

char	*find_cmd_path(char *cmd, char **paths)
{
	char	*cmd_path;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	cmd_path = NULL;
	cmd_path = check_access(cmd, paths);
	return (cmd_path);
}

void	execv_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = NULL;
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		error_exit("Split", pipex);
	cmd_path = find_cmd_path(cmd_args[0], pipex->paths);
	if (!cmd_path)
	{
		if (ft_strchr(cmd_args[0], '/') || ft_strchr(cmd_args[0], '.'))
		{
			perror(cmd_args[0]);
			free_tab(cmd_args);
			clean_pipex(pipex);
			exit(EXIT_FAILURE);
		}
		free_tab(cmd_args);
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd_args, envp);
	free(cmd_path);
	free_tab(cmd_args);
	error_exit("Execve", pipex);
}

void	child_process(t_pipex *pipex, char **envp, int i)
{
	int		fd_infile;
	int		fd_outfile;
	int		j;

	if (i == 0)
	{
		fd_outfile = pipex->pipes_fds[i][1];
		fd_infile = pipex->fd_infile;
	}
	else if (i == (pipex->cmds_count) - 1)
	{
		fd_infile = pipex->pipes_fds[i - 1][0];
		fd_outfile = pipex->fd_outfile;
	}
	else
	{
		fd_infile = pipex->pipes_fds[i - 1][0];
		fd_outfile = pipex->pipes_fds[i][1];
	}
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	j = 0;
	while (j < pipex->pipes_count)
	{
		close(pipex->pipes_fds[j][0]);
		close(pipex->pipes_fds[j][1]);
		j++;
	}
	execv_cmd(pipex, pipex->cmds_list[i], envp);
}

void	init_pipes(t_pipex *pipex, char **av)
{
	int	i;

	pipex->cmds_count = 0;
	if (!(pipex->is_here_doc))
		pipex->cmds_list = av + 2;
	else if (pipex->is_here_doc)
		pipex->cmds_list = av + 3;
	while (pipex->cmds_list[pipex->cmds_count])
		pipex->cmds_count++;
	pipex->cmds_count--;
	pipex->pipes_count = pipex->cmds_count - 1;
	pipex->pipes_fds = NULL;
	pipex->pipes_fds = malloc(sizeof(int *) * pipex->pipes_count);
	if (!(pipex->pipes_fds))
		error_exit("Pipes", pipex);
	i = 0;
	while (i < pipex->pipes_count)
	{
		pipex->pipes_fds[i] = NULL;
		pipex->pipes_fds[i] = malloc(sizeof(int) * 2);
		if (!(pipex->pipes_fds[i]) || pipe(pipex->pipes_fds[i]) < 0)
			error_exit("Pipes", pipex);
		i++;
	}
}

void	pipex_bonus(t_pipex *pipex, char **av, char **envp)
{
	int	i;
	int	status;

	init_pipes(pipex, av);
	get_paths(pipex, envp);
	i = 0;
	pipex->pid = NULL;
	pipex->pid = malloc(sizeof(int) * pipex->cmds_count);
	if (!pipex->pid)
		return ;
	while (i < pipex->cmds_count)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			error_exit("Fork", pipex);
		if (pipex->pid[i] == 0)
			child_process(pipex, envp, i);
		i++;
	}
	i = 0;
	while (i < pipex->pipes_count)
	{
		close(pipex->pipes_fds[i][0]);
		close(pipex->pipes_fds[i][1]);
		i++;
	}
	i = 0;
	while (i < pipex->cmds_count)
	{
		if (wait(&status) == -1)
			error_exit("Wait", pipex);
		i++;
	}
	clean_pipex(pipex);
}
