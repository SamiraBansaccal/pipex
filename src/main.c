/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:05:51 by sabansac          #+#    #+#             */
/*   Updated: 2024/08/08 22:33:55 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	pipe_error(void)
{
	perror("Pipe");
	exit(EXIT_FAILURE);
}

int	is_valid_infile(char *infile)
{
	int		fd_infile;

	fd_infile = open(infile, O_RDONLY);
	if (fd_infile < 0 || access(infile, R_OK) == -1)
	{
		perror("Infile");
		return (-1);
	}
	return (fd_infile);
}

int	is_valid_outfile(char *outfile)
{
	int		fd_outfile;

	fd_outfile = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd_outfile < 0 || access(outfile, W_OK) == -1)
	{
		perror("Outfile");
		exit(EXIT_FAILURE);
	}
	return (fd_outfile);
}

int	main(int ac, char **av, char **envp)
{
	int		fd_infile_outfile[2];
	int		pipe_ends[2];

	if (ac != 5)
	{
		write(2, "error : nbr of arguments incorrect\n", 35);
		return (1);
	}
	fd_infile_outfile[0] = is_valid_infile(av[1]);
	fd_infile_outfile[1] = is_valid_outfile(av[4]);
	if (pipe(pipe_ends) == -1)
		pipe_error();
	pipex(pipe_ends, fd_infile_outfile, av, envp);
	close(fd_infile_outfile[0]);
	close(fd_infile_outfile[1]);
	return (0);
}
