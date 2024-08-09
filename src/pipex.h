/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:01 by sabansac          #+#    #+#             */
/*   Updated: 2024/08/08 22:56:20 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../includes/libft/libft.h"

void	pipex(int *pipe_ends, int *fd_infile_outfile, char **av, char **envp);
void	double_close(int to_close1, int to_close2);
void	free_tab(char **tab);

#endif