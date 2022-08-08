/*********************
* Topaz Avraham
* 206842627
* ex_3
*********************/

#include <stdio.h>

void printPrimes();
int isPrime(int numToCheck);
void goldbach(int size);
int reverseNum(int num);
void printLychrel(int num);
int isSymetric(int num);
void readArray(int arr[], int numOfElements);
int countMaxSetNumber(int arr[], int arr2[], int size, int maxForNow);


void main() {
	//variables declarations
	int size = SIZE;
	int digit, numOfElements, count;
	int arr1[SIZE], arr2[SIZE];

	printf("1: primes\n2: goldbach\n3: lychrel\n4: max set\n");
	scanf("%d", &digit);

	switch (digit) {
	case 1:
		printPrimes();
		break;

	case 2:

		/*
		we send all even numbers until size*2 to function
		2 * size = the max value that can be represented as the addition of 2 nums with "size" value
		*/
		for (int i = 2; i < 2 * size; i += 2) {
			goldbach(i);
		}
		break;

	case 3:
		printLychrel(LIMIT - 1);
		break;

	case 4:
		printf("Enter the number of elements\n");
		scanf("%d", &numOfElements);
		readArray(arr1, numOfElements);
		count = countMaxSetNumber(arr1, arr2, numOfElements, 1);
		printf("%d\n", count);
		break;

	default:
		printf("Wrong option!");
	}
}

/***********************************************************************************
* Function Name: printPrimes
* Input: nothing
* Output: nothing
* Function Operation: the function prints all prime numbers until SIZE.
*					  the first print for prime number 2 is separately because we don't need space before
***********************************************************************************/
void printPrimes()
{
	for (int i = 2; i < SIZE; i++) {
		for (int j = 2; j <= i; j++) {
			if (i == 2) {
				printf("%d", i);
			}
			if (j == i && i > 2) {
				printf(" %d", i);
			}
			else if (i % j == 0) {
				break;
			}
		}
	}
	printf("\n");
}

/***********************************************************************************
* Function Name: goldbach
* Input: int size (positive number with even value)
* Output: nothing
* Function Operation: the function prints all the combinations of size as the addition of 2 prime numbers
*		              the functions takes one even number at a time
***********************************************************************************/
void goldbach(int size) {
	/*
	for (int i = 2; i < SIZE; i++) {
		for (int j = i; j < SIZE; j++) {
			if ((isPrime(i) && isPrime(j)) && ((i+j)%2==0))
			{
				printf("%d = %d + %d\n", i + j, i, j);
			}
		}
	}
	*/

	//starting from 2 until size-2 which is the max value of a prime num to be part of an addition
	for (int i = 2, j = size - 2; j >= i; j--, i++) {
		//making sure that the 2 nums of the addition are prime, and also that their value is not exceeding SIZE
		if ((isPrime(i) && isPrime(j)) && j < SIZE)
		{
			printf("%d = %d + %d\n", size, i, j);
		}
	}
}

/***********************************************************************************
* Function Name: isPrime
* Input: int numToCheck (positive number)
* Output: 1 (true) if the number is prime, 0 (false) otherwise
* Function Operation: the function tests whether a given number is prime
***********************************************************************************/
int isPrime(int numToCheck) {
	for (int i = 2; i <= numToCheck; i++) {

		//if we reached the end of loop and there wasn't a divisor, so it is prime
		if (i == numToCheck)
			return 1;

		//if the number divides in one of the numbers smaller than him, it is not prime
		else if ((numToCheck % i) == 0)
			return 0;
	}
	return 0;
}

/***********************************************************************************
* Function Name: printLychrel
* Input: int num (positive number)
* Output: nothing
* Function Operation: a recursive function- we assume all numbers before num are Lychrel and check the last num
*					  "the smallest problem" - when num equals 0 and then we do nothing, it's the end
***********************************************************************************/
void printLychrel(int num) {

	//smallest problem
	if (num == 0) {
		return;
	}

	//recursive call
	printLychrel(num - 1);

	//linking to last num
	int reverse, result = num;

	//first we print num
	printf("%d", num);

	//then as long as the num is not Palindrom we reverse it and print the addition
	while (!isSymetric(result)) {
		reverse = reverseNum(result);
		printf(":%d+%d=%d", result, reverse, result + reverse);
		result = result + reverse;
	}
	printf("\n");
}

/***********************************************************************************
* Function Name: reverseNum
* Input: int num (positive number)
* Output: int reverse (the reversed version of num - also positive)
* Function Operation: the function creates a new number and digit by digit assign the reversed value of num
***********************************************************************************/
int reverseNum(int num) {
	int reverse = 0;
	while (num != 0) {
		reverse *= 10;
		reverse += num % 10;
		num /= 10;
	}
	return reverse;
}

/***********************************************************************************
* Function Name: isSymetric
* Input: int num (positive number)
* Output: 1 (true) if the number is symetric (Palindrom), 0 (false) otherwise
* Function Operation: the function gets the reverse num using other function, and compare it with the original num
***********************************************************************************/
int isSymetric(int num) {

	//assign the reversed version of num
	int reversedNum = reverseNum(num);

	//compare the reversed num to original num, if the same they are Palindrom
	if (reversedNum == num) {
		return 1;
	}

	//if the reversed is not identical to the original,  it's not a Palindrom
	else if (reversedNum != num) {
		return 0;
	}
	return 0;
}

/***********************************************************************************
* Function Name: readArray
* Input: int arr[] (array of numbers), int size (the number of elements in the array)
* Output: nothing
* Function Operation: the function reads from the user elements and assign them to array
***********************************************************************************/
void readArray(int arr[], int numOfElements) {
	for (int i = 0; i < numOfElements; i++) {
		scanf("%d", &arr[i]);
	}
}

/***********************************************************************************
* Function Name: countMaxSetNumber
* Input: int arr1[], int arr2[] (array of numbers), int size (the number of elements in the arrays)
*		 int maxForNow (the biggest subset we were able to create for now)
* Output: int maxForNow (the biggest subset we were able to create after going through all elements
* Function Operation: the function uses a different array (arr2) to count the longest increasing subset in arr1
***********************************************************************************/
int countMaxSetNumber(int arr1[], int arr2[], int size, int maxForNow) {

	/*
	first we assume the basis to build on, that the sequence is monotonically decreasing.
	meaning there are no elements which are bigger that the ones before them,
	therefore the biggest subset in arr1 is 1
	*/
	for (int i = 0; i < size; i++) {
		arr2[i] = 1;
	}

	//going through all elements except hte first one (isn't necessary)
	for (int i = 1; i < size; i++) {
		// for each element check the biggest subset until his index.
		for (int j = 0; j < i; j++) {

			//test if this element is bigger than one of his predecessors and also test if this 
			//element is a part of an existing increasing subset and not a new subset
			if ((arr1[i] > arr1[j]) && arr2[i] < arr2[j] + 1) {

				//if so, we increase the max set number by 1
				arr2[i] = arr2[j] + 1;

				//if this is the biggest subset by now, we assign the length to maxForNow
				if (maxForNow < arr2[i]) {
					maxForNow = arr2[i];
				}
			}
		}
	}
	//finally, we return the number of elements which combined are the longest increasing subset 
	return maxForNow;
}
