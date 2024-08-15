/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:30:55 by sbansacc          #+#    #+#             */
/*   Updated: 2024/08/15 05:13:55 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../includes/libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		is_here_doc;
	int		pipes_count;
	int		**pipes_fds;
	int		cmds_count;
	char	**cmds_list;
	char	**paths;
}	t_pipex;

void	pipex_bonus(t_pipex *pipex, char **av, char **envp);
char	*find_cmd_path(char *cmd, char **envp);
int		here_doc(char *limiter, char *infile);
void	error_exit(char *msg, t_pipex *pipex);
void	free_tab(char **tab);
void	close_pipes(int *pipefd, int n);
void	pipe_error(void);
void	child_process(t_pipex *pipex, char **envp, int i);
void	clean_pipex(t_pipex *pipex);


#endif