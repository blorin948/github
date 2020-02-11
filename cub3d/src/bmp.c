/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bmp.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 02:01:46 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 22:58:35 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../cub3d.h"

void			write_rgb(t_storage *ptr, int fd, int width, int height, int *img)
{
	int				i;
	int				j;
	unsigned int	color;

	j = 0;
	height = height - 1;
	i = height;
	while (i > 0)
	{
		j = 0;
		while (j < width)
		{
			color = img[i * ptr->resox + j];
			write(fd, &color, 3);
			j++;
		}
		i--;
	}
}

unsigned char	*create_bitmap_file_header(int height,
int width, int padding_size)
{
	int						file_size;
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
};

	file_size = 14 + 40 +
		(3 * width + padding_size) * height;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

unsigned char	*create_bitmap_info_header(int height, int width)
{
	static unsigned char info_header[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(3 * 8);
	return (info_header);
}

void			generate_bitmap_image(t_storage *r, int height, int width,
int *img)
{
	int						fd;
	unsigned char			*file_header;
	unsigned char			*info_header;

	file_header = create_bitmap_file_header(height, width,
	(4 - (width * 3) % 4) % 4);
	info_header = create_bitmap_info_header(height, width);
	fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00700);
	if (fd < 0)
	{
		ft_putstr("Error with save.bmp file\n");
		ft_exit(r);
	}
	write(fd, file_header, 14);
	write(fd, info_header, 40);
	write_rgb(r, fd, width, height, img);
	close(fd);
}

void			save_bmp_file(t_storage *ptr, int *img)
{
	int			height;
	int			width;

width = ptr->resox;
	height = ptr->resoy;
	if (width % 2 == 1)
		width -= 1;
	if (height % 2 == 1)
		height -= 1;
	generate_bitmap_image(ptr, height, width, img);
	ft_exit(ptr);
}
