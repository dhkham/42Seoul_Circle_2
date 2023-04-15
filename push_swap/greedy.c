/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:26:36 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 18:02:37 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	greedy(t_pdeque *pd)
{
	int		*count_ras;
	int		*count_rbs;

	while (1)
	{
		count_ras = (int *)malloc(sizeof(int) * pd->b->cnt);
		count_rbs = (int *)malloc(sizeof(int) * pd->b->cnt);
		get_count(pd, count_ras, count_rbs);
		execute_cmd(pd, count_ras, count_rbs);
		free(count_ras);
		free(count_rbs);
		if (pd->a->front->num > pd->a->front->next->num)
			command(pd, "ra");
		if (pd->b->cnt == 0)
		{
			finalize_a(pd);
			break ;
		}
	}
}

void	finalize_a(t_pdeque *pd)
{
	t_node	*cur_a;
	int		i;

	cur_a = pd->a->front;
	i = 1;
	while (cur_a->next)
	{
		if (cur_a->num > cur_a->next->num)
		{
			final_ra(pd, i);
			break ;
		}
		else
		{
			cur_a = cur_a->next;
			i++;
		}
	}
	return ;
}

void	final_ra(t_pdeque *pd, int i)
{
	if (i <= pd->a->cnt / 2)
	{
		while (i--)
			command(pd, "ra");
	}
	else
	{
		while (pd->a->cnt - i)
		{
			command(pd, "rra");
			i++;
		}
	}
}

void	get_count(t_pdeque *pd, int *count_ras, int *count_rbs)
{
	t_node	*cur_b;
	int		i;

	i = 0;
	cur_b = pd->b->front;
	while (cur_b)
	{
		count_ras[i] = get_count_ra(pd, cur_b);
		count_rbs[i] = get_count_rb(pd, cur_b);
		i++;
		cur_b = cur_b->next;
	}
}

int	get_count_ra(t_pdeque	*pd, t_node *cur_b)
{
	int		count_ra;
	int		break_flag;
	t_node	*a_front;

	count_ra = 0;
	break_flag = 0;
	a_front = pd->a->front;
	while (1)
	{
		if (a_front->next == NULL)
		{
			count_ra++;
			break ;
		}
		break_flag = calc_count_ra(cur_b, a_front, &count_ra);
		if (break_flag == 1)
			break ;
		count_ra++;
		a_front = a_front->next;
	}
	if (count_ra >= pd->a->cnt / 2 + 1)
		count_ra = count_ra * -1;
	return (count_ra);
}
