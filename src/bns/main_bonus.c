/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:30:45 by sbansacc          #+#    #+#             */
/*   Updated: 2024/08/20 05:57:19 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_exit(char *msg, t_pipex *pipex)
{
	perror(msg);
	clean_pipex(pipex);
	exit(EXIT_FAILURE);
}

int	is_valid_infile(char **av, int is_here_doc)
{
	int		fd_infile;
	char	*infile;

	fd_infile = -1;
	if (!is_here_doc)
	{
		fd_infile = open(av[1], O_RDONLY);
		infile = av[1];
	}
	else
	{
		fd_infile = here_doc(av[2], av[3]);
		infile = av[3];
	}
	if (fd_infile < 0 || access(infile, R_OK) == -1)
	{
		perror(infile);
		return (-1);
	}
	return (fd_infile);
}

int	is_valid_outfile(char *outfile, int is_append)
{
	int		fd_outfile;

	if (is_append)
		fd_outfile = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		fd_outfile = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (access(outfile, W_OK) == -1 || fd_outfile < 0)
	{
		perror("Outfile");
		exit(EXIT_FAILURE);
	}
	return (fd_outfile);
}

void	init_files(t_pipex *pipex, int ac, char **av)
{
	pipex->is_here_doc = 0;
	pipex->is_append = 0;
	if (ac > 1 && ft_strncmp(av[1], "here_doc", 8) == 0)
		pipex->is_here_doc = 1;
	if ((!pipex->is_here_doc && ac < 5) || (pipex->is_here_doc && ac < 6))
	{
		ft_putstr_fd("Error: to few number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex->fd_infile = is_valid_infile(av, pipex->is_here_doc);
	if (ft_strncmp(av[ac - 2], ">>", 2) == 0)
	{
		pipex->is_append = 1;
		pipex->fd_outfile = is_valid_outfile(av[ac - 1], 1);
	}
	else
		pipex->fd_outfile = is_valid_outfile(av[ac - 1], 0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	init_files(&pipex, ac, av);
	status = pipex_bonus(&pipex, av, envp);
	return (status);
}
