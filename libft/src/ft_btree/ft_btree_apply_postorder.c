/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_postorder.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:37:33 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/05 11:42:48 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_btree_apply_postorder(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	ft_btree_apply_postorder(root->left, applyf);
	ft_btree_apply_postorder(root->right, applyf);
	applyf(root->item);
}
