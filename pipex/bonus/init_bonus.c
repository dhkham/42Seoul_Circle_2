/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:02:01 by dkham             #+#    #+#             */
/*   Updated: 2023/03/31 21:36:42 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// 먼저 cases 1(./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2)인지 
// cases2(./pipex here_doc LIMITER cmd cmd1 file)인지 확인한다
// cases 1이면 infile을 open => fd = open(argv[1], O_RDONLY);
// cases 2면 gnl을 통해 내용을 받는다
t_info	*init(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = NULL;
	init_info(&info, argc, argv);
	if (argc < 4)
	{
		perror("Error: not enough arguments\n");
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0) // cases 2 : heredoc
		here_doc(argc, argv, envp, info);
	else										 // cases 1 : infile
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
	(*info)->cases = 0;
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

	info->cases = 1; // cases1: infile
	info->num_cmd = argc - 3; // cmd 수
	get_cmd(argv, info); // cmd 저장
	get_path(envp, info); // path 저장
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error: cannot open infile\n");
		exit(1);
	}
	info->input_fd = fd;
}

// here_doc
// ./pipex here_doc LIMITER cmd cmd1 file
// should behave like: cmd << LIMITER | cmd1 >> file
void	here_doc(int argc, char **argv, char **envp, t_info *info)
{
	char	*line;
	int		fd;
	char	*temp;

	info->cases = 2; // cases2: here_doc
	info->num_cmd = argc - 4; // cmd 수
	get_cmd(argv, info); // cmd 저장
	get_path(envp, info); // path 저장
	fd = open("temp.txt", O_WRONLY | O_CREAT | O_APPEND, 0644); // 확인해야함
	if (fd == -1)
	{
		perror("Error: cannot open file\n");
		exit(1);
	}
	temp = ft_strjoin(argv[2], "\n");
	while (1)
	{
		line = get_next_line(1);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, temp, ft_strlen(argv[2]) + 1) == 0)
			break ;
		ft_putstr_fd(line, fd);
	}
	free(temp);
	fd = open("temp.txt", O_RDONLY);
	info->input_fd = fd;
}
