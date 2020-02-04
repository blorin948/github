/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bmp.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 02:01:46 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:24:37 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"


static void	write_rgb(t_storage *ptr, int fd, int pad)
{
	unsigned char	zero[3];
	unsigned int	i;
	unsigned int	j;
	unsigned int			color;

	i = -1;
	while (++i < 3)
		zero[i] = 0;
	i = 0;
	while (i < ptr->resoy)
	{
		j = 0;
		while (j < ptr->resox)
		{
			color = ptr->t_img.image[i * ptr->resox + j];
           // printf("%d\n", color);
			write(fd, &color, 3);
		//	write(fd, &zero, pad);
			j++;
		}
        printf("lol\n");
		i++;
	}
}

unsigned char    *create_bitmap_file_header(int height,
                                            int width, int padding_size)
{
    int                        file_size;
    static unsigned char    file_header[] = {
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

unsigned char    *create_bitmap_info_header(int height, int width)
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

void            generate_bitmap_image(t_storage *r, int height, int width)
{
    int                    fd;
    unsigned char        *file_header;
    unsigned char        *info_header;

    file_header = create_bitmap_file_header(height, width,
                            (4 - (width * 3) % 4) % 4);
    info_header = create_bitmap_info_header(height, width);
    fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00700);
    if (fd < 0)
    {
        ft_putstr_fd("Error\n", 1);
        ft_putstr_fd("Create save.bmp file.", 1);
        exit(0);
    }
    write(fd, file_header, 14);
    write(fd, info_header, 40);
    write_rgb(r, fd,  (4 - (width * 3) % 4) % 4);
    close(fd);
}

void            save_bmp_file(t_storage *r)
{
    int        height;
    int        width;

    height = r->resoy;
    if (height % 2 == 1)
        height -= 1;
    width = r->resox;
    if (width % 2 == 1)
        width -= 1;
    generate_bitmap_image(r, height, width);
    exit(0);
}