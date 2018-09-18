/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   select.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 09:48:02 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 04:43:42 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_select.h"

static int		ft_putc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

void			ft_tcaps_exec(const char *cmd)
{
	char		*cmd_target;

	if ((cmd_target = tgetstr((char *)cmd, NULL)))
		tputs(cmd_target, 1, ft_putc);
}

int				ft_select(t_select *select)
{
	char		buff[3];
	t_key		key;

	ft_bzero(buff, 3);
	key = KNONE;
	while (key != KESC && key != KENT)
	{
		ft_tcaps_exec("ho");
		ft_select_print(select);
		ft_tcaps_exec("cd");
		read(STDIN_FILENO, buff, 3);
		key = ft_key_get(buff, select);
		ft_bzero(buff, 3);
	}
	return ((key == KENT) ? 1 : 0);
}

int				main(int argc, const char *argv[])
{
	t_select	*select;

	if (!(select = ft_select_new(argc, argv)))
	{
		ft_putendl_fd("Usage : ./ft_select [FILE] ...", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if ((ft_enable_raw(&(select->termios))))
		return (EXIT_FAILURE);
	ft_handle_signal();
	ft_select_save(&select, 0);
	select->live = ft_select(select);
	ft_disable_raw(select->termios);
	if (select->live)
		ft_key_return(select);
	ft_select_delete(&select);
	return (EXIT_SUCCESS);
}
