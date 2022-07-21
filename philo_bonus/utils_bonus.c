/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:55:17 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 17:38:20 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_usleep(int delay)
{
	struct timeval	t1;
	struct timeval	t2;
	long long		time;

	gettimeofday(&t1, 0);
	t2 = t1;
	time = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
	while (time < delay)
	{
		if (delay - time < 15)
		{
			usleep(delay - time);
			return (0);
		}
		else if (delay - time < 100)
			usleep(20);
		else
			usleep(100);
		gettimeofday(&t2, 0);
		time = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sig;
	long int	res;

	i = 0;
	res = 0;
	sig = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + sig * (str[i++] - '0');
	if (str[i])
		return (-1);
	if ((int)res == res)
		return ((int)res);
	else if (sig == -1)
		return (0);
	else
		return (-1);
}
