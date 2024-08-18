/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:32:51 by sbansacc          #+#    #+#             */
/*   Updated: 2024/08/17 20:48:50 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	closenfree_pipes(int **pipes_fds, int pipes_count)
{
	int	i;

	i = 0;
	while (i < pipes_count)
	{
		close(pipes_fds[i][0]);
		close(pipes_fds[i][1]);
		free(pipes_fds[i]);
		i++;
	}
	free(pipes_fds);
}

void	clean_pipex(t_pipex *pipex)
{
	close(pipex->fd_infile);
	close(pipex->fd_outfile);
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->pipes_fds)
		closenfree_pipes(pipex->pipes_fds, pipex->pipes_count);
	if (pipex->paths)
		free_tab(pipex->paths);
	if (pipex->is_here_doc)
		unlink(".here_doc_tmp");
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	error_exit(char *msg, t_pipex *pipex)
{
	perror(msg);
	clean_pipex(pipex);
	exit(EXIT_FAILURE);
}

int	here_doc(char *limiter, char *infile)
{
    int     fd;
    char    *line;

    fd = open(infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        perror("Here_doc temp file error");

    while (1)
    {
        ft_putstr_fd("heredoc> ", 1);
        line = get_next_line(0);
        if (!line)
            break;
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 &&
            line[ft_strlen(limiter)] == '\n')
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd);
        free(line);
    }
    close(fd);

    fd = open(infile, O_RDONLY);
    if (fd < 0)
    {
        unlink(infile);
        perror("Here_doc temp file error");
    }
    return (fd);
}
