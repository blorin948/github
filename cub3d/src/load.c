/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:29:24 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:17:19 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		load2(t_storage *ptr)
{
	ptr->text[2].data = (int*)mlx_get_data_addr(ptr->text[2].img,
	&ptr->text[2].bpp, &ptr->text[2].sizeline, &ptr->text[2].endian);
	if (!(ptr->text[3].img = mlx_xpm_file_to_image(ptr->mlx_ptr,
	ptr->texture.sud, &ptr->text[3].x, &ptr->text[3].y)))
		return (error(ptr, "texture"));
	ptr->text[3].data = (int*)mlx_get_data_addr(ptr->text[3].img,
	&ptr->text[3].bpp, &ptr->text[3].sizeline, &ptr->text[3].endian);
	if (ptr->checkdoor > 0)
	{
		if (!(ptr->text[4].img = mlx_xpm_file_to_image(ptr->mlx_ptr,
	ptr->texture.porte, &ptr->text[4].x, &ptr->text[4].y)))
			return (error(ptr, "texture"));
		ptr->text[4].data = (int*)mlx_get_data_addr(ptr->text[4].img,
	&ptr->text[4].bpp, &ptr->text[4].sizeline, &ptr->text[4].endian);
	}
	if (!(ptr->text[5].img = mlx_xpm_file_to_image(ptr->mlx_ptr,
	ptr->texture.sprite, &ptr->text[5].x, &ptr->text[5].y)))
		return (error(ptr, "texture"));
	ptr->text[5].data = (int*)mlx_get_data_addr(ptr->text[5].img,
	&ptr->text[5].bpp, &ptr->text[5].sizeline, &ptr->text[5].endian);
	return (1);
}

int		load(t_storage *ptr)
{
	if (!(ptr->text[0].img = mlx_xpm_file_to_image(ptr->mlx_ptr,
		ptr->texture.nord, &ptr->text[0].x, &ptr->text[0].y)))
		return (error(ptr, "texture"));
	ptr->text[0].data = (int*)mlx_get_data_addr(ptr->text[0].img,
	&ptr->text[0].bpp, &ptr->text[0].sizeline, &ptr->text[0].endian);
	if (!(ptr->text[1].img = mlx_xpm_file_to_image(ptr->mlx_ptr,
		ptr->texture.est, &ptr->text[1].x, &ptr->text[1].y)))
		return (error(ptr, "texture"));
	ptr->text[1].data = (int*)mlx_get_data_addr(ptr->text[1].img,
	&ptr->text[1].bpp, &ptr->text[1].sizeline, &ptr->text[1].endian);
	if (!(ptr->text[2].img = mlx_xpm_file_to_image(ptr->mlx_ptr,
		ptr->texture.ouest, &ptr->text[2].x, &ptr->text[2].y)))
		return (error(ptr, "texture"));
	load2(ptr);
	return (1);
}

int		skybox(t_storage *ptr)
{
	int z;
	int f;
	int ju;

	if (!(ptr->t_img.img_ptr = mlx_new_image(ptr->mlx_ptr,
	ptr->resox, ptr->resoy)))
		return (error(ptr, "skybox"));
	if (!(ptr->t_img.img2 = mlx_xpm_file_to_image(ptr->mlx_ptr,
	ptr->texture.skybox, &ptr->t_img.imgx, &ptr->t_img.imgy)))
		return (error(ptr, "skybox"));
	if (!(ptr->t_img.text = (int*)mlx_get_data_addr(ptr->t_img.img2,
	&z, &f, &ju)))
		return (error(ptr, "skybox"));
	return (1);
}

int		check_text_p(char *line, t_storage *ptr, t_check *checkv)
{
	int i;
	int a;

	i = 2;
	a = 0;
	if (line[0] != 'P')
		return (0);
	checkv->p++;
	ptr->texture.porte = ft_strdup(line + i);
	return (1);
}
