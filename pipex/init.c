/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:02:01 by dkham             #+#    #+#             */
/*   Updated: 2023/04/02 12:22:41 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_info	*init(int argc, char **argv, char **envp)
{
	t_info	*info;

	info = NULL;
	init_info(&info, argc, argv);
	if (argc != 5)
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

	info->num_cmd = argc - 3;
	get_cmd(argv, info);
	get_path(envp, info);
	fd = open(argv[1], O_RDONLY, 0644);
	if (fd == -1)
		perror("Error: cannot open infile\n");
	info->input_fd = fd;
}
