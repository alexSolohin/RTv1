/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:33:48 by user              #+#    #+#             */
/*   Updated: 2020/04/01 11:31:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SDL_SetRenderDrawColor(rtv1->rend, 100, 100, i++,
// 									255); - это невероятно красиво)

#include "rtv1.h"
#include <stdio.h>
#include "SDL.h"

float	vec_len(t_vector a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

float	vec_dot(t_vector a, t_vector b)
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

t_vector	vec_scale(t_vector v, float nb)
{
	v.x *= nb;
	v.y *= nb;
	v.z *= nb;
	return (v);
}

float	vec_magn(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vec_sub(t_vector a, t_vector b)
{
	b = vec_scale(b, -1);
	return (vec_add(a, b));
}

t_vector	vec_norm(t_vector v)
{
	return (vec_scale(v, 1.0 / vec_magn(v)));
}

int		ray_intersect(t_vector orig, t_vector dir, t_sphere sphere)
{
	float k1;
	float k2;
	float k3;
	float discriminant;
	t_vector OC;
	// dir - точка на луче;

	// printf("x = %f y = %f z = %f\n", orig.x, orig.y, orig.z);
	// printf("x = %f y = %f z = %f\n", sphere.center.x, sphere.center.y, sphere.center.z);
	OC = vec_sub(sphere.center, orig);
	// printf("x = %f y = %f z = %f\n", OC.x, OC.y, OC.z);
	k1 = vec_dot(dir, dir);
	k2 = vec_dot(OC, dir) * 2;
	k3 = vec_dot(OC, OC) - sphere.radius * sphere.radius;
	// printf("k1 = %f, k2 = %f, k3 = %f \n", k1, k2, k3);
	discriminant = k2 * k2 - 4 * k1 * k3;
	discriminant = ABS(discriminant);
	float t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	float t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
	// printf("t1 = %f t2 = %f\n", t1, t2);
	// printf("%f\n", discriminant); // !!!axtung!!! - дискриминант постоянно меньше нуля
	if (t1 < 10000000 && t1 > 0)
		return (1);
	else if (t2 < 1000000 && t2 > 0)
		return (1);
	else
		return (0);
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
	t_vector origin;
	t_sphere sphere;
	t_vector vector;
	t_vector dir;


	sphere.center.x = 1;
	sphere.center.y = 1;
	sphere.center.z = 2;
	sphere.radius = 1;

	// origin - точка из которой смотрим
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1));
	init_sdl(rtv1);
	j = 0;
	while (j < HEIGHT * 2) // HEIGHT * 2
	{
		i = 0;
		while (i < WIDTH * 2) // WIDTH * 2
		{
			// dir - это луч из точки камеры в напраление к сфере
			dir.x = i;
			dir.y = j;
			dir.z = 100;
			vector = cast_ray(origin, dir, sphere);
			// printf("x = %f y = %f z = %f\n", vector.x, vector.y, vector.z);
			SDL_SetRenderDrawColor(rtv1->rend, 255 * (vector.y / ((float)HEIGHT * 2)), vector.x * (255 / ((float)WIDTH * 2)), vector.z * (100 / ((float)WIDTH * 2)),
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

