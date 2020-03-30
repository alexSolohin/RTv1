/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:33:48 by user              #+#    #+#             */
/*   Updated: 2020/03/30 11:23:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SDL_SetRenderDrawColor(rtv1->rend, 100, 100, i++,
// 									255); - это невероятно красиво)

#include "rtv1.h"
#include <stdio.h>
#include "SDL.h"

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

// int		main(int ac, char **av)
// {
// 	t_rtv1	*rtv1;

// 	av = 0;
// 	ac = 2;
// 	if (!(rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1))))
// 		exit(0);
// 	if (ac == 2)
// 	{
// 		rtv1->mlx = mlx_init();
// 		ft_mlx_win_init(rtv1);
// 		init_hook(rtv1);
// 		draw(rtv1);
// 		draw_button(rtv1);
// 		mlx_loop(rtv1->mlx);
// 	}
// 	return (0);
// }

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



int		ray_intersect(t_vector orig, t_vector dir, float t0, t_sphere sphere)
{


	t_vector	L;
	L = vec_sub(sphere.center, orig);
	// printf("%f %f %f\n", L.x, L.y, L.z);
	float tca = vec_dot(L, dir);
	float d2 = vec_dot(L, L) - tca * tca;
	// printf("%f %f\n", tca, d2);
	if (d2 > sphere.radius * sphere.radius)
		return (0);
	float thc = sqrtf(sphere.radius * sphere.radius - d2);
	t0 = tca - thc;
	float t1 = tca + thc;
	if (t0 < 0)
		t0 = t1;
	if (t0 < 0)
		return (0);
	return (1);
}

t_vector	cast_ray(t_vector orig, t_vector dir, t_sphere sphere)
{
	t_vector vector;

	vector.x = 0.4;
	vector.y = 0.4;
	vector.z = 0.3;
	float sphere_dist = 10000000;
	if (!ray_intersect(orig, dir, sphere_dist, sphere))
	{
		vector.x = 0.2;
		vector.y = 0.7;
		vector.z = 0.8;
		return (vector);
	}
	return (vector);
}

int		main()
{
	t_rtv1 *rtv1;
	SDL_Event event;
	size_t j;
	size_t i;
	t_vector origin;
	t_sphere sphere;
	// t_color		color;
	// int	fov = M_PI/2;
	t_vector vector;
	t_vector dir;


	sphere.center.x = 3;
	sphere.center.y = 0;
	sphere.center.z = 16;
	sphere.radius = 2;

	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1));
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		if ((rtv1->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN))) // SDL_WINDOW_FULLSCREEN
			if (!(rtv1->rend = SDL_CreateRenderer(rtv1->window, -1,
			SDL_RENDERER_ACCELERATED)))
				printf("no");
	SDL_SetRenderDrawBlendMode(rtv1->rend, SDL_BLENDMODE_BLEND);
	j = 0;
	while (j < HEIGHT * 2)
	{
		i =  0;
		while (i < WIDTH * 2)
		{
			// float x = (2 * (i + 0.5) / (float)WIDTH) * tan(fov / 2.) * (float)WIDTH / (float)HEIGHT;
			// float y = (2 * (j + 0.5) / (float)HEIGHT) * tan(fov / 2.);
			// printf("%f %f\n", x, y);
			dir.x = i;
			dir.y = j;
			dir.z = -1;
			// printf("%f %f %f\n", dir.x, dir.y, dir.z);
			vector = cast_ray(origin, dir, sphere);
			// printf("%f %f %f\n", vector.x, vector.y, vector.z);
			SDL_SetRenderDrawColor(rtv1->rend, 255 * (j / ((float)HEIGHT * 2)), 255 * (i / ((float)WIDTH * 2)), 0,
									255);
			SDL_RenderDrawPoint(rtv1->rend, i, j);
			i++;
		}
		j++;
	}
	// circle(rtv1);
	SDL_RenderPresent(rtv1->rend);
	while (1)
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				exit(0);
	return (0);
}

// int		main()
// {
// 	SDL_Init(SDL_INIT_EVERYTHING);

// 	SDL_Surface *screen;
// 	SDL_Window *window;

// 	screen = NULL;
// 	window = SDL_CreateWindow("rtv1", SDL_WINDOWPOS_UNDEFINED,
// 								SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
// 								SDL_WINDOW_SHOWN);
// 	// if (window == NULL)
// 	// 	return (1);

// 	screen = SDL_GetWindowSurface(window);
// 	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
// 	SDL_UpdateWindowSurface(window);
// 	SDL_Delay(2000);
// 	SDL_DestroyWindow(window);
// 	SDL_Quit();
// }


void	circle(t_rtv1 *rtv1)
{
	int x;
	int y;
	double r;
	double d;
	// t_color	color;

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
				SDL_SetRenderDrawColor(rtv1->rend, 100, 88, 255,
									100);
				SDL_RenderDrawPoint(rtv1->rend, x, y);
			}
			if (d < r + 0.5 && d > r - 0.5)
			{
				SDL_SetRenderDrawColor(rtv1->rend, 0, 0, 0,
									255);
				SDL_RenderDrawPoint(rtv1->rend, x, y);
			}
			x++;
		}
		y++;
	}
}
