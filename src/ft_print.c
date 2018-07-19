/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 01:53:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 04:47:38 by dzonda      ###    #+. /#+    ###.fr     */
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
	(select->lst->ftype[k] == ISEXEC) ? ft_putstr_fd(CYAN, STDIN_FILENO) : 0;
	(select->lst->ftype[k] == ISDIR) ? ft_putstr_fd(BOLD, STDIN_FILENO) : 0;
	(select->lst->ftype[k] == ISDIR) ? ft_putstr_fd(YELLOW, STDIN_FILENO) : 0;
	ft_putstr_fd(select->lst->lst[k], STDIN_FILENO);
	if (select->map.col_width < select->map.screen_width)
		if ((blank = select->map.col_width - ft_strlen(select->lst->lst[k])))
			while (blank-- > 0)
				ft_putchar_fd(' ', STDIN_FILENO);
	(select->lst->ftype[k] == ISEXEC || select->lst->ftype[k] == ISDIR) ?
		ft_putstr_fd(END, STDIN_FILENO) : 0;
	(k == select->id || select->lst->state[k]) ? ft_tcaps_exec("me") : 0;
	return (1);
}

static unsigned short	ft_select_print_help(t_select *select)
{
	if (50 < select->map.screen_width)
	{
		ft_putendl_fd("\r ------------------------------------------------- ",
			STDIN_FILENO);
		ft_putstr_fd(BOLD, STDIN_FILENO);
		ft_putendl_fd("\r| Quit : [ ESC ]           Finish : [ ENTER ]     |",
			STDIN_FILENO);
		ft_putendl_fd("\r| Select : [ SPACEBAR ]    Remove : [ BACKSPACE ] |",
			STDIN_FILENO);
		ft_putendl_fd("\r ------------------------------------------------- ",
			STDIN_FILENO);
		ft_putstr_fd(END, STDIN_FILENO);
		return (4);
	}
	return (0);
}

static unsigned short	ft_select_print_title(t_select *select)
{
	if (!(55 < select->map.screen_width))
		return (0 + ft_select_print_help(select));
	ft_putstr_fd(BOLD, STDIN_FILENO);
	ft_putstr_fd(BLUE, STDIN_FILENO);
	ft_putendl_fd("\r  _____  __                   .__                 __   ",
		STDIN_FILENO);
	ft_putendl_fd("\r_/ ____\\/  |_     ______ ____ |  |   ____   _____/  |_ ",
		STDIN_FILENO);
	ft_putendl_fd(
			"\r \\   __\\   __\\   /  ___// __ \\|  | _/ __ \\_/ ___\\   __\\",
		STDIN_FILENO);
	ft_putendl_fd(
			"\r |  |   |  |    \\ \\___ \\  ___/|  |_  ___/\\  \\___|  |   ",
		STDIN_FILENO);
	ft_putchar_fd('\r', STDIN_FILENO);
	ft_putendl_fd(" |__|   |__|____/____  >\\___  >____/\\___  >\\___  >__|   ",
		STDIN_FILENO);
	ft_putchar_fd('\r', STDIN_FILENO);
	ft_putendl_fd("          /_____/    \\/     \\/          \\/     \\/      ",
		STDIN_FILENO);
	ft_putstr_fd(END, STDIN_FILENO);
	return (6 + ft_select_print_help(select));
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
	while (h-- >= (select->map.screen_height - header))
		k += select->map.nb_col;
	while ((++y <= select->map.screen_height - header) && (k < select->live))
	{
		ft_putchar_fd('\r', STDIN_FILENO);
		while ((++x <= select->map.nb_col) && (k < select->live))
			if (ft_select_print_case(select, k++))
				if (x != select->map.nb_col)
					ft_putstr_fd("  ", STDIN_FILENO);
		(k < select->live) ? ft_tcaps_exec("cr") : 0;
		(k < select->live) ? ft_tcaps_exec("do") : 0;
		x = 0;
	}
}
