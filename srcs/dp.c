/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:45:51 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/28 20:25:37 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dp.h"

int	initialize_dp(int map_info_fd, int ***dp, int *max_col, char *symbol)
{
	int		temp_fd;
	char	buf[1];
	int		idx;

	*max_col = 0;
	temp_fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	while(read(map_info_fd, buf, 1) > 0 && buf[0] != '\n')
	{
		if (buf[0] != symbol[0] && buf[0] != symbol[1])
		{
			close(temp_fd);
			return (0);
		}
		write(temp_fd, buf, 1);
		(*max_col)++;
	}
	close(temp_fd);
	(*dp) = (int **) malloc (sizeof(int *) * 2);
	if (dp == NULL)
		return (0);
	(*dp)[0] = (int *) malloc (sizeof(int) * (*max_col));
	if ((*dp)[0] == NULL)
	{
		free(dp);
		return (0);
	}
	(*dp)[1] = (int *) malloc (sizeof(int) * (*max_col));
	if ((*dp)[1] == NULL)
	{
		free((*dp)[0]);
		free(*dp);
		return (0);
	}
	temp_fd = open("tmp", O_RDONLY);
	idx = 0;
	while (read(temp_fd, buf, 1) > 0)
	{
		(*dp)[0][idx] = 0;
		if (buf[0] == symbol[0])
			(*dp)[1][idx] = 1;
		else if (buf[0] == symbol[1])
			(*dp)[1][idx] = 0;
		idx++;
	}
	close(temp_fd);
	return (1);
}

/*
 * row : 현재 탐색 중인 행번호
 *
 * result[0] : 최대값이 나타나는 행번호 (y 좌표)
 * result[1] : 최대값이 나타나는 열번호 (x 좌표)
 * result[2] : 최대크기
 */
int	update_dp(int ***dp, int **result, int row, int max_col)
{
	int	c;

	// 현재 행과 관련된 dp 배열 업데이트
	c = 0;
	while (++c < max_col)
	{
		if ((*dp)[1][c] != 0)
			(*dp)[1][c] = min((*dp)[0][c], (*dp)[1][c - 1], (*dp)[0][c - 1]) + 1;
		if ((*dp)[1][c] > (*result)[2])
		{
			(*result)[0] = row;
			(*result)[1] = c;
			(*result)[2] = (*dp)[1][c];
		}
	}

	// 다음 행 탐색을 위해 현재 dp 배열 정보를 한 행 위로 올림.
	c = -1;
	while (++c < max_col)
	{
		(*dp)[0][c] = (*dp)[1][c];
		(*dp)[1][c] = 0;
	}
	return (1);
}

int	insert_dp(int map_info_fd, int ***dp, int max_col, char *symbol)
{
	char	buf[1];
	int		c;

	// 현재 행과 관련된 dp 배열 업데이트
	c = -1;
	while (++c < max_col)
	{
		if (read(map_info_fd, buf, 1) <= 0
			|| (buf[0] != symbol[0] && buf[0] != symbol[1]))
			return (0);
		(*dp)[1][c] = buf[0];
	}
	return (1);
}
