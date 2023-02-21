/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:22:41 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/21 01:08:29 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

double	slope(t_img *img)
{
	return (img->p->a / 1200);
}

double	str2double(char *s)
{
	double	p1;
	double	p2;
	char	*tmp;
	size_t	i;

	if (!s)
		return (0);
	p1 = (double) ft_atoi(s);
	p1 = p1 * ((*s != '-') - (*s == '-'));
	tmp = ft_strchr(s, '.');
	if (tmp && ++tmp)
		p2 = (double) ft_atoi(tmp);
	i = -1;
	while (tmp && ++i < ft_strlen(tmp))
		p2 /= 10.0;
	return ((p1 + p2) * ((*s != '-') - (*s == '-')));
}

void	mlx_create_window(t_var *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
		exit(EXIT_FAILURE);
	var->win = mlx_new_window(var->mlx, 1200, 1200, "FRACTAL");
}

void	mlx_create_image(t_var *var, t_img *img, t_julia *c, t_complex_plan *p)
{
	img->julia = c;
	img->nmax = 150;
	img->h = 1200;
	img->w = 1200;
	p->dx = 0;
	p->dy = 0;
	p->a = 4;
	p->b = 2;
//	img->fractal = 0;
	p->old_xc = 0;
	p->old_yc = 0;
	img->p = p;
	img->img = mlx_new_image(var->mlx, img->h, img->w);
	img->var = var;
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_len, &img->edn);
}

void	mlx_pixel_put_in_img(t_img *img, int x, int y, int color)
{
	int	*pixel;

	pixel = img->addr + (y * img->l_len + x * (img->bpp / 8));
	*pixel = color;
}
