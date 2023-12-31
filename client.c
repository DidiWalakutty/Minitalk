/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 15:48:12 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/17 22:15:02 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_receiver = 0;

// pause() so sig_handler() can send a 
// kill() confirmation on receiving
// the signal. usleep() so both can catch up.
static void	send_character(char c, int pid)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		c >>= 1;
		shift++;
	}
	usleep(200);
}

// Send every char seperately.
// Lastly, send '\0' so server knows it's the
// end of the string. kill() so handle_done
// knows it can print the message.
static void	send_string(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_character(str[i++], pid);
	}
	send_character('\0', pid);
	kill(pid, SIGUSR1);
}

static void	delivered(int sig)
{
	if (sig == g_receiver)
		g_receiver = 1;
	else
		g_receiver = 0;
}

// Check if given PID is the same
// as the one running on ./server.
// Set signal registration 'delivered' to
// make sure every signal is received.
int	main(int argc, char **argv)
{
	pid_t	pid;

	pid = ft_atoi(argv[1]);
	if (argc != 3)
		exit_error("Client: Wrong amount of arguments");
	else if (kill(pid, 0) < 0)
		exit_error("Client: given PID is not valid");
	signal(SIGUSR1, delivered);
	signal(SIGUSR2, delivered);
	send_string(argv[2], pid);
	ft_printf("Message delivered.\n");
	return (0);
}
