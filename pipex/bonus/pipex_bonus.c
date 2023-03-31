/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:54:04 by dkham             #+#    #+#             */
/*   Updated: 2023/03/31 20:23:54 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// case 1:
// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// should behave like: < file1 cmd1 | cmd2 | ... | cmdn > file2

// case 2:
// ./pipex here_doc LIMITER cmd cmd1 file (argc - 4)
// should behave like: cmd << LIMITER | cmd1 >> file

// to do
// 1. initialize
// envp에서 PATH=를 찾기
// PATH=를 기준으로 ":"을 기준으로 split
// split한 것을 기준으로 access를 통해 cmd가 있는지 확인
// cmd가 있으면 해당 cmd의 path를 찾기
// cmd가 없으면 error

// 2. execute
// 각 cmd가 자식 프로세스로 실행되어야 함
// while 돌면서 각 cmd를 실행

// 먼저 case 1인지 case2인지 확인한다
// case 1이면 infile을 open => dup2(open(argv[1], O_RDONLY), 0);
// case 2면 gnl을 통해 내용을 받는다

// case 1, 2의 경우 모두 while문을 돌면서 각 cmd를 실행한다
// 각 cmd는 자식 프로세스로 실행되어야 함 (execve 사용 시 아래는 실행 되지 않기 때문, 따로 자식으로 빼서 해야함)
// 각 cmd 나올 때마다 부모에서 fork 일어남
// 각 cmd는 pipe를 통해 연결되어야 함

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = init(argc, argv, envp); // infile인지 here_doc인지 확인, cmd/path 저장, 파일 open
	run_cmd(envp, info); // 
}
