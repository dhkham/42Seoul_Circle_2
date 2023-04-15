/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:29:04 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 14:10:53 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap_bonus.h"

void	case_one(t_pdeque *pd, int *count_ras, int *count_rbs, int min_idx)
{
	while (count_ras[min_idx] > 0 && count_rbs[min_idx] > 0)
	{
		command(pd, "rr");
		count_ras[min_idx]--;
		count_rbs[min_idx]--;
	}
	while (count_ras[min_idx] > 0)
	{
		command(pd, "ra");
		count_ras[min_idx]--;
	}
	while (count_rbs[min_idx] > 0)
	{
		command(pd, "rb");
		count_rbs[min_idx]--;
	}
}

void	case_two(t_pdeque *pd, int *count_ras, int *count_rbs, int min_idx)
{
	count_ras[min_idx] = pd->a->cnt + count_ras[min_idx];
	count_rbs[min_idx] = pd->b->cnt + count_rbs[min_idx];
	while (count_ras[min_idx] > 0 && count_rbs[min_idx] > 0)
	{
		command(pd, "rrr");
		count_ras[min_idx]--;
		count_rbs[min_idx]--;
	}
	while (count_ras[min_idx] > 0)
	{
		command(pd, "rra");
		count_ras[min_idx]--;
	}
	while (count_rbs[min_idx] > 0)
	{
		command(pd, "rrb");
		count_rbs[min_idx]--;
	}
}

void	case_three_a(t_pdeque *pd, int *count_ras, int min_idx)
{
	if (count_ras[min_idx] > 0)
	{
		while (count_ras[min_idx] > 0)
		{
			command(pd, "ra");
			count_ras[min_idx]--;
		}
	}
	else if (count_ras[min_idx] < 0)
	{
		count_ras[min_idx] = pd->a->cnt + count_ras[min_idx];
		while (count_ras[min_idx] > 0)
		{
			command(pd, "rra");
			count_ras[min_idx]--;
		}
	}
}

void	case_three_b(t_pdeque *pd, int *count_rbs, int min_idx)
{
	if (count_rbs[min_idx] > 0)
	{
		while (count_rbs[min_idx] > 0)
		{
			command(pd, "rb");
			count_rbs[min_idx]--;
		}
	}
	else if (count_rbs[min_idx] < 0)
	{
		count_rbs[min_idx] = pd->b->cnt + count_rbs[min_idx];
		while (count_rbs[min_idx] > 0)
		{
			command(pd, "rrb");
			count_rbs[min_idx]--;
		}
	}
}
