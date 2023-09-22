/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 15:48:12 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/22 20:20:35 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_receiver = 0;

// SIGUSR1 = 1
// SIGUSR2 = 0
// C &(1 << shift): shift left operator: moves the bits to the left, 
// and discards the far left bit.
// usleep: delay without relying on a signal.
static void	send_character(char c, int pid)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if (c & 1 )
		{
			kill(pid, SIGUSR1);
			g_receiver = SIGUSR1;
		}
		else
		{
			kill(pid, SIGUSR2);
			g_receiver = SIGUSR2;
		}
		pause();
		c >>= 1;
		shift++;
		usleep(100);
	}
}

static void	send_string(char *str, int pid)
{
	int	i;

	i = 0;
	while(str[i])
	{
		send_character(str[i++], pid);
	}
	send_character('\0', pid);
	if (g_receiver == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
}

// Client sends the character to the server.
// Kill notifies server that a signal was send.
static void	delivered(int sig)
{

	if (sig == g_receiver)
	{
		g_receiver = 1;
		ft_printf("signal received\n");
	}
	else
		g_receiver = 0;
}

int	main(int argc, char **argv)
{
	int		byte_i;
	pid_t	pid;

	if (argc != 3)
		exit_error("Client: Wrong amount of arguments");
	else if (kill(ft_atoi(argv[1]), 0) < 0)
		exit_error("Client: given PID is not valid");
	pid = ft_atoi(argv[1]);
	byte_i = 0;
	signal(SIGUSR1, delivered);
	signal(SIGUSR2, delivered);
	send_string(argv[2], pid);
	ft_printf("Message delivered.\n");
	return (0);
}
