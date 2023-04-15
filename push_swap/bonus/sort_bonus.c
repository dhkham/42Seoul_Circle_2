/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:50:32 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 14:07:11 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap_bonus.h"

void	sort_three(t_pdeque *pd)
{
	int		a;
	int		b;
	int		c;

	a = pd->a->front->num;
	b = pd->a->front->next->num;
	c = pd->a->front->next->next->num;
	if (a < b && b > c && c > a)
	{
		command(pd, "sa");
		command(pd, "ra");
	}
	else if (a > b && b < c && c > a)
	{
		command(pd, "sa");
	}
	else if (a < b && b > c && c < a)
		command(pd, "rra");
	else if (a > b && b < c && c < a)
		command(pd, "ra");
	else if (a > b && b > c)
	{
		command(pd, "sa");
		command(pd, "rra");
	}
}

void	sort_four(t_pdeque *pd)
{
	int		i;
	int		min;

	i = 0;
	find_min(pd, &min);
	while (i < pd->a->cnt)
	{
		if (pd->a->front->num == min)
		{
			command(pd, "pb");
			break ;
		}
		if (pd->a->rear->num == min)
			command(pd, "rra");
		else
			command(pd, "ra");
		i++;
	}
	sort_three(pd);
	command(pd, "pa");
}

void	find_min(t_pdeque *pd, int *min)
{
	t_node	*tmp;

	tmp = pd->a->front;
	*min = tmp->num;
	while (tmp)
	{
		if (tmp->num < *min)
			*min = tmp->num;
		tmp = tmp->next;
	}
}

void	sort_five(t_pdeque *pd)
{
	int		i;
	int		min;

	i = 0;
	find_min(pd, &min);
	while (i < pd->a->cnt)
	{
		if (pd->a->front->num == min)
		{
			command(pd, "pb");
			break ;
		}
		if (pd->a->rear->num == min || pd->a->rear->prev->num == min)
			command(pd, "rra");
		else
			command(pd, "ra");
		i++;
	}
	sort_four(pd);
	command(pd, "pa");
}
