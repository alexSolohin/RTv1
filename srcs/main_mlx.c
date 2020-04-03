/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 17:03:17 by user              #+#    #+#             */
/*   Updated: 2020/04/03 17:48:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"



int		ray_intersect(t_vector orig, t_vector dir, t_sphere sphere)
{
	// float t0;
	// t_vector L;
	double t = 20000;

	t_vector oc = vec_sub(orig, sphere.center);
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
}

int		scene_intersect(t_vector orig, t_vector dir, t_sphere sphere, t_vector hit, t_vector N)
{
	float sphere_dist = 10000;
	float dist_i = 0;
	if (ray_intersect(orig, dir, sphere) && dist_i < sphere_dist)
	{
		sphere_dist = dist_i;
		hit = vec_add(orig, vec_scale(dir, dist_i));
		N = vec_norm(vec_sub(hit, sphere.center));
	}
	return ((sphere_dist < 1000) ? 1 : 0);
}

t_vector	get_normal(t_vector pi, t_sphere sphere)
{
	return (vec_diff(vec_sub(pi, sphere.center), sphere.radius));
}

t_vector	cast_ray(t_vector orig, t_vector dir, t_sphere sphere, t_light light)
{
	t_vector point;
	t_vector N;
	t_vector vector;
	light.intensity = 0;
	point.x = 0;
	point.y = 0;
	point.z = 0;

	N.x = 0;
	N.y = 0;
	N.z = 0;
	// t_vector pi = vec_add(orig, vec_scale(dir, t));
	// t_vector L = vec_sub(sphere.center, pi);
	// t_vector N = get_normal(pi, sphere);
	// float dt = vec_dot(vec_normalize(L), vec_normalize(N));
	if (!scene_intersect(orig, dir, sphere, point, N))
	{
		vector.x = 0.3;
		vector.y = 0.7;		//Background
		vector.z = 0.8;	//Фиолетовый
		return (vector);
	}
	float diffuse_light_intensity = 0;
	t_vector light_dir = vec_sub(light.position, point);
	diffuse_light_intensity += light.intensity * vec_dot(light_dir, N);
	// printf("%f\n", dt);
	vector.x = 0.3 * diffuse_light_intensity;
	vector.y = 0.3 * diffuse_light_intensity;
	vector.z = 0.3 * diffuse_light_intensity;

	// vector.x = 1400;
	// vector.y = 700;
	// vector.z = 300; 		// Светло зеленный
	// if (!ray_intersect(orig, dir, sphere))
	// {
	// 	vector.x = 0.3;
	// 	vector.y = 0.7;		//Background
	// 	vector.z = 0.8;	//Фиолетовый
	// 	return (vector);
	// }
	return (vector);
}

int		main(int ac, char **av)
{
	t_rtv1	*rtv1;
	int		x;
	int		y;
	t_color color;

	t_light lights;

	lights.position.x = 0;
	lights.position.y = 0;
	lights.position.z = 2;
	lights.intensity = 1.5;

	if (!(rtv1 = malloc(sizeof(t_rtv1))))
		exit (0);
	ac = 0;
	av = 0;

	t_vector camera;
	t_sphere sphere;
	t_vector vector;
	t_vector dir;
	// float fov = M_PI / 2;

	sphere.center.x = 1;
	sphere.center.y = 1;
	sphere.center.z = 3;
	sphere.radius = 1;
	// camera - точка из которой смотрим
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
				dir.x = x / (float)WIDTH;//(2 * (x + 0.5) / (float)WIDTH - 1) * tan(fov / 2) * WIDTH / (float)HEIGHT; // printf("dir.x = %f dir.y = %f		", dir.x, dir.y);
				dir.y = y / (float)HEIGHT;//(2 * (y + 0.5) / (float)(HEIGHT - 1) * tan(fov / 2));
				dir.z = 1;
				dir = vec_norm(dir); 				// printf("dir.x = %f dir.y = %f\n", dir.x, dir.y);
				vector = cast_ray(camera, dir, sphere, lights);
				color.channel[0] = 0;									//ALPHA
				color.channel[1] = 255 * (vector.y ); 	//RED
				color.channel[2] = 255 * (vector.x);	//GREEN
				color.channel[3] = 255 * (vector.z); 	// BLUE
				put_pixel(rtv1, x, y, color);
				x++;
			}
			y++;
		}
	mlx_put_image_to_window(rtv1->mlx, rtv1->win, rtv1->img, 0, 0);
	mlx_loop(rtv1->mlx);
}
