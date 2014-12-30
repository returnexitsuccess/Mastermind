#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TRIALS 100000

void display(int guess, char* table, int* response);
int increment(int currentGuess, int numGuesses, int* guesses, int* response, char* table);
int verify(int answer, int guess, int* reply, char* table);
void convertGuess(int guess, char* g, char* table);
void scramble(char* table);
void swap(char* color);
void getPegs(int guess, char* answer, char* table, int* response);
int oldgame(char* answer);

int main()
{
	srand(time(NULL));
	
	int a;
	char colors[6] = {'W', 'G', 'R', 'P', 'O', 'B'};
	char code[4];
	int *guesses = malloc(10 * sizeof(int));
	
	int i = 0;
	while (i < 10)
	{
		guesses[i] = 0;
		i++;
	}
	
	i = 0;
	while (i < TRIALS)
	{
		int j = 0;
		while (j < 4)
		{
			code[j] = colors[rand() % 6];
			j++;
		}
		a = oldgame(code);
		guesses[a]++;
		
		//printf("%d\n", i);
		i++;
	}
	
	int k = 0;
	while (k < 10)
	{
		printf("%2d: %5.2f\n", k + 1, (100.0 * guesses[k]) / TRIALS);
		
		k++;
	}
	
	/*
	char b[4] = "WWWW";
	int a = oldgame(b);
	printf("%d\n", a);
	*/
	
	return 0;
}

int oldgame(char* answer)
{
	
	int guesses[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int response[10][2] = { {0, 0},
	                        {0, 0},
	                        {0, 0},
	                        {0, 0},
	                        {0, 0},
	                        {0, 0},
	                        {0, 0},
	                        {0, 0},
	                        {0, 0},
	                        {0, 0} };
	char table[4][6] = { {'W', 'G', 'R', 'P', 'O', 'B'},
	                     {'W', 'G', 'R', 'P', 'O', 'B'},
	                     {'W', 'G', 'R', 'P', 'O', 'B'},
	                     {'W', 'G', 'R', 'P', 'O', 'B'} };
	
	scramble(table);
	/*
	int r = 0;
	int c = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 6)
		{
			printf("%c, ", table[r][c]);
			c++;
		}
		printf("\n");
		r++;
	}
	*/
	
	int currentGuess = 0;
	int numGuesses = 0;
	while (currentGuess < 6 * 6 * 6 * 6 && numGuesses <= 10)
	{
		//display(currentGuess, &table, &(response[numGuesses][0]));
		getPegs(currentGuess, answer, &table, &(response[numGuesses][0]));
		//printf("%d, %d\n", response[numGuesses][0], response[numGuesses][1]);
		guesses[numGuesses] = currentGuess;
		numGuesses++;
		
		if (response[numGuesses - 1][0] == 4)
		{
			//printf("\n\nI WIN!!!\nIt took %d guesses to break your code.\n", numGuesses);
			return numGuesses;
			break;
		}
		
		currentGuess = increment(currentGuess, numGuesses, guesses, response, table);
		if (currentGuess >= 6 * 6 * 6 * 6)
		{
			printf("No solution found! %d\n", currentGuess);
			//currentGuess %= 6 * 6 * 6 * 6;
			//currentGuess = increment(currentGuess, numGuesses, guesses, response);
			break;
		}
		
	}
	printf("PROBLEM");
}

void display(int guess, char* table, int* response)
{
	char disp[4];
	int i = 0;
	while (i < 4)
	{
		disp[i] = *(table + 6 * i + (guess % 6));
		guess /= 6;
		i++;
	}
	printf("\n%s\n", disp);
	printf("How many red (or black) pegs?\n");
	scanf("%d", response);
	printf("How many white pegs?\n");
	scanf("%d", response + 1);
}

int increment(int currentGuess, int numGuesses, int* guesses, int* response, char* table)
{
	currentGuess++;
	while (currentGuess < 6 * 6 * 6 * 6)
	{
		int i = 0;
		while (i < numGuesses)
		{
			if (!verify(currentGuess, guesses[i], response + 2 * i, table))
			{
				break;
			}
			i++;
		}
		if (i == numGuesses)
		{
			return currentGuess;
		}
		currentGuess++;
	}
	//printf("overflow\n");
	return currentGuess;
}

int verify(int answer, int guess, int* reply, char* table)
{
	int red = 0;
	int white = 0;
	char ans[4];
	char g[4];
	
	
	
	convertGuess(answer, ans, table);
	convertGuess(guess, g, table);
	
	int i = 0;
	while (i < 4)
	{
		if (ans[i] == g[i])
		{
			red++;
			ans[i] = ' ';
			g[i] = ' ';
		}
		i++;
	}
	
	if (red != reply[0])
	{
		return false;
	}
	
	int j;
	i = 0;
	while (i < 4)
	{
		if (ans[i] != ' ')
		{
			j = 0;
			while (j < 4)
			{
				if (ans[i] == g[j])
				{
					white++;
					ans[i] = ' ';
					g[j] = ' ';
					break;
				}
				j++;
			}
		}
		i++;
	}
	
	if (white != reply[1])
	{
		return false;
	}
	
	return true;
}

void convertGuess(int guess, char* g, char* table)
{
	int i = 0;
	while (i < 4)
	{
		g[i] = *(table + 6 * i + (guess % 6));
		guess /= 6;
		i++;
	}
}

void scramble(char* table)
{
	int r;
	
	int i = 0;
	while ((i / 100) < 4)
	{
		r = rand() % 5;
		swap(table + 6 * (i / 100) + r);
		i++;
	}
}

void swap(char* color)
{
	char temp;
	temp = *color;
	*color = *(color + 1);
	*(color + 1) = temp;
}

void getPegs(int guess, char* answer, char* table, int* response)
{
	int red = 0;
	int white = 0;
	char g[4];
	char ans[4] = {answer[0], answer[1], answer[2], answer[3]};
	
	
	convertGuess(guess, g, table);
	
	//printf("%s\n", g);
	
	int i = 0;
	while (i < 4)
	{
		if (ans[i] == g[i])
		{
			red++;
			ans[i] = ' ';
			g[i] = ' ';
		}
		i++;
	}
	
	int j;
	i = 0;
	while (i < 4)
	{
		if (ans[i] != ' ')
		{
			j = 0;
			while (j < 4)
			{
				if (ans[i] == g[j])
				{
					white++;
					ans[i] = ' ';
					g[j] = ' ';
					break;
				}
				j++;
			}
		}
		i++;
	}
	
	//printf("%d, %d\n", red, white);
	*response = red;
	*(response + 1) = white;
}