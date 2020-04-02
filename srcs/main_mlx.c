/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 17:03:17 by user              #+#    #+#             */
/*   Updated: 2020/04/02 19:49:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ray_intersect(t_vector *orig, t_vector dir, t_sphere sphere)
{
	// float t0;
	// t_vector L;
	double t = 20000;

	t_vector oc = vec_sub(*orig, sphere.center);
	double b = 2 * vec_dot(oc, dir);
	double c = vec_dot(oc, oc) - sphere.radius * sphere.radius;
	double disc = b * b - 4 * c;
	if (disc < 0)
		return (0);
	else
	{
		disc = sqrt(disc);
		double t0 = -b - disc;
		double t1 = -b + disc;

		t = (t0 < t1) ? t0 : t1;
		return(1);
	}


	// dir - точка на луче;

	// printf("x = %f y = %f z = %f\n", orig.x, orig.y, orig.z);
	// printf("x = %f y = %f z = %f\n", sphere.center.x, sphere.center.y, sphere.center.z);

	// PLEASE ATTENTION:: ЭТА ФУНКЦИЯ ОСТАЕТСЯ ПОД ПРИСМОТРОМ ВРАЧЕЙ
	// PLEASE ATTENTION:: НЕОБХОДИМО НАЙТИ t0 t1 КАК ОТВЕТЫ КВАДРАТНОГО УРАВНЕНИЯ
	// PLEASE ATTENTION:: РАЗОБРАТЬСЯ В ВЕКТОРАХ
	// PLEASE ATTENTION:: ВЗЯТО ОТ СЮДА: https://m.habr.com/ru/post/436790/

	// L = vec_sub(sphere.center, *orig);
	// // printf("x = %f y = %f z = %f\n", L.x, L.y, L.z);
	// float tca = vec_magn(L) * vec_magn(dir);
	// float d2 = vec_magn(L) * vec_magn(L) - tca * tca;
	// // d2 *= -1;
	// if (d2 > sphere.radius * sphere.radius)
	// 	return (0);
	// float thc = sqrtf(sphere.radius * sphere.radius - d2);
	// t0 = tca - thc;
	// float t1 = tca + thc;
	// // printf("tca = %f d2 = %f thc = %f t0 = %f t1 = %f r = %f\n", tca, d2, thc, t0, t1, sphere.radius);
	// if (t0 < 0)
	// 	t0 = t1;
	// if (t0 < 0)
	// 	return (0);
	// return (1);
}

t_vector	cast_ray(t_vector *orig, t_vector dir, t_sphere sphere)
{
	t_vector vector;

	vector.x = 1400;
	vector.y = 700;
	vector.z = 300; 		// Светло зеленный
	if (!ray_intersect(orig, dir, sphere))
	{
		vector.x = 300;
		vector.y = 700;
		vector.z = 1400;	//Фиолетовый
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

	t_vector *camera;
	t_sphere sphere[10];
	t_vector vector;
	t_vector dir;
	float fov = M_PI / 2;

	sphere[0].center.x = -3;
	sphere[0].center.y = 15;
	sphere[0].center.z = -16;
	sphere[0].radius = 1;

	sphere[1].center.x = -3;
	sphere[1].center.y = 1;
	sphere[1].center.z = -1;
	sphere[1].radius = 1;

	sphere[2].center.x = -2;
	sphere[2].center.y = 2;
	sphere[2].center.z = -3;
	sphere[2].radius = 2;
	// camera - точка из которой смотрим
	if (!(camera = malloc(sizeof(t_vector))))
		exit(0);
	camera->x = 0;
	camera->y = 0;
	camera->z = 0;

	int i;

	i = 0;
	rtv1->mlx = mlx_init();
	ft_mlx_win_init(rtv1);
		y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while (x < WIDTH)
			{
				dir.x = (2 * (x + 0.5) / (float)WIDTH - 1) * tan(fov / 2) * WIDTH / (float)HEIGHT;
				dir.y = (2 * (y + 0.5) / (float)(HEIGHT - 1) * tan(fov / 2));
				dir.z = -1;
				// printf("dir.x = %f dir.y = %f		", dir.x, dir.y);
				dir = vec_norm(dir);
				// printf("dir.x = %f dir.y = %f\n", dir.x, dir.y);
				vector = cast_ray(camera, dir, sphere[i]);
				// vector = test(dir);
				color.channel[0] = 0;									//ALPHA
				color.channel[1] = 255 * (vector.y / ((float)HEIGHT)); 	//RED
				color.channel[2] = 255 * (vector.x / ((float)WIDTH));	//GREEN
				color.channel[3] = 255 * (vector.z / ((float)WIDTH)); 	// BLUE
				put_pixel(rtv1, x, y, color);
				x++;
			}
			y++;
		}
		mlx_put_image_to_window(rtv1->mlx, rtv1->win, rtv1->img, 0, 0);
		mlx_loop(rtv1->mlx);
}
