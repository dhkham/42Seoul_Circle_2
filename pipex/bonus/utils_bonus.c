/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:17:10 by dkham             #+#    #+#             */
/*   Updated: 2023/04/01 21:28:07 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(t_info *info, int *pipe_fd, int i)
{
	close(pipe_fd[0]);
	if (dup2(info->input_fd, 0) == -1)
		exit(1);
	if (dup2(pipe_fd[1], 1) == -1)
		exit(1);
	close(pipe_fd[1]);
	close(info->input_fd);
}

void	last_cmd(t_info *info, int *pipe_fd, int i)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (info->cases == 1)
		info->output_fd = open(info->outfile, O_WRONLY | O_CREAT | \
		O_TRUNC, 0644);
	else if (info->cases == 2)
		info->output_fd = open(info->outfile, O_WRONLY | O_CREAT | \
		O_APPEND, 0644);
	if (dup2(info->output_fd, 1) == -1)
		exit(1);
	close(info->output_fd);
}

void	get_cmd(char **argv, t_info *info)
{
	int		i;
	int		cmd_start;

	i = 0;
	info->cmds = (char **)malloc(sizeof(char *) * (info->num_cmd + 1));
	if (info->cmds == NULL)
	{
		perror("Error: cannot allocate memory\n");
		exit(1);
	}
	if (info->cases == 1)
		cmd_start = 2;
	else
		cmd_start = 3;
	while (i < info->num_cmd)
	{
		info->cmds[i] = ft_strdup(argv[cmd_start + i]);
		if (info->cmds[i] == NULL)
		{
			perror("Error: cannot allocate memory\n");
			exit(1);
		}
		i++;
	}
	info->cmds[i] = NULL;
}

void	get_path(char **envp, t_info *info)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (path == NULL)
			{
				perror("Error: cannot allocate memory\n");
				exit(1);
			}
			break ;
		}
		i++;
	}
	info->paths = ft_split(path, ':');
	if (info->paths == NULL)
	{
		perror("Error: cannot allocate memory\n");
		exit(1);
	}
	free(path);
}
