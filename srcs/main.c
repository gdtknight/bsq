/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:30:53 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/28 23:25:46 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(int argc, char **argv)
{
	int	idx;

	if (argc < 2)
		return (0);
	idx = 0;
	while (++idx < argc)
	{
		if (!processing(argv[idx]))
			write(1, "map error\n", 10);
	}
	exit(0);
}
