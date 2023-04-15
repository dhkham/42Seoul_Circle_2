/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 18:02:32 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_pdeque *pd)
{
	int		pivot_arr[2];
	int		count;
	int		break_flag;

	count = 0;
	break_flag = hard_sort(pd);
	if (break_flag == 1)
		return ;
	get_pivot(pd, pivot_arr);
	push_groups_to_b(pd, pivot_arr, count);
	sort_five(pd);
	greedy(pd);
}

int	hard_sort(t_pdeque *pd)
{
	if (pd->a->cnt == 2)
	{
		command(pd, "sa");
		return (1);
	}
	else if (pd->a->cnt == 3)
	{
		sort_three(pd);
		return (1);
	}
	else if (pd->a->cnt == 4)
	{
		sort_four(pd);
		return (1);
	}
	else if (pd->a->cnt == 5)
	{
		sort_five(pd);
		return (1);
	}
	return (0);
}

void	get_pivot(t_pdeque *pd, int pivot_arr[2])
{
	int		*sorted;
	int		i;
	t_node	*cur_a;

	sorted = (int *)malloc(sizeof(int) * pd->a->cnt);
	cur_a = pd->a->front;
	i = 0;
	while (cur_a)
	{
		sorted[i] = cur_a->num;
		cur_a = cur_a->next;
		i++;
	}
	bubble(pd, sorted);
	pivot_arr[0] = sorted[pd->a->cnt / 3];
	pivot_arr[1] = sorted[pd->a->cnt * 2 / 3];
	free(sorted);
}

void	bubble(t_pdeque *pd, int *sorted)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (i < pd->a->cnt - 1)
	{
		j = 0;
		while (j < pd->a->cnt - i - 1)
		{
			if (sorted[j] > sorted[j + 1])
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	push_groups_to_b(t_pdeque *pd, int *pivot_arr, int count)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		count = pd->a->cnt;
		while (count)
		{
			if (is_sorted(pd->a) == 1)
				break ;
			if (pd->a->cnt == 5)
				break ;
			if (pd->a->front->num < pivot_arr[i] && i < 2)
				command(pd, "pb");
			else if (pd->a->front->num >= pivot_arr[1] && i == 2)
				command(pd, "pb");
			else
				command(pd, "ra");
			count--;
		}
		i++;
	}
}
