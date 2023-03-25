/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:02:33 by dkham             #+#    #+#             */
/*   Updated: 2023/03/25 17:26:38 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// 제출 전 확인
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "stdio.h"
# include <sys/types.h>

typedef struct s_info
{
	int		case; // 1: infile, 2: here_doc
	int		num_cmd; // 커맨드 수
	char 	**cmds; // 각 커맨드
	char 	**paths; // envp에서 PATH=를 찾아 split한 것
	int		input_fd; // infile
	int		output_fd; // outfile
	int		pipe_fd[2]; // pipe
}	t_info;

#endif