/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:33:47 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 22:22:51 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_philo(t_pinfo pinfo, int i)
{
	pthread_t	monitor;

	pinfo.ph_nbr = i + 1;
	if (pthread_create(&monitor, NULL, monitoring, (void *)(&pinfo)) != 0)
		exit(1);
	gettimeofday(&(pinfo.start_time), 0);
	gettimeofday(&(pinfo.last_meal), 0);
	while (1)
	{
		ft_eat(&pinfo);
		if (ft_sleep_n_think(&pinfo))
			break ;
	}
	if (pthread_join(monitor, NULL) != 0)
		exit(0);
	exit(0);
	return (0);
}

void	ft_lets_eat(t_pinfo pinfo)
{
	int				i;

	i = -1;
	while (++i < pinfo.info[0])
	{
		(pinfo.pid)[i] = fork();
		if ((pinfo.pid)[i] == 0)
			exit(ft_philo(pinfo, i));
		if ((pinfo.pid)[i] < 0)
		{
			while (i >= 0)
				kill((pinfo.pid)[--i], SIGKILL);
			write(2, "Fork error\n", 12);
			exit(1);
		}
	}
	ft_kill_n_finish(&pinfo, i);
}

int	main(int argc, char **argv)
{
	t_pinfo	pinfo;

	if (argc < 5 || argc > 6)
	{
		printf("err: ./philo n_phs t_die t_eat t_sleep [n_times_eat]");
		ft_usleep(100);
		return (1);
	}
	pinfo = ft_init_values(&pinfo, argv);
	if (!pinfo.info)
		return (1);
	ft_lets_eat(pinfo);
	return (0);
}
