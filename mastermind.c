#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void display(int guess, char* table, int* response);
int increment(int currentGuess, int numGuesses, int* guesses, int* response, char* table);
int verify(int answer, int guess, int* reply, char* table);
void convertGuess(int guess, char* g, char* table);
void scramble(char* table);
void swap(char* color);

int main()
{
	srand(time(NULL));
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
		display(currentGuess, &table, &(response[numGuesses][0]));
		//printf("%d\n", response[numGuesses][0]);
		guesses[numGuesses] = currentGuess;
		numGuesses++;
		
		if (response[numGuesses - 1][0] == 4)
		{
			printf("\n\nI WIN!!!\nIt took %d guesses to break your code.\n", numGuesses);
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
	
	return 0;
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