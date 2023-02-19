/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:41:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/19 22:56:27 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "fractol.h"

int	rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	create_color(int n)
{
	int	arr[1530];
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (++i < 256)
		arr[j++] = rgb(255, i, 0);
	i = 256;
	while (--i >= 0)
		arr[j++] = rgb(i, 255, 0);
	i = -1;
	while (++i < 256)
		arr[j++] = rgb(0, 255, i);
	i = 256;
	while (--i >= 0)
		arr[j++] = rgb(0, i, 255);
	i = -1;
	while (++i < 256)
		arr[j++] = rgb(i, 0, 255);
	i = 256;
	while (--i >= 0)
		arr[j] = rgb(255, 0, i);
	return (arr[n]);
}

int	display_fractal(t_img *img, int ac, char **av)
{
	if ((ac == 2 && str2double(av[1]) == MANDELBROT)
			|| (img->fractal == MANDELBROT))
	{
//		printf("=> Mandelbrot \n");
		return (display_mandelbrot_fractal(img), MANDELBROT);
	}
	if ((ac == 2 && str2double(av[1]) == BURNING_SHIP)
			|| (img->fractal == BURNING_SHIP))
	{
//		printf("=> Burning ship \n");
		return (display_burning_ship_fractal(img), 3);
	}
	if ((ac == 4 && str2double(av[1]) == JULIASET)
			|| (img->fractal = JULIASET))
	{
//		printf("=> Julia \n");
		if (ac != 0)
		{
			img->julia->cr = str2double(av[2]);
			img->julia->ci = str2double(av[3]);
		}
		return (display_julia_fractal(img), JULIASET);
	}
	return (0);
}

void	display_mandelbrot_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;

	img->fractal = MANDELBROT;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		img->p->xc =  -img->p->b + ((grid.x * img->p->a) / img->w) + img->p->dx;
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			img->p->yc = img->p->b - ((grid.y * img->p->a) / img->h) + img->p->dy;
			z.r = 0;
			z.i = 0;
			z.n  = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + img->p->xc;
				z.i = 2 * z.i * z.tmp + img->p->yc;
			}
			if (z.n != img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y, create_color(z.n));
			else
				mlx_pixel_put_in_img(img, grid.x, grid.y, 0);
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
	mlx_put_max_iteration(img);
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
			z.r = -img->p->b + (grid.x * img->p->a/ img->w) + img->p->dx;
			z.i = img->p->b - (grid.y * img->p->a/ img->h) + img->p->dy;
			z.n = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4.0)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + img->julia->cr;
				z.i = (2 * z.tmp * z.i) + img->julia->ci;
			}
			if (z.n == img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y, create_color(z.n));
			else
				mlx_pixel_put_in_img(img, grid.x, grid.y, 0);
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
	mlx_put_max_iteration(img);
}

void	mlx_put_max_iteration(t_img *img)
{
	char	*tmp;
	char	*iter;

	tmp = ft_itoa(img->nmax);
	iter = ft_strjoin(ITERATIONS, tmp);
	mlx_string_put(img->var->mlx, img->var->win, 10, 1170, RED, iter);
	mlx_string_put(img->var->mlx, img->var->win, 10, 30, RED, "Usage:");
	mlx_string_put(img->var->mlx, img->var->win, 20, 90, RED, "Arows       : moving fractal");
	mlx_string_put(img->var->mlx, img->var->win, 20, 110, RED, "Mouse wheel : zoom in && zoom out");
	mlx_string_put(img->var->mlx, img->var->win, 20, 70, RED, "R           : reset");
	mlx_string_put(img->var->mlx, img->var->win, 20, 50, RED, "ESC         : exit");
	free(tmp);
	free(iter);
	mlx_string_put(img->var->mlx, img->var->win, 900, 1170, RED, "Cr : 0.03");
	mlx_string_put(img->var->mlx, img->var->win, 1100, 1170, RED, "Ci : 0.03");
}
