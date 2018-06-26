/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_select.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/03 08:02:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 01:33:56 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>

# define END "\x1b[0m"
# define BOLD "\x1b[1m"
# define YELLOW "\x1b[33m"
# define LIGHTYELLOW "\x1b[34m"
# define CYAN "\x1b[36m"

typedef struct termios	t_termios;
typedef struct stat		t_stat;

typedef enum		e_key
{
	KNONE,
	KENT,
	KUP,
	KDOWN,
	KRIGHT,
	KLEFT,
	KDEL,
	KESC,
	KSPACE
}					t_key;

typedef enum		e_filetype
{
	ISREG,
	ISDIR,
	ISEXEC
}					t_filetype;

typedef enum		e_state
{
	CLEAR,
	HOVER,
	SELECTED,
	DELETED
}					t_state;

typedef struct		s_lstsel
{
	char			*lst[4096];
	t_filetype		ftype[4096];
	t_state			state[4096];
}					t_lstsel;

typedef struct		s_select_map
{
	int				screen_width;
	int				screen_height;
	int				nb_col;
	int				nb_row;
	int				col_width;
}					t_select_map;

typedef struct		s_select
{
	t_termios		termios;
	int				fd;
	int				id;
	unsigned short	idy;
	unsigned short	idx;
	int				live;
	t_lstsel		*lst;
	t_select_map	map;
}					t_select;

/*
**					ft_select.c
*/

void				ft_tcaps_exec(const char *cmd);
int					ft_select(t_select *select);
int					main(int argc, const char *argv[]);

/*
**					ft_select_config.c
*/

void				ft_select_delete(t_select **select);
void				ft_select_save(t_select **select, int stat);
t_lstsel			*ft_select_get_lst(const char *argv[], int argc,
		int idtarget);
t_select			*ft_select_new(int argc, const char *argv[]);

/*
**					ft_term.c
*/

t_select_map		ft_select_get_map(t_select *select);
int					ft_enable_raw(t_termios *org_term);
int					ft_disable_raw(t_termios org_term);

/*
**					ft_signal.c
*/

void				ft_handle_signal(void);

/*
**					ft_print.c
*/

void				ft_select_print(t_select *select);

/*
**					ft_keys.c
*/

t_key				ft_key_return(t_select *select);
t_key				ft_key_get(char buff[3], t_select *select);
t_key				ft_key_update_id_auto(t_select *select, unsigned int buff,
					char *lst[]);

#endif
