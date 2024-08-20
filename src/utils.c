/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 05:39:17 by sabansac          #+#    #+#             */
/*   Updated: 2024/08/20 05:50:24 by sabansac         ###   ########.fr       */
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
		tmp = ft_strjoin(paths[i++], "/");
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

static char	**get_path_from_env(char **envp)
{
	char	**paths;

	paths = NULL;
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp && !ft_strncmp(*envp, "PATH=", 5))
	{
		paths = ft_split(*envp + 5, ':');
		if (!paths)
			return (NULL);
	}
	return (paths);
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
	paths = get_path_from_env(envp);
	if (paths)
	{
		cmd_path = check_access(cmd, paths);
		free_tab(paths);
		return (cmd_path);
	}
	perror(cmd);
	return (NULL);
}
