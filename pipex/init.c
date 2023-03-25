/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:02:01 by dkham             #+#    #+#             */
/*   Updated: 2023/03/25 17:28:34 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 먼저 case 1(./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2)인지 
// case2(./pipex here_doc LIMITER cmd cmd1 file)인지 확인한다
// case 1이면 infile을 open => dup2(open(argv[1], O_RDONLY), 0);
// case 2면 gnl을 통해 내용을 받는다
void	init(int argc, char **argv, char **envp)
{
	int		fd;
	t_info	*info;

	init_info(info);
	if (argc < 4)
	{
		perror("Error: not enough arguments\n");
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9) == 0) // case 2 : heredoc
		here_doc(argc, argv, envp, info);
	else										 // case 1 : infile
		infile(argc, argv, evnp, info);
}

void	init_info(int argc, char **argv, t_info *info)
{
	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
	{
		perror("Error: cannot allocate memory\n");
		exit(1);
	}
	info->case = 0;
	info->num_cmd = 0;
	info->cmds = NULL; // 내부도 다 NULL로 초기화?
	info->paths = NULL; // 내부도 다 NULL로 초기화?
	info->input_fd = 0;
	info->output_fd = 0;
	info->pipe_fd[0] = 0;
	info->pipe_fd[1] = 0;
}

// infile
// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// should behave like: < file1 cmd1 | cmd2 | ... | cmdn > file2
void	infile(int argc, char **argv, char **envp, t_info *info)
{
	int		fd;

	info->case = 1; // case1: infile
	info->num_cmd = argc - 3; // cmd 수
	get_cmd(argc, argv, info); // cmd 저장
	get_path(envp, info); // path 저장
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error: cannot open infile\n");
		exit(1);
	}
	dup2(fd, 0); // stdin을 fd(file1)로 바꿈
}

// here_doc
// ./pipex here_doc LIMITER cmd cmd1 file
// should behave like: cmd << LIMITER | cmd1 >> file
void	here_doc(int argc, char **argv, char **envp, t_info *info)
{
	char	*line;
	int		fd;

	info->case = 2; // case2: here_doc
	info->num_cmd = argc - 4; // cmd 수
	get_cmd(argc, argv, info); // cmd 저장
	get_path(envp, info); // path 저장
	fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // 확인
	if (fd == -1)
	{
		perror("Error: cannot open file\n");
		exit(1);
	}
	while (get_next_line(fd) != NULL)
	{
		line = get_next_line(fd);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		ft_putstr_fd(line, fd);
	}
}

void	get_cmd(int argc, char **argv, t_info *info)
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
	if (info->case == 1) // case 1의 경우 argv[2], case 2의 경우 argv[3]부터 cmd가 시작
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

// info->paths 구하기
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
	if (envp[i] == NULL)
	{
		perror("Error: cannot find path\n");
		exit(1);
	}
	info->paths = ft_split(path, ':');
	if (info->paths == NULL)
	{
		perror("Error: cannot allocate memory\n");
		exit(1);
	}
	free(path);
}
