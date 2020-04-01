/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:33:48 by user              #+#    #+#             */
/*   Updated: 2020/04/01 17:21:57 by user             ###   ########.fr       */
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

	// k1 = vec_dot(dir, dir);
	// k2 = vec_dot(OC, dir) * 2;
	// k3 = vec_dot(OC, OC) - sphere.radius * sphere.radius;
	// // printf("k1 = %f, k2 = %f, k3 = %f \n", k1, k2, k3);
	// discriminant = k2 * k2 - 4 * k1 * k3;
	// discriminant = ABS(discriminant);
	// float t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	// float t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
	// // printf("t1 = %f t2 = %f\n", t1, t2);
	// // printf("%f\n", discriminant); // !!!axtung!!! - дискриминант постоянно меньше нуля
	// if (t1 < 10000000 && t1 > 0)
	// 	return (1);
	// else if (t2 < 1000000 && t2 > 0)
	// 	return (1);
	// else
	// 	return (0);
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
	// float fov = M_PI / 2;


	sphere.center.x = -3;
	sphere.center.y = 0;
	sphere.center.z = -16;
	sphere.radius = 2;

	// origin - точка из которой смотрим
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
			// dir - это луч из точки камеры в напраление к сфере
			dir.x = i;	//(2 * (i + 0.5) / (float)WIDTH - 1) * tan(fov / 2) * WIDTH / (float)HEIGHT;
			dir.y = j;	//(2 * (j + 0.5) / (float)(HEIGHT - 1) * tan(fov/2));
			dir.z = -1;
			// printf("x = %f y = %f ", dir.x, dir.y);
			vector = cast_ray(camera, dir, sphere);
			// printf("x = %f y = %f z = %f\n", vector.x, vector.y, vector.z);

			SDL_SetRenderDrawColor(rtv1->rend, 255 * (vector.y / ((float)HEIGHT * 2)), vector.x * (255 / ((float)WIDTH * 2)), vector.z * (255 / ((float)WIDTH * 2)),
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

