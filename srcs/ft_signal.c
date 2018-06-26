/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_signal.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 02:24:12 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 01:32:12 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			ft_handle_signal_quit(int signo)
{
	t_select		*select;

	(void)signo;
	ft_select_save(&select, 1);
	ft_disable_raw(select->termios);
	exit(EXIT_FAILURE);
}

static void			ft_handle_signal_tstp(int signo)
{
	t_select		*select;

	(void)signo;
	ft_select_save(&select, 1);
	signal(SIGTSTP, SIG_DFL);
	ioctl(select->fd, TIOCSTI, "\x1A");
	ft_disable_raw(select->termios);
}

static void			ft_handle_signal_resize(int signo)
{
	t_select		*select;

	ft_select_save(&select, 1);
	ft_tcaps_exec("ho");
	ft_tcaps_exec("cd");
	if (signo == SIGCONT)
	{
		ft_enable_raw(&(select->termios));
		signal(SIGTSTP, ft_handle_signal_tstp);
	}
	select->map = ft_select_get_map(select);
	ft_select_print(select);
}

void				ft_handle_signal(void)
{
	unsigned int	signo;

	signo = 0;
	while (++signo < 32)
	{
		if (signo == SIGINT || signo == SIGQUIT || signo == SIGTERM)
			signal(signo, ft_handle_signal_quit);
		if (signo == SIGTSTP)
			signal(signo, ft_handle_signal_tstp);
		if (signo == SIGCONT || signo == SIGWINCH)
			signal(signo, ft_handle_signal_resize);
	}
}
