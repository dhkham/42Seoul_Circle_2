/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequefunctions_2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:50:52 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 13:59:21 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap_bonus.h"

int	is_empty(t_deque *deque)
{
	if (deque->front == NULL)
		return (1);
	else
		return (0);
}

int	is_sorted(t_deque *deque)
{
	t_node	*temp;

	temp = deque->front;
	while (temp->next != NULL)
	{
		if (temp->num > temp->next->num)
			return (0);
		temp = temp->next;
	}
	return (1);
}
