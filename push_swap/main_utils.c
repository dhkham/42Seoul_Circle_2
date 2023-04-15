/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:14:19 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 17:55:47 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	del_deque(t_pdeque *pd)
{
	t_node	*throw;
	t_node	*cur;

	cur = pd->a->front;
	while (cur != NULL)
	{
		throw = cur;
		cur = cur->next;
		free(throw);
	}
	pd->a->front = NULL;
	pd->a->rear = NULL;
	pd->a->cnt = 0;
	free(pd->a);
	cur = pd->b->front;
	while (cur != NULL)
	{
		throw = cur;
		cur = cur->next;
		free(throw);
	}
	pd->b->front = NULL;
	pd->b->rear = NULL;
	pd->b->cnt = 0;
	free(pd->b);
}
