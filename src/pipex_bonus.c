/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:30:50 by sbansacc          #+#    #+#             */
/*   Updated: 2024/08/15 09:11:32 by sabansac         ###   ########.fr       */
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
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
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
	if (*cmd == '/' || *cmd == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		perror(cmd);
		return (NULL);
	}
	cmd_path = NULL;
	cmd_path = check_access(cmd, paths);
	if (cmd_path)
		return (cmd_path);
	perror(cmd);
	return (cmd_path);
}

void	exec_cmd(t_pipex *pipex, char *cmd, char **envp)
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
	free(cmd_path);
	free_tab(cmd_args);
	error_exit("Execve", pipex);
}

void	child_process(t_pipex *pipex, char **envp, int i)
{
	int		fd_infile;
	int		fd_outfile;

	if (i == 0)
	{
		fd_outfile = pipex->pipes_fds[i][0];
		fd_infile = pipex->fd_infile;
	}
	else if (i == (pipex->cmds_count) - 1)
	{
		fd_infile = pipex->pipes_fds[i - 1][1];
		fd_outfile = pipex->fd_outfile;
	}
	else
	{
		fd_infile = pipex->pipes_fds[i - 1][1];
		fd_outfile = pipex->pipes_fds[i][0];
	}
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	exec_cmd(pipex, pipex->cmds_list[i], envp);
	exit(EXIT_FAILURE);
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
	(pipex->cmds_count)--;
	pipex->pipes_count = (pipex->cmds_count) - 1;
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
	int	pid;

	init_pipes(pipex, av);
	get_paths(pipex, envp);
	i = 0;
	while (i < pipex->cmds_count)
	{
		pid = fork();
		if (pid == -1)
			error_exit("Fork", pipex);
		if (pid == 0)
			child_process(pipex, envp, i);
		i++;
	}
	wait(NULL);
	clean_pipex(pipex);
}
/*
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
		free(cmd_path);
		i++;
	}
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
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

	if (*cmd == '/' || *cmd == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		perror(cmd);
		return (NULL);
	}
	cmd_path = check_access(cmd, paths);
	if (cmd_path)
		return (cmd_path);
	return (NULL);
}

void	exec_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	printf("DEBUG: Executing command: %s\n", cmd);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	printf("DEBUG: Command arguments:");
	for (int i = 0; cmd_args[i]; i++)
		printf(" [%s]", cmd_args[i]);
	printf("\n");

	cmd_path = find_cmd_path(cmd_args[0], pipex->paths);
	printf("DEBUG: Command path: %s\n", cmd_path ? cmd_path : "Not found");
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd_args[0]);
		for (int i = 0; pipex->paths[i]; i++)
			printf("DEBUG: Searched in path: %s\n", pipex->paths[i]);
		free_tab(cmd_args);
		exit(127);  // Exit code for command not found
	}
	execve(cmd_path, cmd_args, envp);
	perror("execve");
	free(cmd_path);
	free_tab(cmd_args);
	error_exit("Execve", pipex);
}

void	child_process(t_pipex *pipex, char **envp, int i)
{
	int		fd_infile;
	int		fd_outfile;

	printf("DEBUG: Child process %d: Setting up file descriptors\n", i);
	if (i == 0)
	{
		fd_infile = pipex->fd_infile;
		fd_outfile = pipex->pipes_fds[i][1];
	}
	else if (i == pipex->cmds_count - 1)
	{
		fd_infile = pipex->pipes_fds[i - 1][0];
		fd_outfile = pipex->fd_outfile;
	}
	else
	{
		fd_infile = pipex->pipes_fds[i - 1][0];
		fd_outfile = pipex->pipes_fds[i][1];
	}
	printf("DEBUG: Child process %d: Closing unused pipe ends\n", i);
	for (int j = 0; j < pipex->pipes_count; j++)
	{
		if (j != i - 1)
			close(pipex->pipes_fds[j][0]);
		if (j != i)
			close(pipex->pipes_fds[j][1]);
	}
	printf("DEBUG: Child process %d: Duplicating file descriptors\n", i);
	if (dup2(fd_infile, STDIN_FILENO) == -1 || dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	if (fd_infile != STDIN_FILENO)
		close(fd_infile);
	if (fd_outfile != STDOUT_FILENO)
		close(fd_outfile);
	printf("DEBUG: Child process %d: Executing command\n", i);
	exec_cmd(pipex, pipex->cmds_list[i], envp);
}

void	init_pipes(t_pipex *pipex, char **av)
{
	int	i;

	printf("DEBUG: Initializing pipes\n");
	pipex->cmds_count = 0;
	if (!(pipex->is_here_doc))
		pipex->cmds_list = av + 2;
	else
		pipex->cmds_list = av + 3;
	while (pipex->cmds_list[pipex->cmds_count] && pipex->cmds_list[pipex->cmds_count + 1])
		pipex->cmds_count++;
	pipex->pipes_count = pipex->cmds_count - 1;
	printf("DEBUG: cmds_count: %d, pipes_count: %d\n", pipex->cmds_count, pipex->pipes_count);
	printf("DEBUG: Commands: ");
	for (int j = 0; j < pipex->cmds_count; j++)
		printf("[%s] ", pipex->cmds_list[j]);
	printf("\n");
	pipex->pipes_fds = malloc(sizeof(int *) * pipex->pipes_count);
	if (!(pipex->pipes_fds))
		error_exit("Pipes malloc failed", pipex);
	i = 0;
	while (i < pipex->pipes_count)
	{
		pipex->pipes_fds[i] = malloc(sizeof(int) * 2);
		if (!(pipex->pipes_fds[i]) || pipe(pipex->pipes_fds[i]) < 0)
			error_exit("Pipe creation failed", pipex);
		printf("DEBUG: Pipe %d created: [%d, %d]\n", i, pipex->pipes_fds[i][0], pipex->pipes_fds[i][1]);
		i++;
	}
	printf("DEBUG: Pipes initialization complete\n");
}

void	pipex_bonus(t_pipex *pipex, char **av, char **envp)
{
	int	i;
	int	pid;

	printf("DEBUG: Starting pipex_bonus\n");
	init_pipes(pipex, av);
	get_paths(pipex, envp);
	printf("DEBUG: Paths retrieved\n");
	for (int j = 0; pipex->paths[j]; j++)
		printf("DEBUG: Path %d: %s\n", j, pipex->paths[j]);
	i = 0;
	while (i < pipex->cmds_count)
	{
		printf("DEBUG: Forking for command %d: %s\n", i, pipex->cmds_list[i]);
		pid = fork();
		if (pid == -1)
			error_exit("Fork", pipex);
		if (pid == 0)
		{
			printf("DEBUG: Child process %d started\n", i);
			child_process(pipex, envp, i);
		}
		i++;
	}
	clean_pipex(pipex);
	printf("DEBUG: Pipex cleaned up\n");
}
*/