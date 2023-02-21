/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:41:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/21 01:54:32 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void set_rgb(t_rgb *rgb, float r, float g, float b)
{
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
}

int	hsv_to_rgb(int hue, float saturation, float value, t_img *img)
{
	float	c;
	float	x;
	float	m;
	t_rgb	rgb;

	(void) img;
	c = (value / 100.0) * (saturation / 100.0);
	x = c * (1 - ABS((fmod(((float) hue / 60.0), 2) - 1)));
	m = (value / 100.0) - c;
	if (hue >= 0 && hue < 60)
		set_rgb(&rgb, c, x, 0);
	if (hue >= 60 && hue < 120)
		set_rgb(&rgb, x, c, 0);
	if (hue >= 120 && hue < 180)
		set_rgb(&rgb, 0, c, x);
	if (hue >= 180 && hue < 240)
		set_rgb(&rgb, 0, x, c);
	if (hue >= 240 && hue < 300)
		set_rgb(&rgb, x, 0, c);
	if (hue >= 300 && hue < 360)
		set_rgb(&rgb, c, 0, x);
	rgb.r = (rgb.r + m) * 255 /*!(hue == (img->nmax * 5) % 360)*/;
	rgb.g = (rgb.g + m) * 255 /*!(hue == (img->nmax * 5) % 360)*/;
	rgb.b = (rgb.b + m) * 255 /*!(hue == (img->nmax * 5) % 360)*/;
	return ((int) rgb.r << 16 | (int) rgb.g << 8 | (int) rgb.b);
}

int	display_fractal(t_img *img, int ac, char **av)
{
	if ((ac == 2 && str2double(av[1]) == MANDELBROT)
		|| (img->fractal == MANDELBROT))
		display_mandelbrot_fractal(img);
	if ((ac == 4 && str2double(av[1]) == JULIASET)
		|| (img->fractal == JULIASET))
	{
		if (ac != 0)
		{
			img->julia->cr = str2double(av[2]);
			img->julia->ci = str2double(av[3]);
		}
		display_julia_fractal(img);
	}
	mlx_put_max_iteration(img);
	return (img->fractal);
}

void	display_mandelbrot_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;

	img->fractal = MANDELBROT;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		img->p->xc = -img->p->b + (grid.x * slope(img)) + img->p->dx;
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			img->p->yc = img->p->b - (grid.y * slope(img)) + img->p->dy;
			z.r = 0;
			z.i = 0;
			z.n = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + img->p->xc;
				z.i = 2 * z.i * z.tmp + img->p->yc;
			}
			mlx_pixel_put_in_img(img, grid.x, grid.y, hsv_to_rgb((z.n * 4) % 360, 100, 100, img));
			if (z.n == img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y, 0);
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
}

void	display_julia_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;

	img->fractal = JULIASET;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			z.r = -img->p->b + (grid.x * slope(img)) + img->p->dx;
			z.i = img->p->b - (grid.y * slope(img)) + img->p->dy;
			z.n = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4.0)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + img->julia->cr;
				z.i = (2 * z.tmp * z.i) + img->julia->ci;
			}
			mlx_pixel_put_in_img(img, grid.x, grid.y, hsv_to_rgb(((z.n * 4) % 360), 100, 100, img));
			if (z.n == img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y, 0);
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
}

void	mlx_put_max_iteration(t_img *img)
{
	char	*tmp;
	char	*iter;

	tmp = ft_itoa(img->nmax);
	iter = ft_strjoin(ITERATIONS, tmp);
	mlx_string_put(img->var->mlx, img->var->win, 10, 15, WHITE, USAGE);
	mlx_string_put(img->var->mlx, img->var->win, 20, 40, WHITE, U_ESC);
	mlx_string_put(img->var->mlx, img->var->win, 20, 60, WHITE, U_R);
	mlx_string_put(img->var->mlx, img->var->win, 20, 80, WHITE, U_ARROWS);
	mlx_string_put(img->var->mlx, img->var->win, 20, 100, WHITE, U_M_WHEEL);
	mlx_string_put(img->var->mlx, img->var->win, 10, 1170, WHITE, iter);
	free(tmp);
	free(iter);
}
