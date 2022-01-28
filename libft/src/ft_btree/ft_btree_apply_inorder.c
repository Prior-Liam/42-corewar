/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_inorder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:34:07 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/05 11:39:02 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_btree_apply_inorder(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	ft_btree_apply_inorder(root->left, applyf);
	applyf(root->item);
	ft_btree_apply_inorder(root->right, applyf);
}
