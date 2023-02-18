/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:22:41 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/18 18:58:03 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

double	ft_power(double base, double power)
{
	if (power > 0)
		return (base * ft_power(base, --power));
	return (1);
}

double	str2double(char *s)
{
	double	p1;
	double	p2;
	char	*tmp;

	if (!s)
		return (0);
	p1 = (double) ft_atoi(s);
	p1 = p1 * ((*s != '-') - (*s == '-')); 
	tmp = ft_strchr(s, '.');
	if (tmp && ++tmp)
		p2 = (double) ft_atoi(tmp) / ft_power(10, ft_strlen(tmp));
	return ((p1 + p2) * ((*s != '-') - (*s == '-')));
}

void	mlx_create_window(t_var *var)
{
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, 1200, 1200, "FRACTAL");
}

void	mlx_create_image(t_var *var, t_img *img, t_julia *c, t_complex_plan *p)
{
	img->julia = c;
	// Zn+1 = Zn^2 + C
	img->nmax = 255;

	// DEMANSION
	img->h = 1200;
	img->w = 1200;

	// MOUSE POSITION
//	p->m_x = 600;
//	p->m_y = 600;
	

	// DX && DY
	p->dx = 0;
	p->dy = 0;
	// F(X) = AX + B
	p->a = 4;
	p->b = 2;
	// OLD POSITION IN COMPLEX PLAN
	p->old_xc = 0;
	p->old_yc = 0;
	img->p = p;

	img->img = mlx_new_image(var->mlx, img->h, img->w);
	img->var = var;
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

void	mlx_pixel_put_in_img(t_img *img, int x, int y, int color)
{
	int	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*pixel = color;
}
