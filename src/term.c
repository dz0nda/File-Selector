/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 04:56:35 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 04:56:44 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

static int			ft_error(const char *target)
{
	ft_putstr_fd("ft_select encountered a fatal error: ", STDERR_FILENO);
	ft_putendl_fd(target, 2);
	return (1);
}

int					ft_enable_raw(t_termios *org_term)
{
	char			*name;
	t_termios		raw;

	name = NULL;
	if (!(name = getenv("TERM")))
		return (ft_error("Terminal name could not be found."));
	if (tgetent(NULL, name) < 1)
		return (ft_error("Terminfo database could not be found."));
	if (!isatty(STDIN_FILENO))
		return (ft_error("File descriptor is not pointing to a TTY device."));
	if (tcgetattr(STDIN_FILENO, org_term) < 0)
		return (ft_error("Current configuration could not be found."));
	raw = *org_term;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1)
		return (ft_error("Raw mode could not be activate."));
	ft_tcaps_exec("vi");
	ft_tcaps_exec("ti");
	return (0);
}

int					ft_disable_raw(t_termios org_term)
{
	ft_tcaps_exec("te");
	ft_tcaps_exec("ve");
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
	return (0);
}
