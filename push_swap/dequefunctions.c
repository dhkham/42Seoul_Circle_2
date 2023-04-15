/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequefunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:13 by dkham             #+#    #+#             */
/*   Updated: 2023/03/18 17:40:59 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_node(int num)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->num = num;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	insert_front(t_deque *deque, int num)
{
	t_node	*node;

	node = create_node(num);
	if (deque->front == NULL)
	{
		deque->front = node;
		deque->rear = node;
	}
	else
	{
		node->next = deque->front;
		deque->front->prev = node;
		deque->front = node;
	}
	deque->cnt++;
}

void	insert_rear(t_deque *deque, int num)
{
	t_node	*node;

	node = create_node(num);
	if (deque->rear == NULL)
	{
		deque->rear = node;
		deque->front = node;
	}
	else
	{
		node->prev = deque->rear;
		deque->rear->next = node;
		deque->rear = node;
	}
	deque->cnt++;
}

int	delete_front(t_deque *deque, int *is_error)
{
	t_node	*temp;
	int		num;

	if (deque->front == NULL)
	{
		*is_error = 1;
		return (-1);
	}
	else
	{
		temp = deque->front;
		deque->front = deque->front->next;
		if (deque->front != NULL)
			deque->front->prev = NULL;
		num = temp->num;
		free(temp);
		deque->cnt--;
		return (num);
	}
}

int	delete_rear(t_deque *deque, int *is_error)
{
	t_node	*temp;
	int		num;

	if (deque->rear == NULL)
	{
		*is_error = 1;
		return (-1);
	}
	else
	{
		temp = deque->rear;
		deque->rear = deque->rear->prev;
		if (deque->rear != NULL)
			deque->rear->next = NULL;
		num = temp->num;
		free(temp);
		deque->cnt--;
		return (num);
	}
}
