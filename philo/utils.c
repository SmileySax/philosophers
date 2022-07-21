/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:55:17 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 11:18:34 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_check_info(int *info, int flag)
{
	int	i;

	if (flag)
	{
		printf("err: ./philo n_phs t_die t_eat t_sleep [n_times_eat]\n");
		printf("err: integer n_phs >= 0\n");
		printf("err: integer t_die >= 0\n");
		printf("err: integer t_eat >= 0\n");
		printf("err: integer t_sleep >= 0\n");
		printf("err: integer n_times_eat >= 0\n");
		return (0);
	}
	i = 0;
	while (i++ < 4)
		if (info[i - 1] < 0)
			return (ft_check_info(info, 1));
	return (1);
}

int	**ft_fill_info(char **argv, int **info)
{
	int	i;

	(*info) = (int *)malloc(5 * sizeof(int));
	if (!*info)
		return (NULL);
	i = 0;
	while (argv[++i])
	{
		(*info)[i - 1] = ft_atoi(argv[i]);
		if (i == 5 && (*info)[i - 1] == 0)
		{
			ft_usleep(100);
			free(*info);
			return (NULL);
		}
	}
	if (i == 5)
		(*info)[4] = 0;
	if (!ft_check_info(*info, 0))
	{
		free(*info);
		return (NULL);
	}
	return (info);
}
