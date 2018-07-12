/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/06 00:06:07 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:07:55 by dzonda      ###    #+. /#+    ###.fr     */
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

	ioctl(select->fd, TIOCGWINSZ, &sz);
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

static int			ft_error(const char *target)
{
	ft_putstr_fd("ft_select has encountered a fatal error: ", 2);
	ft_putendl_fd(target, 2);
	return (1);
}

int					ft_enable_raw(t_termios *org_term)
{
	char			*name;
	int				fd;
	t_termios		raw;

	name = NULL;
	fd = 0;
	if (!(name = getenv("TERM")))
		return (ft_error("Terminal name could not be found."));
	if (tgetent(NULL, name) < 1)
		return (ft_error("Terminfo database could not be found."));
	if (!isatty(fd))
		return (ft_error("File descriptor is not pointing to a TTY device."));
	if (tcgetattr(fd, org_term) < 0)
		return (ft_error("Current configuration could not be found."));
	raw = *org_term;
	raw.c_iflag &= ~(ICRNL);
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSANOW, &raw) == -1)
		return (ft_error("Raw mode could not be activate."));
	ft_tcaps_exec("vi");
	ft_tcaps_exec("ti");
	return (fd);
}

int					ft_disable_raw(t_termios org_term)
{
	ft_tcaps_exec("te");
	ft_tcaps_exec("ve");
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
	return (0);
}
