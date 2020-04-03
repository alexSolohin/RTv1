/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 11:01:03 by user              #+#    #+#             */
/*   Updated: 2020/04/03 16:56:00 by user             ###   ########.fr       */
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

void	put_pixel(t_rtv1 *rtv1, int x, int y, t_color color)
{
	int	i;

	i = (x * rtv1->bits_per_pixel / 8)
		+ (y * rtv1->line_size);
	rtv1->pixels_arr[i] = color.channel[3];
	rtv1->pixels_arr[++i] = color.channel[2];
	rtv1->pixels_arr[++i] = color.channel[1];
	rtv1->pixels_arr[++i] = color.channel[0];
}
