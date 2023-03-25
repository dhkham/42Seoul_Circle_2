/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:34:50 by dkham             #+#    #+#             */
/*   Updated: 2023/03/25 21:42:32 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// info->paths, info->cmds 값 이용해 커맨드 실행
// path, cmd 값 이어 붙여서 access() 로 확인
// access() 성공하면 fork 후 자식 프로세스에서 execve() 실행

void	run_cmd(int argc, char **argv, char **envp, t_info *info)
{
	int		i;
	char	*path;
	char	*cmd;
	char	**cmd_split;
	char	*tmp;
	pid_t	pid;
	int		pipe_fd[2];

	//각 cmd에 대해 path의 모든 값들과 cmd 붙여서 access()로 확인
	//access() 성공하면 fork() 후 자식 프로세스에서 execve() 실행
	i = 0;
	while (i < info->num_cmd)
	{
		cmd = info->cmds[i];
		cmd_split = ft_split(cmd, ' ');
		while (*info->paths)
		{
			path = *info->paths;
			tmp = ft_strjoin(path, "/");
			cmd = ft_strjoin(tmp, cmd_split[0]);
			free(tmp);
			if (access(cmd, F_OK) == 0)
			{
				if (pipe(pipe_fd) == -1)
				{
					perror("pipe");
					exit(1);
				}
				pid = fork();
				if (pid == -1)
				{
					perror("fork");
					exit(1);
				}
				else if (pid == 0) // child
				{
					if (i == 0) // 첫번째 커맨드
					{
						if (info->case == 1)
						{
							dup2(info->input_fd, 0);
							dup2(pipe_fd[1], 1);
						}
					}
					else if (i == info->num_cmd - 1) // 마지막 커맨드
					{
						if (info->case == 2)
							info->output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
						else
							info->output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
						dup2(info->pipe_fd[0], 0); // 확인
						dup2(info->output_fd, 1);
					}
					else // 중간 커맨드
					{
						dup2(info->pipe_fd[0], 0);
						dup2(pipe_fd[1], 1);
					}
					close(pipe_fd[0]);
					close(pipe_fd[1]);
					execve(cmd, cmd_split, envp);
				}
				else // parent???
				{
					if (i == 0) // 첫번째 커맨드
					{
						if (info->case == 1) // infile
						{
							close(info->input_fd);
							close(pipe_fd[1]);
						}
						else if (info->case == 2) // here_doc
						{
							close(info->pipe_fd[0]);
							close(pipe_fd[1]);
						}
					}
					else if (i == info->num_cmd - 1) // 마지막 커맨드
					{
						close(info->pipe_fd[0]);
						close(info->output_fd);
					}
					else // 중간 커맨드
					{
						close(info->pipe_fd[0]);
						close(pipe_fd[1]);
					}
					waitpid(pid, NULL, 0);
			}
			free(cmd);
			info->paths++;
		} // while 다 돌았는데도 cmd가 없으면 error??
		free(cmd_split[0]);
		free(cmd_split[1]);
		free(cmd_split);
		i++;
		}
	}
}
