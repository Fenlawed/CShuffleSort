#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

/*
This is just a small side project to run shuffle sort and display how many attempts it takes prior to getting a solved array.
Note that when the user inputs values into the array, if the user puts in a invalid value, the program will crash.
Any array greater than size 10 will take substantial time to solve. Run higher numbers at your own risk (or entertainment)
*/


int sort(int array[], int n)//Checks if the array of size n is sorted
{
	int i;
	int z;//Pretty much just a bool on if it is done or not
	z = 1;
	for (i = 0; i < (n-1); i++)//Go through the array
	{
		if (array[i] > array[i + 1])//If the array isn't sorted
		{
			z = 0;
			return z;//Return 0 AKA false
		}
	}
	return z;//Since it didn't cancel earlier, return 1 AKA true
}


int* shuffle(int array[], int n)//Shuffle function that returns an int* AKA array back to the user. Takes in an array and the size of the array (n)
{
	int i;
	for (i = 0; i < n; i++)//Go through the array
	{
		int r = rand() % (n);//Get two random indexes
		int z = rand() % (n);
		int hold;
		hold = array[r];//Flip the two indexes
		array[r] = array[z];
		array[z] = hold;
	}
	return array;//Return the array
}

int * shuffleSort(int array[], int n)//ShuffleSort function that takes an array and size n and returns the sorted array
{
	int colorSwitch = rand() % 7;//This is so we can print in fun colors
	int i;//This keeps track of number of tries
	i = 1;
	while (sort(array, n) != 1)//While it isn't sorted
	{
		if(i % 100000 == 0)//Switch color every 100000 entries
		{
			colorSwitch = rand() % 7;
		}
		shuffle(array, n);//Shuffle the array
		switch (colorSwitch)//Switch color and print the attempt we are on
		{
			case 0 :
				printf("\033[0;31m");
				printf("Try number %d\n", i);
				break;
			case 1 :
				printf("\033[0;32m");
				printf("Try number %d\n", i);
				break;
			case 2 :
				printf("\033[0;33m");
				printf("Try number %d\n", i);
				break;
			case 3 :
				printf("\033[0;34m");
				printf("Try number %d\n", i);
				break;
			case 4 :
				printf("\033[0;35m");
				printf("Try number %d\n", i);
				break;
			case 5 :
				printf("\033[0;36m");
				printf("Try number %d\n", i);
				break;
			case 6 :
				printf("\033[0;37m");
				printf("Try number %d\n", i);
				break;
			default:
				printf("IT BROKE\n");
		}
		i++;//Increment the count
		wait(0);//Wait so it doesn't strain the CPU as bad (since it will run for a while)
	}
	printf("\033[0;37m");//Switch back to white for printing
	return array;
}


int main(void)
{
	srand(time(NULL));//Set the random
	int* array;//Make an array
	int total;//Total size of array
	printf("How big is your array?\n");
	scanf("%d", &total);//Prompt the user then take in the total
	array = malloc(sizeof(int*) * total);//Allocate the array to the users size
	if (array != NULL)//If the array allocated
	{
		for (int i = 0; i < total; i++)//Let the user input the values
		{
			printf("Array index %d is : ", i);
			scanf("%d",array+i);
		}
		//array = shuffle(array, total); //Uncomment if you want the array to shuffle after user input
		/* here, do your time-consuming job */
		shuffleSort(array, total);//run shuffle sort
		printf("The array sorted is \n");
		for (int i = 0; i < total; i++)//Print the sorted array
		{
			printf("%d element is %d\n", i, array[i]);
		}
		free(array);//Free the malloc
	}
	else
	{
		printf("Failed to allocate the array\n");
	}
}
