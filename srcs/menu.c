/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:00:30 by rmaxima           #+#    #+#             */
/*   Updated: 2020/03/16 14:08:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int				in_button(int x, int y)
{
	if (y >= 0 && y < B_H)
		if (x >= WIDTH - 200 && x < WIDTH)
			return (1);
	return (0);
}

static void		string_help_second(t_rtv1 *rtv1)
{
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 160,
		GREEN, "            < >");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 190,
		0x0f4c81, "Colors: ");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 190,
		GREEN, "            P");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 220,
		0x0f4c81, "Exit: ");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 220,
		GREEN, "            ESC");
}

static void		string_help(t_rtv1 *rtv1)
{
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 50,
		0x0f4c81, "Change color: ");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 50,
		GREEN, "              0-9");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 80,
		0x0f4c81, "Zoom: ");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 80,
		GREEN, "      left button/");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 100,
		GREEN, "right button, mouse");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 130,
		0x0f4c81, "Position: ");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 130,
		GREEN, "          arrows");
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH - 200, 160,
		0x0f4c81, "Iterations: ");
	string_help_second(rtv1);
}

void			draw_help(t_rtv1 *rtv1)
{
	int x;
	int y;

	y = B_H + 1;
	while (y < 250)
	{
		x = WIDTH - 200;
		while (x < WIDTH)
		{
			mlx_pixel_put(rtv1->mlx, rtv1->win, x, y, 0xff);
			x++;
		}
		y++;
	}
	string_help(rtv1);
}

void			draw_button(t_rtv1 *rtv1)
{
	int x;
	int y;
	int i;

	i = 0;
	y = 0;
	while (y < HEIGHT / 50)
	{
		x = WIDTH / 2 - 200;
		while (x < WIDTH / 2 + 200)
		{
			mlx_pixel_put(rtv1->mlx, rtv1->win, x, y, 0xffff);
			x++;
		}
		y++;
	}
	mlx_string_put(rtv1->mlx, rtv1->win, WIDTH / 2 - 70, 2,
		0x000000, "Choose a figure");
}
