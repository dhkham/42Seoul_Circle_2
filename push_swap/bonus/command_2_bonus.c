/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:54:48 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 15:14:50 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap_bonus.h"

int	rotate(t_deque *deque, enum e_rear is_rear)
{
	int		val;
	int		is_error;

	is_error = 0;
	if (deque->cnt < 2)
		return (0);
	if (is_rear)
	{
		val = delete_rear(deque, &is_error);
		if (is_error)
			return (0);
		insert_front(deque, val);
	}
	else
	{
		val = delete_front(deque, &is_error);
		if (is_error)
			return (0);
		insert_rear(deque, val);
	}
	return (1);
}

int	exec_rr(t_pdeque *pd, enum e_rear is_rear)
{
	if (is_rear == REAR)
	{
		rotate(pd->a, REAR);
		rotate(pd->b, REAR);
	}
	else if (is_rear == FRONT)
	{
		rotate(pd->a, FRONT);
		rotate(pd->b, FRONT);
	}
	return (1);
}
