/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:38:18 by eduwer            #+#    #+#             */
/*   Updated: 2021/02/26 17:29:36 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <libft.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <pthread.h>
# include <unistd.h>

typedef struct			s_keys {
	char				*k_left;
	char				*k_right;
	char				*k_up;
	char				*k_down;
}						t_keys;

typedef struct			s_ctx {
	struct termios		base_termios;
	char				*term;
	int					co;
	int					li;
	t_keys				keys;
}						t_ctx;

extern t_ctx			g_context;
extern pthread_mutex_t	g_mutex;

void	print_error_and_exit(char *error);
void	get_term_size(void);
void	init_signals(void);

#endif
