/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:23 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 16:08:26 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdlib.h"
# include "./libft/libft.h"

typedef struct s_node
{
	int				num;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_deque
{
	int		cnt;
	t_node	*front;
	t_node	*rear;
}	t_deque;

typedef struct s_pdeque
{
	struct s_deque	*a;
	struct s_deque	*b;
}	t_pdeque;

enum e_rear
{
	FRONT = 0,
	REAR = 1
};

t_pdeque	*pd_init(void);
void		pd_parse(t_pdeque *pd, int argc, char **argv);
void		check_duplicate(t_pdeque *pd, int num);
void		push_swap(t_pdeque *pd);
void		sort_three(t_pdeque *pd);
void		get_count(t_pdeque *pd, int *count_ras, int *count_rbs);
void		execute_cmd(t_pdeque *pd, int *count_ras, int *count_rbs);
int			get_count_ra(t_pdeque	*pd, t_node *cur_b);
int			get_count_rb(t_pdeque	*pd, t_node *cur_b);
t_node		*create_node(int num);
void		insert_front(t_deque *deque, int num);
void		insert_rear(t_deque *deque, int num);
int			delete_front(t_deque *deque, int *is_error);
int			delete_rear(t_deque *deque, int *is_error);
int			is_empty(t_deque *deque);
int			is_sorted(t_deque *deque);
int			command(t_pdeque *pd, char *cmd);
int			push(t_deque *from, t_deque *to, int pa_pb);
int			swap(t_deque *deque, int sa_sb);
int			rotate(t_deque *deque, enum e_rear is_rear, int ra_rb);
int			exec_ss(t_pdeque *pd, int ss);
int			exec_rr(t_pdeque *pd, enum e_rear is_rear, int rr);
void		checker(t_pdeque *pd);
void		get_pivot(t_pdeque *pd, int pivot_arr[2]);
void		greedy(t_pdeque *pd);
void		finalize_a(t_pdeque *pd);
void		print_rotate(enum e_rear is_rear, int ra_rb);
void		bubble(t_pdeque *pd, int *sorted);
void		push_groups_to_b(t_pdeque *pd, int *pivot_arr, int count);
int			calc_count_ra(t_node *cur_b, t_node *a_front, int *count_ra);
void		get_min_idx(t_pdeque *pd, int *cmd_cnt, int *min, int *min_idx);
void		case_one(t_pdeque *pd, int *count_ras, int *count_rbs, int min_idx);
void		case_two(t_pdeque *pd, int *count_ras, int *count_rbs, int min_idx);
void		case_three_a(t_pdeque *pd, int *count_ras, int min_idx);
void		case_three_b(t_pdeque *pd, int *count_rbs, int min_idx);
int			*count_cmd(int *count_ras, int *count_rbs, t_pdeque *pd, \
int *ra_rb);
void		sort_four(t_pdeque *pd);
void		sort_five(t_pdeque *pd);
void		find_min(t_pdeque *pd, int *min);
int			hard_sort(t_pdeque *pd);
void		final_ra(t_pdeque *pd, int i);
void		del_deque(t_pdeque *pd);
void		check_int_range(t_pdeque *pd, long long num);
int			is_valid(char *str);

#endif