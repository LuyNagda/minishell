/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:46:19 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/23 16:49:25 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>

static void	assign_values(t_env_map *current, t_env_map *original)
{
	current->key = original->key;
	current->value = original->value;
	current->has_equal = original->has_equal;
	current->is_system = original->is_system;
	current->is_immutable = original->is_immutable;
}

t_env_map	*duplicate_list(t_env_map *head)
{
	t_env_map	*new_head;
	t_env_map	*current;
	t_env_map	*original;

	new_head = malloc(sizeof(t_env_map));
	current = new_head;
	original = head;
	if (head == NULL)
		return (NULL);
	while (original != NULL)
	{
		assign_values(current, original);
		if (original->next_node != NULL)
		{
			current->next_node = malloc(sizeof(t_env_map));
			current = current->next_node;
		}
		else
			current->next_node = NULL;
		original = original->next_node;
	}
	return (new_head);
}

t_env_map	*merge(t_env_map *left, t_env_map *right)
{
	t_env_map	*result;

	result = NULL;
	if (left == NULL)
		return (right);
	if (right == NULL)
		return (left);
	if (ft_strncmp(left->key, right->key, ft_strlen(left->key)) < 0)
	{
		result = left;
		result->next_node = merge(left->next_node, right);
	}
	else
	{
		result = right;
		result->next_node = merge(left, right->next_node);
	}
	return (result);
}

t_env_map	*merge_sort(t_env_map *head)
{
	t_env_map	*slow;
	t_env_map	*fast;
	t_env_map	*left;
	t_env_map	*right;

	slow = head;
	fast = head->next_node;
	if (!head || !(head->next_node))
		return (head);
	while (fast != NULL && fast->next_node != NULL)
	{
		slow = slow->next_node;
		fast = fast->next_node->next_node;
	}
	left = head;
	right = slow->next_node;
	slow->next_node = NULL;
	left = merge_sort(left);
	right = merge_sort(right);
	return (merge(left, right));
}
