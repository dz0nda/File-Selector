/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/26 09:48:02 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:07:58 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_select.h"

void			ft_tcaps_exec(const char *cmd)
{
	char		*cmd_target;

	if ((cmd_target = tgetstr((char *)cmd, NULL)))
		tputs(cmd_target, 1, ft_putchar);
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
		read(select->fd, buff, 3);
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
		ft_putendl_fd("Usage : ./ft_select [FILE] ...", 2);
		return (EXIT_FAILURE);
	}
	if ((select->fd = ft_enable_raw(&(select->termios))))
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
