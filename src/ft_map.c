/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_map.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 05:52:45 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 04:32:16 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_select.h"

static int			ft_select_get_maxlen(t_lstsel lst)
{
	size_t			k;
	size_t			len;

	k = 0;
	len = 0;
	while (lst.lst[k])
	{
		if (ft_strlen(lst.lst[k]) > len)
			len = ft_strlen(lst.lst[k]);
		k++;
	}
	return ((int)len);
}

t_select_map		ft_select_get_map(t_select *select)
{
	t_select_map	map;
	struct winsize	sz;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &sz);
	map.screen_width = (int)(sz.ws_col - 2);
	map.screen_height = (int)(sz.ws_row - 2);
	map.col_width = ft_select_get_maxlen(*(select->lst));
	if ((map.nb_col = (map.screen_width / map.col_width)) <= 0)
		map.nb_col = 1;
	while ((map.col_width * map.nb_col) + ((map.nb_col - 1) * 2)
		>= map.screen_width && map.nb_col > 1)
		map.nb_col--;
	if ((map.nb_row = (select->live / map.nb_col)) <= 0)
		map.nb_row = 1;
	while ((map.nb_row * map.nb_col) < select->live)
		map.nb_row++;
	return (map);
}
