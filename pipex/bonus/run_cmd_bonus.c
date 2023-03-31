/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:34:50 by dkham             #+#    #+#             */
/*   Updated: 2023/03/31 20:29:45 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	run_cmd(char **envp, t_info *info)
{
	int		i;
	pid_t	pid;
	int		pipe_fd[2];

	i = 0;
	while (i < info->num_cmd) // 명령어 개수만큼 반복
	{
		if (pipe(pipe_fd) == -1) // 파이프 열기 (pipe_fd[0],[1] 각각 fd 값 할당)
			exit(1);
		pid = fork(); // 파이프 후 포크: 자식 프로세스 생성
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			child_proc(info, i, pipe_fd, envp); // 자식 프로세스 실행 : 처음, 중간, 마지막 커맨드 나누어 구현
		else
			parent_proc(pipe_fd); // 부모 프로세스 실행
		i++;
	}
	while (i-- > 0) // wait for the termination of one of its child processes
		wait(NULL); // 자식 프로세스 종료 시 wait 함수로 부모가 exit status 받기 전까지는 좀비 프로세스임
}

void	child_proc(t_info *info, int i, int *pipe_fd, char **envp)
{
	int		j;
	char	*path;
	char	*cmd;
	char	**cmd_split;

	j = 0;
	while (info->paths[j]) // loop thru paths and check if cmd exists
	{
		path = ft_strjoin(info->paths[j], "/"); // path에 / 붙여서 path/ 만듦
		cmd_split = ft_split(info->cmds[i], ' '); // "wc -l" 있으면 wc만 가져옴
		cmd = ft_strjoin(path, cmd_split[0]); // path/cmd 앞부분 만듦
		free(path);
		if (access(cmd, F_OK) == 0) // returns 0 if the file or directory exists (F_OK flag)
			break ;
		j++;
	}
	if (info->paths[j] == NULL) // cmd가 존재하지 않으면
	{
		perror("command not found\n");
		exit(1); // error 처리 추가?
	}
	handle_fd(info, pipe_fd, i);
	if (execve(cmd, cmd_split, envp) == -1)
		exit(1);
}

void	handle_fd(t_info *info, int *pipe_fd, int i)
{
	if (i == 0) // 첫 커맨드
		first_cmd(info, pipe_fd, i);
	else if (i == info->num_cmd - 1) // 마지막 커맨드
		last_cmd(info, pipe_fd, i);
	else // 중간 커맨드
	{
		close(pipe_fd[0]); // parent에서 dup2(pipe_fd[0], 0); 해준 후 포크 해줘서 필요 없는듯
		if (dup2(pipe_fd[1], 1) == -1) // 출력 시 pipe_fd[1]로 출력
			exit(1); // error 처리 추가
		close(pipe_fd[1]);
	}
}

void	parent_proc(int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0); // 다음 포크 시 자식이 파이프에서 읽어올 수 있도록 pipe_fd[0]을 input으로 설정
	close(pipe_fd[0]); // close 후 dup2로 fd 처리하면 에러 (dup2 먼저)
}
