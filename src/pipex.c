/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:05:58 by sabansac          #+#    #+#             */
/*   Updated: 2024/08/16 08:11:41 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access(char *cmd, char **paths)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	tmp = NULL;
	cmd_path = NULL;
	while (paths[i])
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
		i++;
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;

	if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	if (*cmd == '/' || *cmd == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		perror(cmd);
		return (NULL);
	}
	paths = NULL;
	cmd_path = NULL;
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp && !ft_strncmp(*envp, "PATH=", 5))
	{
		paths = ft_split(*envp + 5, ':');
		if (!paths)
			return (NULL);
		cmd_path = check_access(cmd, paths);
		free_tab(paths);
		return (cmd_path);
	}
	perror(cmd);
	return (cmd_path);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = NULL;
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_tab(cmd_args);
		exit(127);
	}
	execve(cmd_path, cmd_args, envp);
	perror("Execve");
	free(cmd_path);
	free_tab(cmd_args);
	exit(EXIT_FAILURE);
}

void	fork_error(void)
{
	perror("Fork");
	exit(EXIT_FAILURE);
}

void	first_child_process(int *pipe_ends, int *fd_in_out, char *cmd1, char **envp)
{
	int		fd_infile;
	int		fd_outfile;

	fd_infile = fd_in_out[0];
	fd_outfile = fd_in_out[1];
	close(fd_outfile);
	close(pipe_ends[0]);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(pipe_ends[1]);
	exec_cmd(cmd1, envp);
	exit(EXIT_FAILURE);
}

void	last_child_process(int *pipe_ends, int *fd_in_out, char *cmd2, char **envp)
{
	int		fd_infile;
	int		fd_outfile;

	fd_infile = fd_in_out[0];
	fd_outfile = fd_in_out[1];
	close(fd_infile);
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	close(pipe_ends[0]);
	exec_cmd(cmd2, envp);
	exit(EXIT_FAILURE);
}

void pipex(int *pipe_ends, int *fd_infile_outfile, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	if (fd_infile_outfile[0] != -1)
	{
		pid1 = -1;
		pid1 = fork();
		if (pid1 < 0)
			fork_error();
		else if (pid1 == 0)
			first_child_process(pipe_ends, fd_infile_outfile, av[2], envp);
	}
	pid2 = -1;
	pid2 = fork();
	if (pid2 < 0)
		fork_error();
	else if (pid2 == 0)
		last_child_process(pipe_ends, fd_infile_outfile, av[3], envp);
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	if (fd_infile_outfile[0] != -1)
		waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
