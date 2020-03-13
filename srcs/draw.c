/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 08:05:31 by user              #+#    #+#             */
/*   Updated: 2020/03/13 12:13:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	get_color(int x, int y)
{
	t_color	color;

	// x = 0;
	// y = 0;
	color.channel[0] = 0;
	color.channel[1] =
		(255 * y);
	color.channel[2] =
		(225 * x);
	color.channel[3] =
		(0);
	return (color);
}

static void	put_pixel(t_rtv1 *rtv1, int x, int y, t_color color)
{
	int	i;

	i = (x * rtv1->bits_per_pixel / 8)
		+ (y * rtv1->line_size);
	rtv1->pixels_arr[i] = color.channel[3];
	rtv1->pixels_arr[++i] = color.channel[2];
	rtv1->pixels_arr[++i] = color.channel[1];
	rtv1->pixels_arr[++i] = color.channel[0];
}

void	put_pixel_to_img(t_rtv1 *rtv1, int x, int y, int color)
{
		color = mlx_get_color_value(rtv1->mlx, color);
		ft_memcpy(rtv1->pixels_arr + 4 * WIDTH * y + x * 4, &color,
			sizeof(int));
}

void	scuare(t_rtv1 *rtv1)
{
	int x;
	int y;

	y = HEIGHT / 2 - 100;
	while (y < HEIGHT / 2 + 100)
	{
		x = WIDTH / 2 - 100;
		while (x < WIDTH / 2 + 100)
		{
			put_pixel_to_img(rtv1, x, y, GREEN);
			x++;
		}
		y++;
	}
}

void	circle(t_rtv1 *rtv1)
{
	int x;
	int y;
	int r;
	double d;
	t_color	color;

	r = 160;
	y = 0;
	while (y < r * 2)
	{
		x = 0;
		while (x < r * 2)
		{
			d = sqrt((double)(y - r) * (y - r) + (x - r) * (x -r));
			if (d < r)
			{
				color = get_color(x, y);
				put_pixel(rtv1, x, y, color);
			}
			if (d < r + 0.5 && d > r - 0.5)
			{
				put_pixel_to_img(rtv1, x, y, GREEN);
			}
			x++;
		}
		y++;
	}
}

void	ft_draw(t_rtv1 *rtv1)
{
	int		x;
	int		y;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_color(x, y);
			// put_pixel(rtv1, x, y, color);
			put_pixel_to_img(rtv1, x, y, WHITE);
			x++;
		}
		y++;
	}
	scuare(rtv1);
	circle(rtv1);
	mlx_put_image_to_window(rtv1->mlx, rtv1->win, rtv1->img, 0, 0);
}
