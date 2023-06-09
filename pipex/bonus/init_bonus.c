/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:02:01 by dkham             #+#    #+#             */
/*   Updated: 2023/04/02 11:38:27 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		info->cases = 2;
		info->num_cmd = argc - 4;
		here_doc(argc, argv, envp, info);
	}
	else
	{
		info->cases = 1;
		info->num_cmd = argc - 3;
		infile(argc, argv, envp, info);
	}
	get_cmd(argv, info);
	get_path(envp, info);
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
	(*info)->cmds = NULL;
	(*info)->paths = NULL;
	(*info)->input_fd = 0;
	(*info)->output_fd = 0;
	(*info)->pipe_fd[0] = 0;
	(*info)->pipe_fd[1] = 0;
	(*info)->outfile = argv[argc - 1];
}

void	infile(int argc, char **argv, char **envp, t_info *info)
{
	int		fd;

	fd = open(argv[1], O_RDONLY, 0644);
	if (fd == -1)
		perror("Error: cannot open infile\n");
	info->input_fd = fd;
}

void	here_doc(int argc, char **argv, char **envp, t_info *info)
{
	char	*line;
	int		fd;
	char	*temp;

	fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		free(line);
	}
	free(line);
	free(temp);
	fd = open("temp.txt", O_RDONLY);
	info->input_fd = fd;
}
