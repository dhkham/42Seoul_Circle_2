/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:30:35 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 14:08:45 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap_bonus.h"

int	calc_count_ra(t_node *cur_b, t_node *a_front, int *count_ra)
{
	if (a_front->num > a_front->next->num)
	{
		if (a_front->num < cur_b->num && a_front->next->num < cur_b->num)
		{
			*count_ra = *count_ra + 1;
			return (1);
		}
		if (a_front->num > cur_b->num && a_front->next->num > cur_b->num)
		{
			*count_ra = *count_ra + 1;
			return (1);
		}
	}
	if (a_front->num < cur_b->num && a_front->next->num > cur_b->num)
	{
		*count_ra = *count_ra + 1;
		return (1);
	}
	return (0);
}

int	get_count_rb(t_pdeque	*pd, t_node *cur_b)
{
	int		count_rb;

	count_rb = 0;
	if (cur_b == pd->b->front)
		return (count_rb);
	else
	{
		count_rb = 1;
		while (cur_b->prev != pd->b->front)
		{
			count_rb++;
			cur_b = cur_b->prev;
		}
		if (count_rb >= pd->b->cnt / 2 + 1)
			count_rb = count_rb * -1;
	}
	return (count_rb);
}

void	execute_cmd(t_pdeque *pd, int *count_ras, int *count_rbs)
{
	int		ra_rb[2];
	int		*cmd_cnt;
	int		min;
	int		min_idx;

	cmd_cnt = count_cmd(count_ras, count_rbs, pd, ra_rb);
	get_min_idx(pd, cmd_cnt, &min, &min_idx);
	free(cmd_cnt);
	if (count_ras[min_idx] >= 0 && count_rbs[min_idx] >= 0)
		case_one(pd, count_ras, count_rbs, min_idx);
	else if (count_ras[min_idx] < 0 && count_rbs[min_idx] < 0)
		case_two(pd, count_ras, count_rbs, min_idx);
	else
	{
		case_three_a(pd, count_ras, min_idx);
		case_three_b(pd, count_rbs, min_idx);
	}
	command(pd, "pa");
}

int	*count_cmd(int *count_ras, int *count_rbs, t_pdeque *pd, int *ra_rb)
{
	int		i;
	int		*cmd_cnt;

	i = 0;
	cmd_cnt = (int *)malloc(sizeof(int) * pd->b->cnt);
	while (i < pd->b->cnt)
	{
		if (count_ras[i] < 0)
			ra_rb[0] = pd->a->cnt + count_ras[i];
		else
			ra_rb[0] = count_ras[i];
		if (count_rbs[i] < 0)
			ra_rb[1] = pd->b->cnt + count_rbs[i];
		else
			ra_rb[1] = count_rbs[i];
		cmd_cnt[i] = ra_rb[0] + ra_rb[1];
		i++;
	}
	return (cmd_cnt);
}

void	get_min_idx(t_pdeque *pd, int *cmd_cnt, int *min, int *min_idx)
{
	int	i;

	i = 0;
	*min = cmd_cnt[0];
	*min_idx = 0;
	while (i < pd->b->cnt)
	{
		if (cmd_cnt[i] < *min)
		{
			*min = cmd_cnt[i];
			*min_idx = i;
		}
		i++;
	}
}
