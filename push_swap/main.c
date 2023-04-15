/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:17:03 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 17:54:52 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_pdeque	*pd;
	int			i;

	i = 1;
	if (argc < 2)
		exit(1);
	pd = pd_init();
	while (i < argc)
	{
		if (is_valid(argv[i]) == 0)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		i++;
	}
	pd_parse(pd, argc, argv);
	push_swap(pd);
	del_deque(pd);
	free(pd);
	return (0);
}

t_pdeque	*pd_init(void)
{
	t_pdeque	*pd;

	pd = (t_pdeque *)malloc(sizeof(t_pdeque));
	if (pd == NULL)
		exit(1);
	pd->a = (t_deque *)malloc(sizeof(t_deque));
	if (pd->a == NULL)
	{
		free(pd);
		exit(1);
	}
	pd->b = (t_deque *)malloc(sizeof(t_deque));
	if (pd->b == NULL)
	{
		free(pd->a);
		free(pd);
		exit(1);
	}
	pd->a->front = NULL;
	pd->a->rear = NULL;
	pd->a->cnt = 0;
	pd->b->front = NULL;
	pd->b->rear = NULL;
	pd->b->cnt = 0;
	return (pd);
}

void	pd_parse(t_pdeque *pd, int argc, char **argv)
{
	int			i;
	long long	num;

	i = 1;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (num == 0 && ft_strncmp(argv[i], "0", 1) != 0)
		{
			ft_putstr_fd("Error\n", 2);
			del_deque(pd);
			free(pd);
			exit(1);
		}
		check_int_range(pd, num);
		check_duplicate(pd, (int)num);
		insert_rear(pd->a, (int)num);
		i++;
	}
	if (is_sorted(pd->a))
	{
		del_deque(pd);
		free(pd);
		exit(0);
	}
}

void	check_int_range(t_pdeque *pd, long long num)
{
	if (num > 2147483647 || num < -2147483648)
	{
		ft_putstr_fd("Error\n", 2);
		del_deque(pd);
		free(pd);
		exit(1);
	}
}

void	check_duplicate(t_pdeque *pd, int num)
{
	t_node	*tmp;

	tmp = pd->a->front;
	while (tmp)
	{
		if (tmp->num == num)
		{
			ft_putstr_fd("Error\n", 2);
			del_deque(pd);
			free(pd);
			exit(1);
		}
		tmp = tmp->next;
	}
}
