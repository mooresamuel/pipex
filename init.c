/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:06:34 by samoore           #+#    #+#             */
/*   Updated: 2024/01/19 14:57:51 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input_file(char *file, t_cmd *cmds)
{
	if (access(file, F_OK) == -1)
	{
		perror(file);
		free_cmds(cmds);
		exit (2);
	}
	if (!access(file, F_OK))
	{
		if (access(file, R_OK) == -1)
		{
			perror(file);
			free_cmds(cmds);
			exit (13);
		}
	}
}

void	check_output_file(char *file, t_cmd *cmds)
{
	if (!access(file, F_OK))
	{
		if (access(file, W_OK) == -1 || !access(file, X_OK))
		{
			errno = 13;
			perror(file);
			free_cmds (cmds);
			exit (13);
		}
	}
}

t_cmd	*get_commands(int argc, char **argv)
{
	t_cmd	*cmds;
	t_cmd	*prev;
	t_cmd	*head;
	int		i;

	prev = NULL;
	i = 2;
	while (i < argc - 1)
	{
		cmds = malloc(sizeof(t_cmd));
		if (prev)
			prev->next = cmds;
		else
			head = cmds;
		cmds->cmd = ft_split(argv[i++], ' ');
		cmds->next = NULL;
		cmds->path = NULL;
		prev = cmds;
	}
	return (head);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;

	while (cmds)
	{
		i = 0;
		if (cmds->path)
			free (cmds->path);
		while (cmds->cmd[i])
			free (cmds->cmd[i++]);
		free (cmds->cmd[i]);
		free (cmds->cmd);
		tmp = cmds->next;
		free (cmds);
		cmds = tmp;
	}
}

void	parse_input(int argc, char **argv, t_cmd *cmds)
{
	char	**paths;

	check_input_file(argv[1], cmds);
	check_output_file(argv[argc - 1], cmds);
	paths = NULL;
	paths = ft_split(get_path (), ':');
	if (paths)
		add_slash(paths);
	add_path(cmds, paths);
	free_paths (paths);
}
