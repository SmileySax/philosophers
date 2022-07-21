/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpart_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:37:17 by keaton            #+#    #+#             */
/*   Updated: 2022/07/22 00:15:06 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_deccount(long int n)
{
	int		count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

void	ft_writenum(int n, char *num, int len)
{
	num[len--] = n % 10 + '0';
	if (n >= 10)
		ft_writenum (n / 10, num, len);
}

void	ft_itoa(unsigned int n, char *num)
{
	int		len;

	len = ft_deccount(n);
	num[len + 2] = '\0';
	num[0] = 'm';
	num[1] = 't';
	ft_writenum(n, num, len + 1);
}
