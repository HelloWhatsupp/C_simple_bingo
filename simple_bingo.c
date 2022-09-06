/* simple_bingo.c */
/* doesn't work for 4 or more players!!! */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

enum default_settings { drop_out_numbers = 5, player_count = 3 };

int compare_str(char *str1, char *str2) {
	for (; *str1 || *str2; str1++, str2++) {
		if (*str1 != *str2)
			return 0;
	}
	return 1;
}

int arr_contains_str(char **arr, char *str) {
	while (*arr != NULL) {
		if (compare_str(*arr, str)) {
			return 1;
		}
		arr++;
	}

	return 0;
}
int arr_is_fully_equal(int arr_len, int *arr, int num) {
	int i;
	for (i = 0; i < arr_len; i++) {
		if (arr[i] != num)
			return 0;
	}
	return 1;
}
int main(int argc, char **argv) {
	int i, players, numbers_count, min, max;
	int **player_results;
	long long game_tries = 0;
	long long start_time;

	if (arr_contains_str(argv, "-d")) {
		players = player_count;
		numbers_count = drop_out_numbers;
	} else {
		printf("How many players will play?\n");
		scanf("%d", &players);

		printf("How many numbers will drop out?\n");
		scanf("%d", &numbers_count);
	}

	printf("What min and max diap of numbers?\n");
	scanf("%d %d", &min, &max);
	
	printf("\x1B[1J");
	printf("\x1B[1;1H");
	player_results = malloc(sizeof(int) * players);
	for (i = 0; i < players; i++) {
		player_results[i] = malloc(sizeof(int) * numbers_count);
		printf("player%d\t", i + 1);
	}
	printf("\n");

	start_time = time(NULL);
	srand(start_time);

	while (1) {
		int j;
		int winner = 0;

		printf("\x1B[2;1H");
		printf("\x1B[0J");

		game_tries++;

		for (i = 1, j = 0; i <= numbers_count * players; i++) {
			int dropped_num = rand() % (max - min + 1) + min;

			printf("%d\t", dropped_num);
			player_results[(i - 1) % players][j] = dropped_num;
			if (i % players == 0) {
				j++;
				printf("\n");
			}
		}
		for (i = 0; i < players; i++) {
			if (arr_is_fully_equal(numbers_count, player_results[i], *player_results[i])) {
			       winner = i + 1;
			}
		}
		if (winner) {
			printf("player%d is a winner!\n", winner);
			break;
		}

	}
	printf("\x1B[?25h");

	printf("%lld attempts was made to find a winner\n", game_tries);
	printf("Time required for complete the task: %lld seconds\n", time(NULL) - start_time);
	return 0;
}
