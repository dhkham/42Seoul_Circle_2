/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:53:04 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 15:13:49 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap_bonus.h"

void	checker(t_pdeque *pd)
{
	char	*cmd;

	while (1)
	{
		cmd = get_next_line(0);
		if (cmd == NULL)
			break ;
		command(pd, cmd);
		free(cmd);
	}
	if (is_empty(pd->b) && is_sorted(pd->a))
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}
