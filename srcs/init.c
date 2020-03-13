/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:01:03 by user              #+#    #+#             */
/*   Updated: 2020/03/13 11:49:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			init_hook(t_rtv1 *rtv1)
{
	mlx_key_hook(rtv1->win, key_press, rtv1);
	mlx_hook(rtv1->win, 17, 0, ft_close, rtv1);
	return (0);
}

void		ft_mlx_win_init(t_rtv1 *rtv1)
{
	if (!(rtv1->win = mlx_new_window(rtv1->mlx, WIDTH, HEIGHT, "RTv1")))
		exit(0);
	rtv1->img = mlx_new_image(rtv1->mlx, WIDTH, HEIGHT);
	rtv1->pixels_arr = mlx_get_data_addr(rtv1->img,
		&rtv1->bits_per_pixel, &rtv1->line_size, &rtv1->endian);
}
