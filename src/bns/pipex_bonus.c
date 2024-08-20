/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:30:50 by sbansacc          #+#    #+#             */
/*   Updated: 2024/08/20 05:38:29 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	setup_io(t_pipex *pipex, int *fd_infile, int *fd_outfile, int i)
{
	if (i == 0)
	{
		if (pipex->fd_infile < 0)
			error_exit("infile", pipex);
		*fd_outfile = pipex->pipes_fds[i][1];
		*fd_infile = pipex->fd_infile;
	}
	else if (i == (pipex->cmds_count) - 1)
	{
		*fd_infile = pipex->pipes_fds[i - 1][0];
		*fd_outfile = pipex->fd_outfile;
	}
	else
	{
		*fd_infile = pipex->pipes_fds[i - 1][0];
		*fd_outfile = pipex->pipes_fds[i][1];
	}
}

void	child_process(t_pipex *pipex, char **envp, int i)
{
	int	fd_infile;
	int	fd_outfile;
	int	j;

	setup_io(pipex, &fd_infile, &fd_outfile, i);
	dup2(fd_infile, STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	j = 0;
	while (j < pipex->pipes_count)
	{
		close(pipex->pipes_fds[j][0]);
		close(pipex->pipes_fds[j][1]);
		j++;
	}
	close(pipex->fd_infile);
	close(pipex->fd_outfile);
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
	if (pipex->is_append)
		pipex->cmds_count--;
	pipex->pipes_count = pipex->cmds_count - 1;
	pipex->pipes_fds = malloc(sizeof(int *) * pipex->pipes_count);
	if (!(pipex->pipes_fds))
		error_exit("Pipes", pipex);
	i = 0;
	while (i < pipex->pipes_count)
	{
		pipex->pipes_fds[i] = malloc(sizeof(int) * 2);
		if (!(pipex->pipes_fds[i]) || pipe(pipex->pipes_fds[i]) < 0)
			error_exit("Pipes", pipex);
		i++;
	}
}

static void	fork_and_execute(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	pipex->pid = malloc(sizeof(int) * pipex->cmds_count);
	if (!pipex->pid)
		error_exit("pid", pipex);
	while (i < pipex->cmds_count)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			error_exit("Fork", pipex);
		if (pipex->pid[i] == 0)
		{
			child_process(pipex, envp, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	pipex_bonus(t_pipex *pipex, char **av, char **envp)
{
	int	i;
	int	status;

	status = 0;
	init_pipes(pipex, av);
	get_paths(pipex, envp);
	fork_and_execute(pipex, envp);
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
		if (waitpid(-1, &status, 0) == -1)
			error_exit("Wait", pipex);
		i++;
	}
	clean_pipex(pipex);
	return (status);
}
