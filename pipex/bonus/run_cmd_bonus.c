/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:34:50 by dkham             #+#    #+#             */
/*   Updated: 2023/04/02 11:53:52 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	run_cmd(char **envp, t_info *info)
{
	int		i;
	pid_t	pid;
	int		pipe_fd[2];

	i = 0;
	while (i < info->num_cmd)
	{
		if (pipe(pipe_fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			child_proc(info, i, pipe_fd, envp);
		else
			parent_proc(pipe_fd);
		i++;
	}
	while (i-- > 0)
		wait(NULL);
}

void	child_proc(t_info *info, int i, int *pipe_fd, char **envp)
{
	int		j;
	char	*path;
	char	*cmd;
	char	**cmd_split;

	j = check_access(info, i, &cmd, &cmd_split);
	if (info->paths[j] == NULL)
	{
		perror("command not found\n");
		exit(1);
	}
	handle_fd(info, pipe_fd, i);
	if (execve(cmd, cmd_split, envp) == -1)
		exit(1);
}

int	check_access(t_info *info, int i, char **cmd, char ***cmd_split)
{
	int		j;
	char	*path;

	j = 0;
	while (info->paths[j])
	{
		path = ft_strjoin(info->paths[j], "/");
		*cmd_split = ft_split(info->cmds[i], ' ');
		if (access((*cmd_split)[0], F_OK) == 0)
		{
			*cmd = ft_strdup((*cmd_split)[0]);
			free(path);
			break ;
		}
		else
			*cmd = ft_strjoin(path, (*cmd_split)[0]);
		free(path);
		if (access(*cmd, F_OK) == 0)
			break ;
		j++;
	}
	return (j);
}

void	handle_fd(t_info *info, int *pipe_fd, int i)
{
	if (i == 0)
		first_cmd(info, pipe_fd, i);
	else if (i == info->num_cmd - 1)
		last_cmd(info, pipe_fd, i);
	else
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
			exit(1);
		close(pipe_fd[1]);
	}
}

void	parent_proc(int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}
