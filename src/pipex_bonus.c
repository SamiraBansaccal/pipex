/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 22:30:32 by sabansac          #+#    #+#             */
/*   Updated: 2024/08/09 06:15:33 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	n_pipe()
{
	int	pid;
	
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0)
		child_process()
}
void	multi_pipex(int *fd_in_out, char **cmd, char **envp, int cmd_count)
{
	int pipe_ends[cmd_count][2];
	int i;

	i = 0;
	while (i < cmd_count)
	{
		if (pipe([pipe_ends[i]]))
			pipe_error();
	}
	while (i)
	{
		close(pipe_ends[i][0]);
		close(pipe_ends[i][1]);
		i--;
	}
	if (fd_infile_outfile[0] != -1)
		waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
wile cmd
pipex ()


infile = pipex