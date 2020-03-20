/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 08:05:31 by user              #+#    #+#             */
/*   Updated: 2020/03/17 16:37:21 by user             ###   ########.fr       */
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
		(255 * (y / HEIGHT));
	color.channel[2] =
		(225 * (x / WIDTH));
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

double	vec_dot(t_o a, t_o b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
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

t_o		*canvas_to_viewport(int x, int y, int z)
{
	t_o *D;

	D = (t_viewport *)malloc(sizeof(t_viewport));
	D->x = x * WIDTH / 100;
	D->y = y * HEIGHT / 100;
	D->z = 10;
	return 	(D);
}

double	intersect_ray_sphere2(t_o *o, t_viewport *D, t_sphere *sphere)
{
	t_o	C = sphere->center;
}

double	intersect_ray_sphere(t_o *o, t_o *D, t_sphere *sphere)
{
	t_o	C = sphere->center;
	int r = sphere->radius;
	t_o oc;
	oc.x = o->x - C.x;
	oc.y = o->y - C.y;
	oc.z = o->z - C.z;

	double k1 = vec_dot(*D, *D);




}

t_color		trace_ray(t_o *o, t_viewport *D, int t_min, int t_max)
{
	int			closest_t = 10000;
	t_sphere	*closest_sphere = NULL;
	t_sphere	*sphere;
	t_color		color;

	sphere = malloc(sizeof(t_sphere));
	double t1 = intersect_ray_sphere(o, D, sphere);
	double t2 = intersect_ray_sphere2(o, D, sphere);
	if (t1 > t_min && t1 < t_max && t1 < closest_t)
	{
		closest_t = t1;
		closest_sphere = sphere;
	}
	if (t2 > t_min && t2 < t_max && t2 < closest_t)
	{
		closest_t = t2;
		closest_sphere = sphere;
	}
	if (closest_sphere == NULL)
	{
		color = get_color(0, 0);
		return color;
	}
	return closest_sphere->color;
}

void	ray_trace(t_rtv1 *rtv1)
{
	t_o			*o;
	int 		x;
	int 		y;
	t_o 		*D;
	t_color 	color;

	o = malloc(sizeof(t_o));
	o->x = 0;
	o->y = 0;
	o->z = 0;
	x = 0;
	D = malloc(sizeof(t_o));
	while (x < WIDTH)
	{
		y = 0;
		while(y < HEIGHT)
		{
			D = canvas_to_viewport(x, y, 10);
			color = trace_ray(o, D, 1, 10000);
			put_pixel(rtv1, x, y, color);
			y++;
		}
		x++;
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
