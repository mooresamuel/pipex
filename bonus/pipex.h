/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:06:56 by samoore           #+#    #+#             */
/*   Updated: 2024/01/22 12:07:37 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**cmd;
	char			*path;
}	t_cmd;

void	add_input_file(char **cmds, char *filename);
void	add_path(t_cmd *cmds, char **paths);
void	add_slash(char **paths);
void	check_input_file(char *file, t_cmd *cmds);
char	*err_msg(char *cmd, char *file);
void	check_path(char **paths, t_cmd *cmds);
void	free_cmds(t_cmd *cmds);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_paths(char **paths);
t_cmd	*get_commands(int argc, char **argv, int i);
char	*get_path(void);
void	here_doc(char *delim);
void	parent(int fd[2], pid_t pid);
void	parse_input(int argc, char **argv, t_cmd *cmds);
char	*ft_strdup(const char *s);

#endif
