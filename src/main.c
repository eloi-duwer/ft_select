/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:37:21 by eduwer            #+#    #+#             */
/*   Updated: 2021/02/26 17:50:36 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

t_ctx			g_context;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void		print_error_and_exit(char *error)
{
	ft_fdprintf(2, "%s\n", error);
	exit(1);
}

void	get_term_size(void)
{
	pthread_mutex_lock(&g_mutex);	
	if (g_context.term != NULL)
		tgetent(NULL, g_context.term);
	else
		tgetent(NULL, "linux");
	g_context.li = tgetnum("li");
	g_context.co = tgetnum("co");
	ft_printf("Term size %d li %d co\n", g_context.li, g_context.co);
	pthread_mutex_unlock(&g_mutex);
}

static void	init_term(void)
{
	struct termios	new_term;
	int				ret;

	pthread_mutex_lock(&g_mutex);
	if (tcgetattr(0, &g_context.base_termios) == -1)
		print_error_and_exit("Error on tcgetattr");
	ft_memcpy(&new_term, &g_context.base_termios, sizeof(struct termios));
	new_term.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, TCSAFLUSH, &new_term) == -1)
		print_error_and_exit("Error on tcsetattr");
	g_context.term = getenv("TERM");
	if (g_context.term != NULL)
		ret = tgetent(NULL, g_context.term);
	else
		ret = tgetent(NULL, "linux");
	if (ret != 1)
		print_error_and_exit("Your terminal does not seems to support \
termcaps (is your TERM env variable set?)\n");
	g_context.keys.k_left = tgetstr("kl", NULL);
	g_context.keys.k_right = tgetstr("kr", NULL);
	g_context.keys.k_up = tgetstr("ku", NULL);
	g_context.keys.k_down = tgetstr("kd", NULL);
	pthread_mutex_unlock(&g_mutex);	
}

static void	start_loop(void)
{
	char	buff[64];
	ssize_t	size;

	int i = 0;
	while (i < (int)ft_strlen(g_context.keys.k_left)) {
		ft_printf("%d ", (int)g_context.keys.k_left[i]);
		i++;
	}
	ft_printf("\n");
	while (true)
	{
		ft_bzero(buff, 64);
		size = read(1, buff, 64);
		i = 0;
		ft_printf("New line: ");
		while (i < size) {
			ft_printf("%d ", buff[i]);
			i++;
		}
		ft_printf("\n");
		if (ft_strncmp(buff, g_context.keys.k_left, ft_strlen(g_context.keys.k_left) == 0))
			ft_printf("KEY LEFT\n");
		
	}
}

int			main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	init_term();
	init_signals();
	get_term_size();
	start_loop();
	return (0);
}
