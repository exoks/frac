/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/17 20:26:56 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	close_window(t_img *img)
{
	exit(mlx_destroy_window(img->var->mlx, img->var->win) * 0);
}

int	on_press_button(int code, t_img *img)
{
	if (code == ESC)
		close_window(img);
	if (code == PLUS || code == MINUS)
	{
		img->nmax += 10 * ((code == PLUS) - (code == MINUS));
		ft_printf("Iterations => %30d\n", img->nmax);
	}
	if (code == RESET || (code >= MOVE_RIGHT && code <= MOVE_UP))
	{
		if (code == RESET)
			mlx_create_image(img->var, img, img->julia, img->plan);
		img->plan->dx += (img->plan->x / 10.0) * ((code == MOVE_LEFT) - (code == MOVE_RIGHT));
		img->plan->dy += (img->plan->y / 10.0) * ((code == MOVE_UP) - (code == MOVE_DOWN));
	}
	if (img->fractal == MANDELBROT)
			display_mandelbrot_fractal(img);
	if (img->fractal == JULIASET)
			display_julia_fractal(img);
	if (img->fractal == 3)
			display_burning_ship_fractal(img);
	return (0);
}

// MAKE ANY POINT YOU CHOSE AS THE REFERENCE POINT
int	zoom(int code, int x, int y, t_img *img)
{
	int	i;
	double	new_x, new_y;

	if (!(x == img->plan->m_x && y == img->plan->m_y))
	{
			img->plan->old_x = -img->plan->y + (((double) x) * img->plan->x / img->w) + img->plan->dx;
			img->plan->old_y = img->plan->y - (((double) y) * img->plan->x / img->h) + img->plan->dy;
	}
	img->plan->m_y = y;
	img->plan->m_x = x;
	if (code == SCROLL_DOWN || code == SCROLL_UP)
	{
		img->plan->x /= 1.3 * (code == 4) +  (1 / 1.4) * (code == 5);
		img->plan->y /= 1.3 * (code == 4) + (1 / 1.4) * (code == 5);
		new_x = -img->plan->y + (((double) x) * img->plan->x / img->w);
		new_y = img->plan->y - (((double) y) * img->plan->x / img->h);
		img->plan->dx = img->plan->old_x - new_x;
		img->plan->dy = img->plan->old_y - new_y;
	}
	if (img->fractal == MANDELBROT)
			display_mandelbrot_fractal(img);
	if (img->fractal == JULIASET)
			display_julia_fractal(img);
	if (img->fractal == 3)
		display_burning_ship_fractal(img);
	return (0);
}

int	display_fractal(t_img *img, int ac, char **av)
{
	if (ac == 2 && str2double(av[1]) == MANDELBROT)
		return (display_mandelbrot_fractal(img), MANDELBROT);
	if (ac == 4 && str2double(av[1]) == JULIASET)
	{
		img->julia->cr = str2double(av[2]);
		img->julia->ci = str2double(av[3]);
		return (display_julia_fractal(img), JULIASET);
	}
	return (0);
}
int	main(int ac, char **av)
{
	t_var			var;
	t_img			img;
	t_julia			julia;
	t_c_plan		plan;
	
	mlx_create_window(&var, "FRACTAL");
	mlx_create_image(&var, &img, &julia, &plan);
	if (!display_fractal(&img, ac, av))
		return (display_options(), EXIT_SUCCESS);
//	display_burning_ship_fractal(&img);
	mlx_key_hook(var.win, on_press_button, &img);
	mlx_mouse_hook(img.var->win, zoom, &img);
	mlx_hook(var.win, 17, 0, close_window, &img);
	mlx_loop(var.mlx);
	return (EXIT_SUCCESS);
}

// EACH POINT IS A COMPLEX NUMBER : I CHECK EVERY PIXEL USING Zn = Zn+1 ^ 2 + C : IF NOT DEVERGE UNDER ITERATION OF 0 THEN THIS POINT FROM MANDELBROT SET ?
// HOW CAN I GET THE INFORMATION OF EACH PIXEL
//  RADIUS : CHO3A3 OF MANDEL BROT SET IS < 2 : SO IF THE PIXEL IS NOT DEVERGE AND (LMANDAM DYALHA) NOT >= 2 THEN THIS POINT IS A MANDEL BROT SET
//
// FIRST C REPRESENT EACH POINT OF MY PIXEL GRADE => I HAVE TO CHECK EACH PIXEL AND SEE IF DEVERGE OR NOT DEVERGE => THIS PART DETERMINE IF I HAVE TO DRAW THIS POINT OR NOT
