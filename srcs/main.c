/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:33:48 by user              #+#    #+#             */
/*   Updated: 2020/04/12 18:28:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SDL_SetRenderDrawColor(rtv1->rend, 100, 100, i++,
// 									255); - это невероятно красиво)

#include "rtv1.h"
#include <stdio.h>
#include "SDL.h"

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

void		init_sdl(t_rtv1 *rtv1)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		if ((rtv1->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN))) // SDL_WINDOW_FULLSCREEN
			if (!(rtv1->rend = SDL_CreateRenderer(rtv1->window, -1,
			SDL_RENDERER_ACCELERATED)))
				printf("no");
	SDL_SetRenderDrawBlendMode(rtv1->rend, SDL_BLENDMODE_BLEND);
}

int		main()
{
	t_rtv1 *rtv1;
	SDL_Event event;
	size_t j;
	size_t i;
	t_vector camera;
	t_sphere sphere;
	t_vector vector;
	t_vector dir;
	t_light lights;
	float fov = M_PI / 2;

	lights.position.x = 2;
	lights.position.y = 2;
	lights.position.z = 2;
	lights.intensity = 1.5;

	sphere.center.x = 2;
	sphere.center.y = 2;
	sphere.center.z = 5;
	sphere.radius = 2;

	camera.x = 0;
	camera.y = 0;
	camera.z = 0;
	rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1));
	init_sdl(rtv1);
	j = 0;
	while (j < HEIGHT * 2) // HEIGHT * 2
	{
		i = 0;
		while (i < WIDTH * 2) // WIDTH * 2
		{
			dir.x = (2 * (i + 0.5) / (float)WIDTH - 1) * tan(fov / 2) * WIDTH / (float)HEIGHT;
			dir.y = (2 * (j + 0.5) / (float)(HEIGHT - 1) * tan(fov/2));
			dir.z = 1;
			dir = vec_norm(dir);
			vector = cast_ray(camera, dir, sphere, lights);
			SDL_SetRenderDrawColor(rtv1->rend, 255 * (vector.y), vector.x * (255), vector.z * (255),
									255);
			SDL_RenderDrawPoint(rtv1->rend, i, j);
			i++;
		}
		j++;
	}
	SDL_RenderPresent(rtv1->rend);
	while (1) 								//event on keyboard
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				exit(0);
	return (0);
}

