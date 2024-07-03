/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:12:38 by samoore           #+#    #+#             */
/*   Updated: 2024/01/22 12:06:05 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i] && ft_strncmp(environ[i], "PATH=", 5))
		i++;
	return (&environ[i][5]);
}

void	add_slash(char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free (paths[i]);
		paths[i++] = tmp;
	}
}

void	check_path(char **paths, t_cmd *cmds)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths && !cmds->path && paths[i])
	{
		tmp = ft_strjoin(paths[i++], cmds->cmd[0]);
		if (access(tmp, F_OK) == 0)
		{
			cmds->path = ft_strdup(tmp);
			free (tmp);
			return ;
		}
		free (tmp);
	}
}

void	add_path(t_cmd *cmds, char **paths)
{
	t_cmd	*head;

	head = cmds;
	while (cmds)
	{
		cmds->path = NULL;
		if (access(cmds->cmd[0], F_OK) == -1)
			check_path(paths, cmds);
		else
			cmds->path = ft_strdup(cmds->cmd[0]);
		if (!cmds->path)
		{
			free_paths (paths);
			perror(cmds->cmd[0]);
			free_cmds (head);
			exit (2);
		}
		cmds = cmds->next;
	}
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
		free (paths[i++]);
	if (paths)
		free (paths);
}
