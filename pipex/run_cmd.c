/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:34:50 by dkham             #+#    #+#             */
/*   Updated: 2023/03/26 17:26:26 by dkham            ###   ########.fr       */
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
		if (pipe(pipe_fd) == -1)
			exit(1); // error 처리 추가
		pid = fork(); // 파이프 먼저 만들고 포크해야함
		if (pid == -1)
			exit(1); // error 처리 추가
		else if (pid == 0)	//자식 프로세스 실행
			child_proc(info, i, pipe_fd, envp); // 처음, 끝, 중간 커맨드 나눠서 구현
		else //부모 프로세스 실행
			parent_proc(info, i, pipe_fd);
	}
	while (i < info->num_cmd)
		wait(NULL); // 수거
}

void	child_proc(t_info *info, int i, int *pipe_fd, char **envp)
{
	int		j;
	char	*path;
	char	*cmd;
	char	**cmd_split;
	char	*tmp;

	j = 0;// access 검사
	while (info->paths[j])
	{
		path = ft_strjoin(info->paths[j], "/");
		cmd_split = ft_split(info->cmds[i], ' '); // cmd를 split
		cmd = ft_strjoin(path, cmd_split[0]);
		free(path);
		if (access(cmd, F_OK) == 0) // cmd가 존재하면
			break ;
		j++;
	}
	if (info->paths[j] == NULL) // cmd가 존재하지 않으면
		exit(1); // error 처리 추가
	if (i == 0) // 처음 커맨드
	{
		close(pipe_fd[0]); // child에서 fd[0] 닫기 (infile에서 읽어오기 때문)
		if (dup2(info->input_fd, 0) == -1) // infile에서 읽어온다
			exit(1); // error 처리 추가
		if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력
			exit(1); // error 처리 추가
		close(pipe_fd[1]); // child에서 fd[1] 닫기 (outfile으로 출력하기 때문
		close(info->input_fd); // child에서 fd[0] 닫기 (infile에서 읽어오기 때문
	}
	else if (i == info->num_cmd - 1) // 마지막 커맨드
	{
		close(pipe_fd[1]); // child에서 fd[1] 닫기 (outfile으로 출력하기 때문)
		if (dup2(info->output_fd, 1) == -1) // outfile으로 출력
			exit(1); // error 처리 추가
	}
	else // 중간 커맨드
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력
			exit(1); // error 처리 추가
	}
	if (execve(cmd, cmd_split, envp) == -1) // execve() 실행
		exit(1); //free(cmd_split[0]); // 보류
}

void	parent_proc(t_info *info, int i, int *pipe_fd)
{
	int		status;

	// 인덱스 별로 시작, 끝, 중간에 대해 fd 처리
	// 처음 커맨드는 pipe_fd[1]을 close
	// 끝 커맨드는 pipe_fd[0]을 close
	// 중간 커맨드는 pipe_fd[0], pipe_fd[1]을 close
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]); // close 후 dup2로 fd 처리하면 에러
}
