/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:34:50 by dkham             #+#    #+#             */
/*   Updated: 2023/03/29 22:09:45 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_cmd(char **envp, t_info *info)
{
	int		i;
	pid_t	pid;
	int		pipe_fd[2];

	i = 0;
	while (i < info->num_cmd)
	{
		if (pipe(pipe_fd) == -1)
			exit(1); // error 처리 추가
		pid = fork(); // 파이프 먼저 만들고 포크해야함
		if (pid == -1)
			exit(1); // error 처리 추가
		else if (pid == 0)	//자식 프로세스 실행
			child_proc(info, i, pipe_fd, envp); // 처음, 끝, 중간 커맨드 나눠서 구현
		else //부모 프로세스 실행
			parent_proc(pipe_fd);
		i++;
	}
	while (i-- > 0)
		wait(NULL); // 수거
}

void	child_proc(t_info *info, int i, int *pipe_fd, char **envp)
{
	int		j;
	char	*path;
	char	*cmd;
	char	**cmd_split;

	j = 0;
	while (info->paths[j])
	{
		path = ft_strjoin(info->paths[j], "/");
		cmd_split = ft_split(info->cmds[i], ' ');
		cmd = ft_strjoin(path, cmd_split[0]);
		free(path);
		if (access(cmd, F_OK) == 0)
			break ;
		j++;
	}
	if (info->paths[j] == NULL) // cmd가 존재하지 않으면
		exit(1); // error 처리 추가
	handle_fd(info, pipe_fd, i);
	if (execve(cmd, cmd_split, envp) == -1)
		exit(1); //free(cmd_split[0]); 보류
}

void	handle_fd(t_info *info, int *pipe_fd, int i)
{
	if (i == 0)
	{
		close(pipe_fd[0]); // child에서 fd[0] 닫기 (infile에서 읽어오기 때문)
		if (dup2(info->input_fd, 0) == -1) // infile에서 읽어온다
			exit(1); // error 처리 추가
		if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력 (필요?)
			exit(1); // error 처리 추가
		close(pipe_fd[1]); // child에서 fd[1] 닫기
		close(info->input_fd); // child에서 fd[0] 닫기
	}
	else if (i == info->num_cmd - 1)
	{
		close(pipe_fd[0]); //필요?
		close(pipe_fd[1]); // child에서 fd[1] 닫기 (outfile으로 출력하기 때문)
		//printf("outfile: %s", info->outfile);
		if (info->cases == 1)
			info->output_fd = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // outfile 생성
		else if (info->cases == 2)
			info->output_fd = open(info->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644); // outfile 생성
		if (dup2(info->output_fd, 1) == -1) // outfile으로 출력
			exit(1); // error 처리 추가
		close(info->output_fd); // 필요?
	}
	else
	{
		close(pipe_fd[0]); // parent에서 dup2(pipe_fd[0], 0); 해준 후 포크 해줘서 필요 없는듯
		if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력
			exit(1); // error 처리 추가
		close(pipe_fd[1]); // 필요?
	}
}

void	parent_proc(int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0); // 다음 포크 시 자식이 파이프에서 읽어올 수 있도록 pipe_fd[0]을 input으로 설정
	close(pipe_fd[0]); // close 후 dup2로 fd 처리하면 에러 (dup2 먼저)
}

//void	first_cmd(t_info *info, int *pipe_fd)
// {
// 		close(pipe_fd[0]); // child에서 fd[0] 닫기 (infile에서 읽어오기 때문)
// 		if (dup2(info->input_fd, 0) == -1) // infile에서 읽어온다
// 			exit(1); // error 처리 추가
// 		if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력 (필요?)
// 			exit(1); // error 처리 추가
// 		close(pipe_fd[1]); // child에서 fd[1] 닫기
// 		close(info->input_fd); // child에서 fd[0] 닫기
// }

// void	last_cmd(t_info *info, int *pipe_fd)
// {
// 		// close(pipe_fd[0]); 필요?
// 		close(pipe_fd[1]); // child에서 fd[1] 닫기 (outfile으로 출력하기 때문)
// 		if (dup2(info->output_fd, 1) == -1) // outfile으로 출력
// 			exit(1); // error 처리 추가
// }

// void	mid_cmd(t_info *info, int *pipe_fd)
// {
// 	close(pipe_fd[0]); // parent에서 dup2(pipe_fd[0], 0); 해준 후 포크 해줘서 필요 없는듯
// 	if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력
// 		exit(1); // error 처리 추가
// }