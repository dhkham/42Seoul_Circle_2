/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:54:48 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 17:37:03 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rotate(t_deque *deque, enum e_rear is_rear, int ra_rb)
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
	print_rotate(is_rear, ra_rb);
	return (1);
}

void	print_rotate(enum e_rear is_rear, int ra_rb)
{
	if (is_rear == 0 && ra_rb == 0)
		ft_putstr_fd("ra\n", 1);
	else if (is_rear == 0 && ra_rb == 1)
		ft_putstr_fd("rb\n", 1);
	else if (is_rear == 1 && ra_rb == 0)
		ft_putstr_fd("rra\n", 1);
	else if (is_rear == 1 && ra_rb == 1)
		ft_putstr_fd("rrb\n", 1);
}

int	exec_rr(t_pdeque *pd, enum e_rear is_rear, int rr)
{
	if (is_rear == REAR)
	{
		rotate(pd->a, REAR, rr);
		rotate(pd->b, REAR, rr);
		ft_putstr_fd("rrr\n", 1);
	}
	else if (is_rear == FRONT)
	{
		rotate(pd->a, FRONT, rr);
		rotate(pd->b, FRONT, rr);
		ft_putstr_fd("rr\n", 1);
	}
	return (1);
}
