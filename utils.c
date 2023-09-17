/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 15:55:54 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/09/17 22:12:39 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
		exit_error("Couldn't set up SIGUSR1");
	if (sigaction(SIGUSR2, sa, NULL) < 0)
		exit_error("Couldn't set up SIGUSR2");
}