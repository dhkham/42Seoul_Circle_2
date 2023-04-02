/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:02:33 by dkham             #+#    #+#             */
/*   Updated: 2023/04/02 11:59:28 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "fcntl.h"
# include "../get_next_line/get_next_line_bonus.h"
# include "../libft/libft.h"

typedef struct s_info
{
	int		cases;
	int		num_cmd;
	char	**cmds;
	char	**paths;
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	char	*outfile;
}	t_info;

t_info	*init(int argc, char **argv, char **envp);
void	init_info(t_info **info, int argc, char **argv);
void	infile(int argc, char **argv, char **envp, t_info *info);
void	here_doc(int argc, char **argv, char **envp, t_info *info);
void	get_cmd(char **argv, t_info *info);
void	get_path(char **envp, t_info *info);
void	run_cmd(char **envp, t_info *info);
void	child_proc(t_info *info, int i, int *pipe_fd, char **envp);
void	handle_fd(t_info *info, int *pipe_fd, int i);
void	parent_proc(int *pipe_fd);
void	first_cmd(t_info *info, int *pipe_fd, int i);
void	last_cmd(t_info *info, int *pipe_fd, int i);
int		check_access(t_info *info, int i, char **cmd, char ***cmd_split);

#endif