/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 17:03:17 by user              #+#    #+#             */
/*   Updated: 2020/04/12 18:24:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"



int		ray_intersect(t_vector orig, t_vector dir, t_sphere sphere)
{
	double t;

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

int		scene_intersect(t_vector orig, t_vector dir, t_sphere sphere, t_vector point, t_vector N)
{
	float sphere_dist = 10000;
	float dist_i = 0;
	if (!ray_intersect(orig, dir, sphere) && dist_i < sphere_dist)
	{
		dist_i = sphere_dist;
		point = vec_add(orig, vec_scale(dir, dist_i));
		N = vec_norm(vec_sub(point, sphere.center));
	}
	return ((dist_i < 1000) ? 1 : 0);
}

t_vector	get_normal(t_vector pi, t_sphere sphere)
{
	return (vec_diff(vec_sub(pi, sphere.center), sphere.radius));
}

t_vector	cast_ray(t_vector orig, t_vector dir, t_sphere sphere, t_light light)
{
	t_spvec	point;
	t_vector vector;
	point.point.x = 0;
	point.point.y = 0;
	point.point.z = 0;

	if (!scene_intersect(orig, dir, sphere, point.point, point.N))
	{
		vector.x = 0.1 ;
		vector.y = 0.1 ;		//Background
		vector.z = 0.1 ;		//Фиолетовый
		return (vector);
	}
	float diffuse_light_intensity = 0;
	t_vector light_dir = vec_norm(vec_sub(light.position, point.point));
	// printf("x = %f y = %f z = %f", light_dir.x, light_dir.y, light_dir.z);
	// printf("x = %f y = %f z = %f", point.N.x, point.N.y, point.N.z);
	diffuse_light_intensity += light.intensity * vec_dot(light_dir, point.N);
	// printf("%f\n", diffuse_light_intensity);
	vector.x = 0.5 * diffuse_light_intensity;
	vector.y = 0.1 * diffuse_light_intensity;
	vector.z = 0.9 * diffuse_light_intensity;
	return (vector);
}

int		main(int ac, char **av)
{
	t_rtv1	*rtv1;
	int		x;
	int		y;
	t_color color;

	t_light lights;

	lights.position.x = 2;
	lights.position.y = 2;
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
	float fov = M_PI / 2;

	sphere.center.x = 5;
	sphere.center.y = 4;
	sphere.center.z = 10;
	sphere.radius = 5;
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
				dir.x = (2 * (x + 0.5) / (float)WIDTH - 1) * tan(fov / 2) * WIDTH / (float)HEIGHT;
				dir.y = (2 * (y + 0.5) / (float)(HEIGHT - 1) * tan(fov / 2));
				dir.z = 1;
				dir = vec_norm(dir); 				// printf("dir.x = %f dir.y = %f\n", dir.x, dir.y);
				vector = cast_ray(camera, dir, sphere, lights);
				printf("x = %f y = %f z = %f\n", vector.x, vector.y, vector.z);
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
