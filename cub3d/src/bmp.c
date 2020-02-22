/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:27:01 by blorin            #+#    #+#             */
/*   Updated: 2020/02/21 23:27:05 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		set_header(unsigned char *header, int param)
{
	header[0] = (unsigned char)(param);
	header[1] = (unsigned char)(param >> 8);
	header[2] = (unsigned char)(param >> 16);
	header[3] = (unsigned char)(param >> 24);
}

void		imgbmp(t_storage *s, t_bmp *bmp, int *img)
{
	int x;
	int y;
	int i;

	y = s->resoy - 1;
	while (y >= 0)
	{
		x = -1;
		while (++x < s->resox)
		{
			bmp->color = img[y * s->resox + x];
			write(bmp->fd, &bmp->color, 3);
		}
		i = -1;
		while (++i < (4 - (s->resox * 3) % 4) % 4)
			write(bmp->fd, &bmp->pad, 1);
		y--;
	}
}

void		ft_header(t_storage *s, t_bmp *bmp)
{
	int i;

	i = 0;
	while (i < 14)
		bmp->header[i++] = 0;
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	bmp->header[10] = 54;
	i = 0;
	while (i < 40)
		bmp->info[i++] = 0;
	bmp->info[0] = 40;
	bmp->info[12] = 1;
	bmp->info[14] = 24;
	i = 0;
	while (i < 3)
		bmp->pad[i++] = 0;
	set_header(&bmp->header[2], bmp->size);
	set_header(&bmp->info[4], s->resox);
	set_header(&bmp->info[8], s->resoy);
	write(bmp->fd, bmp->header, 14);
	write(bmp->fd, bmp->info, 40);
}

void		save_bmp_file(t_storage *s, int *img)
{
	t_bmp	bmp;
	int		imgsize;

	imgsize = 3 * s->resox * s->resoy;
	bmp.size = 54 + imgsize;
	bmp.img = malloc((sizeof(char) * imgsize));
	ft_memset(bmp.img, 0, imgsize);
	bmp.fd = open("save.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	ft_header(s, &bmp);
	imgbmp(s, &bmp, img);
	ft_free(bmp.img);
	close(bmp.fd);
	ft_exit(s);
}
