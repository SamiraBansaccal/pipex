/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:30:45 by sbansacc          #+#    #+#             */
/*   Updated: 2024/08/15 07:44:31 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	init_files(t_pipex *pipex, int ac, char **av)
{
	pipex->is_here_doc = 0;
	if (ac > 1 && ft_strncmp(av[1], "here_doc", 8) == 0)
		pipex->is_here_doc = 1;
	if ((!pipex->is_here_doc && ac < 5) || (pipex->is_here_doc && ac < 6))
	{
		ft_putstr_fd("Error: to few number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex->fd_infile = is_valid_infile(av, pipex->is_here_doc);
	pipex->fd_outfile = is_valid_outfile(av[ac - 1]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	init_files(&pipex, ac, av);
	pipex_bonus(&pipex, av, envp);
	return (0);
}

/*
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

void	init_files(t_pipex *pipex, int ac, char **av)
{
	pipex->is_here_doc = 0;
	if (ac > 1 && ft_strncmp(av[1], "here_doc", 8) == 0)
		pipex->is_here_doc = 1;
	if ((!pipex->is_here_doc && ac < 5) || (pipex->is_here_doc && ac < 6))
	{
		ft_putstr_fd("Error: too few number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex->fd_infile = is_valid_infile(av, pipex->is_here_doc);
	pipex->fd_outfile = is_valid_outfile(av[ac - 1]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	printf("DEBUG: Starting main\n");
	init_files(&pipex, ac, av);
	printf("DEBUG: Files initialized. infile: %d, outfile: %d, is_here_doc: %d\n", 
		   pipex.fd_infile, pipex.fd_outfile, pipex.is_here_doc);
	pipex_bonus(&pipex, av, envp);
	printf("DEBUG: pipex_bonus finished\n");
	return (0);
}
*/
