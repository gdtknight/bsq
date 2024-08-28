/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:02:01 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/27 20:40:18 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c) {
    int temp = a < b ? a : b;
    return temp < c ? temp : c;
}

int maximalSquare(int** grid, int gridSize, int* gridColSize) {
    if (gridSize == 0 || gridColSize[0] == 0) {
        return 0;
    }
    
    int n = gridSize;
    int m = gridColSize[0];
    int maxSide = 0;

    // 동적 배열 할당
    int** dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)malloc(m * sizeof(int));
    }

    // DP 배열 초기화 및 채우기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
                }
                if (dp[i][j] > maxSide) {
                    maxSide = dp[i][j];
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // 메모리 해제
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    // 정사각형의 넓이 반환
    return maxSide * maxSide;
}
/*
int main() {
	int	**grid;
	int	N;
	int	M;
	int	row;
	int	col;

	N = 4;
	M = 4;

	grid = (int **) malloc(sizeof(int *) * N);
	if (grid == NULL)
		return (0);
	row = -1;
	while (++row < N)
	{
		grid[row] = (int *) malloc (sizeof(int) * M);
		if (grid[row] == NULL)
		{
			finalize((void **)grid, row);
			return (0);
		}
	}

	grid[0][0] = 1;
	grid[0][1] = 0;
	grid[0][2] = 1;
	grid[0][3] = 1;

	grid[1][0] = 1;
	grid[1][1] = 1;
	grid[1][2] = 1;
	grid[1][3] = 1;

	grid[2][0] = 0;
	grid[2][1] = 1;
	grid[2][2] = 1;
	grid[2][3] = 1;

	grid[3][0] = 1;
	grid[3][1] = 1;
	grid[3][2] = 1;
	grid[3][3] = 0;
    
    int *result = maximalSquare(grid, N, M);
    printf("가장 큰 정사각형 우측 하단 위치 : [%d, %d]\n", result[0], result[1]);

	row = -1;
	while (++row < N)
	{
		col = -1;
		while (++col < M)
		{
			printf("%d", grid[row][col]);
			if (col != M - 1)
				printf(" ");
		}
		printf("\n");
	}

	printf_result_map(grid, N, M, result);

	free(result);
    return (0);
}
*/
