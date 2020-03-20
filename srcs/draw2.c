/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 11:44:31 by user              #+#    #+#             */
/*   Updated: 2020/03/17 16:38:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	vec_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vec_add(t_vector v1, t_vector v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vector	vec_scale(t_vector v, double nb)
{
	v.x *= nb;
	v.y *= nb;
	v.z *= nb;
	return (v);
}

t_vector	vec_sub(t_vector a, t_vector b)
{
	b = vec_scale(b, -1);
	return (vec_add(a, b));
}


// t_color	get_color(int x, int y)
// {
// 	t_color	color;

// 	// x = 0;
// 	// y = 0;
// 	color.channel[0] = 0;
// 	color.channel[1] =
// 		(y);
// 	color.channel[2] =
// 		(x));
// 	color.channel[3] =
// 		(0);
// 	return (color);
// }

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

double 		interspect_ray_sphere(t_vector O, t_vector D, t_sphere sphere)
{
	t_vector C = sphere.center;
	int r = sphere.radius;
	t_vector OC = vec_sub(O, C);
	double k1 = vec_dot(D, D);
	double k2 = 2 * vec_dot(OC, D);
	double k3 = vec_dot(OC, OC) - r * r;

	double discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
		return -1;
	double t1 = (-k2 + pow(discriminant, 2)) / (2 * k1);
	return t1;
}

double 		interspect_ray_sphere2(t_vector O, t_vector D, t_sphere sphere)
{
	t_vector C = sphere.center;
	int r = sphere.radius;
	t_vector OC = vec_sub(O, C);
	double k1 = vec_dot(D, D);
	double k2 = 2 * vec_dot(OC, D);
	double k3 = vec_dot(OC, OC) - r * r;

	double discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
		return -1;
	double t2 = (-k2 - pow(discriminant, 2)) / (2 * k1);
	return t2;
}

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

t_color		trace_ray(t_vector O, t_vector D, int min, int max)
{
	double			closest_t = 10000;
	t_sphere		closest_sphere;
	int i = 0;
	t_color 	color;

	color.channel[0] = 0;
	color.channel[1] = 0;
	color.channel[2] = 0;
	color.channel[3] = 255;
	t_sphere sphere1;

	sphere1.center.x = 0;
	sphere1.center.y = -1;
	sphere1.center.z = 3;
	sphere1.radius = 1;
	sphere1.color.channel[0] = 0;
	sphere1.color.channel[1] = 255;
	sphere1.color.channel[2] = 0;
	sphere1.color.channel[3] = 0;

	double t1;
	double t2;

	t1 = interspect_ray_sphere(O, D, sphere1);
	t2 = interspect_ray_sphere2(O, D, sphere1);
	if (t1 > min && t1 < max && t1 < closest_t)
	{
		closest_t = t1;
		closest_sphere = sphere1;
		i = 1;
	}
	if (t2 > min && t2 < max && t2 < closest_t)
	{
		closest_t = t2;
		closest_sphere = sphere1;
		i = 1;
	}
	if (i == 0)
		return (color);
	return (sphere1.color);
}

t_vector	canvas_view_port(int x, int y)
{
	t_vector D;

	D.x = x * VWIDTH / WIDTH;
	D.y = y * VHEIGHT / WIDTH;
	D.z = 1;
	return (D);
}

void	draw(t_rtv1	*rtv1)
{
	int x;
	int y;
	t_vector O;
	t_vector D;
	t_color  color;

	O.x = 0;
	O.y = 0;
	O.z = 0;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			D = canvas_view_port(x, y);
			color = get_color(x, y);
			put_pixel(rtv1, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(rtv1->mlx, rtv1->win, rtv1->img, 0, 0);
}

// void	ft_draw(t_rtv1 *rtv1)
// {
// 	int		x;
// 	int		y;
// 	t_color	color;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			color = get_color(x, y);
// 			// put_pixel(rtv1, x, y, color);
// 			put_pixel_to_img(rtv1, x, y, WHITE);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(rtv1->mlx, rtv1->win, rtv1->img, 0, 0);
// }
