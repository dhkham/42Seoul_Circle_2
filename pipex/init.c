/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:02:01 by dkham             #+#    #+#             */
/*   Updated: 2023/04/01 21:11:47 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 먼저 cases 1(./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2)인지 
// cases2(./pipex here_doc LIMITER cmd cmd1 file)인지 확인한다
// cases 1이면 infile을 open => fd = open(argv[1], O_RDONLY);
// cases 2면 gnl을 통해 내용을 받는다
t_info	*init(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = NULL;
	init_info(&info, argc, argv);
	if (argc != 5) // argc가 5가 아니면 에러
	{
		perror("Error: wrong number of arguments\n");
		exit(1);
	}
	infile(argc, argv, envp, info);
	return (info);
}

void	init_info(t_info **info, int argc, char **argv)
{
	*info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
	{
		perror("Error: cannot allocate memory\n");
		exit(1);
	}
	(*info)->num_cmd = 0;
	(*info)->cmds = NULL; // 내부도 다 NULL로 초기화?
	(*info)->paths = NULL; // 내부도 다 NULL로 초기화?
	(*info)->input_fd = 0;
	(*info)->output_fd = 0;
	(*info)->pipe_fd[0] = 0;
	(*info)->pipe_fd[1] = 0;
	(*info)->outfile = argv[argc - 1];
}

// infile
// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// should behave like: < file1 cmd1 | cmd2 | ... | cmdn > file2
void	infile(int argc, char **argv, char **envp, t_info *info)
{
	int		fd;

	info->num_cmd = argc - 3; // cmd 수
	get_cmd(argv, info); // cmd 저장
	get_path(envp, info); // path 저장
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror("Error: cannot open infile\n");
	info->input_fd = fd;
}
