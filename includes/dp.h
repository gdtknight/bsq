/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:22:19 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/28 20:17:00 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DP_H
# define DP_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "utils.h"

int	initialize_dp(int map_info_fd, int ***dp, int *max_col, char *symbol);
int	update_dp(int ***dp, int **result, int row, int max_col);
int	insert_dp(int map_info_fd, int ***dp, int max_col, char *symbol);
#endif
