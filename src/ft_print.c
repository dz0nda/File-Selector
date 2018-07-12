/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 01:53:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:07:58 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_select.h"

static int				ft_select_print_case(t_select *select, unsigned short k)
{
	int					blank;

	blank = 0;
	(k == select->id) ? ft_tcaps_exec("us") : 0;
	(select->lst->state[k] == SELECTED) ? ft_tcaps_exec("mr") : 0;
	(select->lst->ftype[k] == ISEXEC) ? ft_putstr_fd(CYAN, select->fd) : 0;
	(select->lst->ftype[k] == ISDIR) ? ft_putstr_fd(BOLD, select->fd) : 0;
	(select->lst->ftype[k] == ISDIR) ? ft_putstr_fd(YELLOW, select->fd) : 0;
	ft_putstr_fd(select->lst->lst[k], select->fd);
	if (select->map.col_width < select->map.screen_width)
		if ((blank = select->map.col_width - ft_strlen(select->lst->lst[k])) >
				0)
			while (blank-- > 0)
				ft_putchar_fd(' ', select->fd);
	(select->lst->ftype[k] == ISEXEC || select->lst->ftype[k] == ISDIR) ?
		ft_putstr_fd(END, select->fd) : 0;
	(k == select->id || select->lst->state[k]) ? ft_tcaps_exec("me") : 0;
	return (1);
}

static unsigned short	ft_select_print_title(t_select *select)
{
	if (!(55 < select->map.screen_width))
		return (0);
	ft_putendl_fd("  _____  __                   .__                 __   ",
		select->fd);
	ft_putendl_fd("_/ ____\\/  |_     ______ ____ |  |   ____   _____/  |_ ",
		select->fd);
	ft_putendl_fd(
			" \\   __\\   __\\   /  ___// __ \\|  | _/ __ \\_/ ___\\   __\\",
		select->fd);
	ft_putendl_fd(
			" |  |   |  |    \\ \\___ \\  ___/|  |_  ___/\\  \\___|  |   ",
		select->fd);
	ft_putendl_fd(" |__|   |__|____/____  >\\___  >____/\\___  >\\___  >__|   ",
		select->fd);
	ft_putendl_fd("          /_____/    \\/     \\/          \\/     \\/      ",
		select->fd);
	return (6);
}

static unsigned short	ft_select_print_help(t_select *select)
{
	if (50 < select->map.screen_width)
	{
		ft_putendl_fd(" ------------------------------------------------- ",
				select->fd);
		ft_putstr_fd(BOLD, select->fd);
		ft_putendl_fd("| Quit : [ ESC ]           Finish : [ ENTER ]     |",
				select->fd);
		ft_putendl_fd("| Select : [ SPACEBAR ]    Remove : [ BACKSPACE ] |",
				select->fd);
		ft_putendl_fd(" ------------------------------------------------- ",
				select->fd);
		ft_putstr_fd(END, select->fd);
		return (4);
	}
	return (0);
}

void					ft_select_print(t_select *select)
{
	unsigned short		y;
	unsigned short		x;
	unsigned short		k;
	unsigned short		h;
	unsigned short		header;

	y = 0;
	x = 0;
	k = 0;
	h = select->id / select->map.nb_col;
	header = 0;
	header += ft_select_print_title(select);
	header += ft_select_print_help(select);
	while (h-- >= (select->map.screen_height - header))
		k += select->map.nb_col;
	while ((++y <= select->map.screen_height - header) && (k < select->live))
	{
		while ((++x <= select->map.nb_col) && (k < select->live))
			if (ft_select_print_case(select, k++))
				if (x != select->map.nb_col)
					ft_putstr_fd("  ", select->fd);
		(k < select->live) ? ft_tcaps_exec("cr") : 0;
		(k < select->live) ? ft_tcaps_exec("do") : 0;
		x = 0;
	}
}
