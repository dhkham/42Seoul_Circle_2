/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:17:10 by dkham             #+#    #+#             */
/*   Updated: 2023/03/31 20:33:26 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(t_info *info, int *pipe_fd, int i)
{
	close(pipe_fd[0]); // child에서 fd[0] (read) 닫기 (=> infile에서 읽어오기 때문)
	if (dup2(info->input_fd, 0) == -1) // dup2: old_fd를 복제해 new_fd로 지정 (infile에서 읽어온다)
		exit(1); // error 처리 추가
	if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력 (연결은 되어 있지만 dup2해줘야 결과물이 이동함)
		exit(1); // error 처리 추가
	close(pipe_fd[1]); // child에서 fd[1] 닫기
	close(info->input_fd);
}

void	last_cmd(t_info *info, int *pipe_fd, int i)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]); // child에서 fd[1] 닫기 (outfile으로 출력하기 때문)
	if (info->cases == 1) // O_TRUNC: 기존 파일 내용 삭제
		info->output_fd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // outfile 생성
	else if (info->cases == 2) // O_APPEND: 기존 파일 내용 유지하고 뒤에 추가
		info->output_fd = open(info->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644); // outfile 생성
	if (dup2(info->output_fd, 1) == -1) // outfile으로 출력
		exit(1); // error 처리 추가
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
	if (info->cases == 1) // cases 1의 경우 argv[2], cases 2의 경우 argv[3]부터 cmd가 시작
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
	info->cmds[i] = NULL; // 필요?
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
			path = ft_strdup(envp[i] + 5); // PATH= 다음 부분 복사
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
