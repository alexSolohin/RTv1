/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 17:03:17 by user              #+#    #+#             */
/*   Updated: 2020/04/01 17:24:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ray_intersect(t_vector orig, t_vector dir, t_sphere sphere)
{
	// float k1;
	// float k2;
	// float k3;
	// float discriminant;
	float t0;
	t_vector L;
	// dir - точка на луче;

	// printf("x = %f y = %f z = %f\n", orig.x, orig.y, orig.z);
	// printf("x = %f y = %f z = %f\n", sphere.center.x, sphere.center.y, sphere.center.z);
	L = vec_sub(sphere.center, orig);
	// printf("x = %f y = %f z = %f\n", OC.x, OC.y, OC.z);
	t0 = 1000000;
	float tca = vec_dot(L , dir);
	float d2 = vec_dot(L, L) - tca * tca;
	d2 *= -1;
	if (d2 > sphere.radius * sphere.radius)
		return (0);
	float thc = sqrtf(sphere.radius * sphere.radius - d2);
	t0 = tca - thc;
	float t1 = tca + thc;
	// printf("tca = %f d2 = %f thc = %f t0 = %f t1 = %f\n", tca, d2, thc, t0, t1);
	if (t0 < 0)
		t0 = t1;
	if (t0 < 0)
		return (0);
	return (1);
}

t_vector	cast_ray(t_vector orig, t_vector dir, t_sphere sphere)
{
	t_vector vector;

	vector.x = 1400;
	vector.y = 700;
	vector.z = 300;
	if (!ray_intersect(orig, dir, sphere))
	{
		vector.x = 300;
		vector.y = 700;
		vector.z = 1400;
		return (vector);
	}
	return (vector);
}

int		main(int ac, char **av)
{
	t_rtv1	*rtv1;
	int		x;
	int		y;
	t_color color;

	if (!(rtv1 = malloc(sizeof(t_rtv1))))
		exit (0);
	ac = 0;
	av = 0;

	t_vector camera;
	t_sphere sphere;
	t_vector vector;
	t_vector dir;
	// float fov = M_PI / 2;

	sphere.center.x = -3;
	sphere.center.y = 0;
	sphere.center.z = -16;
	sphere.radius = 2;

	// origin - точка из которой смотрим
	camera.x = 0;
	camera.y = 0;
	camera.z = 0;

	rtv1->mlx = mlx_init();
	ft_mlx_win_init(rtv1);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{

			dir.x = x;	//(2 * (i + 0.5) / (float)WIDTH - 1) * tan(fov / 2) * WIDTH / (float)HEIGHT;
			dir.y = y;	//(2 * (j + 0.5) / (float)(HEIGHT - 1) * tan(fov/2));
			dir.z = -1;

			vector = cast_ray(camera, dir, sphere);
			color.channel[0] = 0;									//ALPHA
			color.channel[1] = 255 * (vector.y / ((float)HEIGHT)); 	//RED
			color.channel[2] = vector.x * (255 / ((float)WIDTH));	//GREEN
			color.channel[3] = vector.z * (255 / ((float)WIDTH)); 	// BLUE
			put_pixel(rtv1, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rtv1->mlx, rtv1->win, rtv1->img, 0, 0);
	mlx_loop(rtv1->mlx);

}
