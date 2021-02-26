/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:34:41 by eduwer            #+#    #+#             */
/*   Updated: 2021/02/26 16:22:11 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	term_size_change(int sig)
{
	(void)sig;
	get_term_size();
}

static void quit_prog(int sig)
{
	(void)sig;
	tputs(tgetstr("me", NULL), 1, &ft_legacy_putchar);
	tcsetattr(0, TCSAFLUSH, &g_context.base_termios);
	exit(0);
}

void		init_signals(void)
{
	if (signal(SIGWINCH, &term_size_change) == SIG_ERR
		|| signal(SIGINT, &quit_prog) == SIG_ERR
		|| signal(SIGTERM, &quit_prog) == SIG_ERR)
		print_error_and_exit("Error while registering signal hander\n");
}
