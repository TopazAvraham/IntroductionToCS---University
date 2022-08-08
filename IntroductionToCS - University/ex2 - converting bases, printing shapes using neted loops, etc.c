/*********************
* Topaz Avraham
* 206842627
* ex_2
*********************/

#include <stdio.h>
#include <math.h>

unsigned long convertToDecimal(int base, unsigned long num);
unsigned long long convertDecimalToAnyBase(int base, unsigned long num);
int maxDigit(unsigned long num);
int isBinary(unsigned long num1);
int digit1BinaryCounter(unsigned long num);
void addingBinaryProcess(unsigned long binNum1, unsigned long binNum2);
int countDigit(unsigned long long num);
int maxCount(int num1, int num2, int num3);
int valueOfHexaDigit(char hexaDigit);
void printButterfly(unsigned int n);

void main() {

	// variables declarations for all tasks
	int base, counter, isValid, fContinue, digit, location, digitValue;
	unsigned long num, result, binNum1, binNum2;
	unsigned long long res;
	long double decimalResult;
	unsigned int n;
	char hexaDigit;
	const char LINE_FEED = 10;

	do {
		printf("Choose an option:\n	1. hexaDecimal to Decimal\n	2. Decimal to Base\n	"
			"3. Base to Decimal\n	4. PLUS\n	5. Shape\n	6. Count bits\n	7. Exit\n");

		scanf("%d", &digit);

		switch (digit) {

		case 1:
			printf("Enter a reversed number in base 16:\n");
			scanf(" %c", &hexaDigit);
			location = 0;
			decimalResult = 0;
			fContinue = 1;

			//as long as the digits are in base 16
			while (fContinue) {

				//if the digit is ENTER, it's the end, we print the result in base 10, and exit the loop
				if (hexaDigit == LINE_FEED) {
					printf("%.0Lf\n", decimalResult);
					break;
				}

				//if the digit is in base 16, we convert it to base 10 using function, add to result, and scan another digit
				else if ((hexaDigit <= '9') && (hexaDigit >= '0') ||
					(hexaDigit <= 'f' && hexaDigit >= 'a') ||
					((hexaDigit <= 'F' && hexaDigit >= 'A'))) {

					digitValue = valueOfHexaDigit(hexaDigit);
					decimalResult += (digitValue * (long double)pow(16, location));
					location++;
					scanf("%c", &hexaDigit);
				}
				//the digit is not in base 16
				else {
					printf("Error!\n");
					fContinue = 0;
					//clean buffer to avoid infinite loop/bugs
					scanf("%*[^\n]");
				}
			}
			break;

		case 2:
			printf("Enter base and a number:\n");
			isValid = scanf("%d%lu", &base, &num);

			//if the user didn't enter 2 numbers 
			if (isValid < 2) {
				printf("Invalid input\n");
				scanf("%*[^\n]");
				break;
			}
			else {
				//convert to any base using function and print result
				res = convertDecimalToAnyBase(base, num);
				printf("%llu\n", res);
			}
			//clean buffer
			scanf("%*[^\n]");
			break;

		case 3:
			printf("Enter base and a number:\n");
			isValid = scanf("%d%lu", &base, &num);

			//if the user didn't enter 2 numbers 
			if (isValid < 2) {
				printf("Invalid input\n");
				scanf("%*[^\n]");
				break;
			}
			//if the number has digits that are not in the base
			else if (maxDigit(num) >= base) {
				printf("this number is not in base %d\n", base);
				scanf("%*[^\n]");
				break;
			}
			else {
				//convert to decimal using function and print result
				result = convertToDecimal(base, num);
				printf("%lu\n", result);

				//clean buffer
				scanf("%*[^\n]");
				break;
			}

		case 4:
			printf("Enter 2 binary numbers:\n");
			isValid = scanf("%lu%lu", &binNum1, &binNum2);

			//if the user didn't enter 2 numbers 
			if (isValid < 2) {
				printf("Invalid input\n");
				scanf("%*[^\n]");
				break;
			}

			//if one of the numbers is not in base 2
			else if ((!isBinary(binNum1)) || (!isBinary(binNum2))) {
				printf("Invalid input\n");
				scanf("%*[^\n]");
				break;
			}

			//we send to function the bigger number first
			else {
				if (binNum1 > binNum2) {
					addingBinaryProcess(binNum1, binNum2);
				}
				else {
					addingBinaryProcess(binNum2, binNum1);
				}
			}
			//clean buffer
			scanf("%*[^\n]");
			break;

		case 5:
			printf("Enter a number:\n");
			scanf("%u", &n);
			printButterfly(n);
			break;

		case 6:
			printf("enter a number:\n");
			isValid = scanf("%lu", &num);

			//if the user entered a number 
			if (isValid) {
				counter = digit1BinaryCounter(num);
				printf("no of bits those are 1 in its binary representation: %d\n", counter);
				scanf("%*[^\n]");
			}
			//in case the user didn't enter a number
			else {
				printf("Invalid input\n");
				scanf("%*[^\n]");
			}
			break;

		case 7:
			break;

		default:
			printf("Wrong option!\n");
		}

	} while (digit != 7);
}

/***********************************************************************************
* Function Name: convertToDecimal
* Input: int base (values between 2<= base <=10), unsigned long num (num >=0)
* Output: unsigned long (positive number in base 10)
* Function Operation: the function converts a number from base 2-10 to base 10,
*					  if the number which was sent to function was already in base 10, it returns it automatically
***********************************************************************************/
unsigned long convertToDecimal(int base, unsigned long num) {
	if (base == 10) {
		return num;
	}

	int location = 0;
	unsigned long res = 0;

	while (num > 0) {
		res += (num % 10) * (int)pow(base, location);
		num /= 10;
		location++;
	}

	return res;
}

/***********************************************************************************
* Function Name: convertDecimalToAnyBase
* Input: int base (values between 2< base <9), unsigned long num (num >=0, in base 10)
* Output: unsigned long long (positive number in base 2-9)
* Function Operation: the function converts a number from base 10 to 2-9 base
***********************************************************************************/
unsigned long long convertDecimalToAnyBase(int base, unsigned long num) {
	unsigned long long res = 0;
	int divisionLeft, location = 0;

	while (num != 0) {
		divisionLeft = num % base;
		num /= base;
		res += (divisionLeft * (unsigned long long)pow(10, location));
		location++;
	}
	return res;
}

/***********************************************************************************
* Function Name: isBinary
* Input: unsigned long num (a positive number which may be in binary)
* Output: int (1 if the number is binary, 0 if not)
* Function Operation: the function go over the number's digits and check whether the value is only 0/1.
*					  if there is a digit with value >=2 then function returns false (0)
***********************************************************************************/
int isBinary(unsigned long num) {
	int rightDigit;
	while (num > 0) {
		rightDigit = num % 10;
		if (rightDigit >= 2)
		{
			return 0;
		}
		num /= 10;
	}
	return 1;
}

/***********************************************************************************
* Function Name: addingBinaryProcess
* Input: unsigned long binNum1, unsigned long binNum2  (two positive number in base 2, the first is always bigger)
* Output: a chart that shows the adding process of the numbers
* Function Operation: first the function calculates the carry line, then calculates which number has the most digits
					  then pad the other numbers with 0, and then prints the adding process.
***********************************************************************************/
void addingBinaryProcess(unsigned long binNum1, unsigned long binNum2) {

	//variables declarations
	int count1 = countDigit(binNum1);
	int count2 = countDigit(binNum2);
	unsigned long long carry = 0, tmpCarry = carry, carryTemp, sum = 0,
		temp1 = binNum1, temp2 = binNum2, tmp1 = binNum1, tmp2 = binNum2;
	int i, location = 1, countDigitsCarry;

	//calculating the carry line
	for (i = 0; i < count1; i++) {
		if (((temp1 % 10) + (temp2 % 10) + (tmpCarry)) < 2) {
			temp1 /= 10;
			temp2 /= 10;
			tmpCarry /= 10;
			location++;
		}
		else {
			carry = carry + (int)(1 * pow(10, location));
			temp1 /= 10;
			temp2 /= 10;
			tmpCarry = carry;
			tmpCarry /= (int)pow(10, location);
			location++;
		}

	}

	//calculating the longest number
	countDigitsCarry = countDigit(carry);
	int maxDigits = maxCount(count1, count2, countDigitsCarry);

	//pad with zeros other numbers and print them all + print the pattern of addition
	for (i = 0; i < maxDigits - countDigitsCarry; i++)
		printf("0");
	printf("%llu\n", carry);

	for (i = 0; i < maxDigits - count1; i++)
		printf("0");
	printf("%lu\n+\n", binNum1);

	for (i = 0; i < maxDigits - count2; i++)
		printf("0");
	printf("%lu\n", binNum2);

	for (i = 0; i < maxDigits; i++) {
		printf("-");
	}

	printf("\n");
	carryTemp = carry;

	//calculating the sum 
	for (i = 0, location = 0; i < maxDigits; i++) {
		if (((((tmp1 % 10) + (tmp2 % 10) + (carryTemp % 10)) % 2) == 0)) {
			sum += 0 * (int)(pow(10, location));
			location++;
			tmp1 /= 10;
			tmp2 /= 10;
			carryTemp /= 10;
		}
		else {
			sum += 1 * (int)(pow(10, location));
			location++;
			tmp1 /= 10;
			tmp2 /= 10;
			carryTemp /= 10;
		}
	}

	printf("%llu\n", sum);
}

/***********************************************************************************
* Function Name: countDigit
* Input: unsigned long num (num >= 0)
* Output: int (amount of digits the number has)
* Function Operation: the function counts the amount of digits the number has
*					  ****used in function addingBinaryProcess
***********************************************************************************/
int countDigit(unsigned long long num) {
	int count = 0;
	while (num > 0) {
		count++;
		num /= 10;
	}
	return count;
}

/***********************************************************************************
* Function Name: maxCount
* Input: int num1, int num2, int num3
* Output: int (the biggest number between num1, num2, num3)
* Function Operation: the function assume num1 is biggest, then checks if num2 is bigger then num1 and num3 ,
*					  if so,returns max is num2. if not,checks if num3 is bigger then num1 and num2,
*					  if so, returns max is num3. if not, returns max num1
*					  ****used in function addingBinaryProcess
***********************************************************************************/
int maxCount(int num1, int num2, int num3) {
	int max;
	max = num1;

	if (num1 <num2 && num2 > num3) {
		max = num2;
		return max;
	}
	else if (num1 < num3 && num3 >num2) {
		max = num3;
		return max;
	}
	else {
		return max;
	}
}

/***********************************************************************************
* Function Name: valueOfHexaDigit
* Input: char (values between '0'-'9' OR 'a'-'f' OR 'A'-'F')
* Output: int (value of digit in Decimal base)
* Function Operation: the function goes over all options for digit value and returns its value in Decimal base
***********************************************************************************/
int valueOfHexaDigit(char hexaDigit) {
	// break is not necessary because we use return function
	switch (hexaDigit) {

	case '0':
		return 0;

	case '1':
		return 1;

	case '2':
		return 2;

	case '3':
		return 3;

	case '4':
		return 4;

	case '5':
		return 5;

	case '6':
		return 6;

	case '7':
		return 7;

	case '8':
		return 8;

	case '9':
		return 9;

	case 'A':
	case 'a':
		return 10;

	case 'B':
	case 'b':
		return 11;

	case 'C':
	case 'c':
		return 12;

	case 'D':
	case 'd':
		return 13;

	case 'E':
	case 'e':
		return 14;

	case 'F':
	case 'f':
		return 15;

	default:
		return 0;
	}
}

/***********************************************************************************
* Function Name: printButterfly
* Input: int (h >= 0)
* Output: butterfly pattern
* Function Operation: the function prints the upper # line, the upper butterfly pattern,
*					  the middle line, the lower butterfly pattern, and the lower # line separately.
					  edge cases - if the size user asks is 0, or 1
***********************************************************************************/
void printButterfly(unsigned int n) {
	int row = 1, i, space;

	//if user entered 0 
	if (n == 0)
	{
		//printing the upper # line
		for (i = 0; i < 2; i++) {
			printf("#");
		}
		printf("\n");

		//printing the lower # line
		for (i = 0; i < 2; i++) {
			printf("#");
		}
		printf("\n");
		return;
	}

	//printing the upper # line
	if (n > 0) {

		//if user entered 1
		if (n == 1) {
			for (i = 0; i < 4; i++) {
				printf("#");
			}
			printf("\n");
		}
		//if user entered 2 or above
		if (n >= 2) {
			for (i = 0; i < 3; i++) {
				printf("#");
			}
			for (space = 1; space <= (2 * (n - row)) - 2; space++) {
				printf(" ");
			}
			for (i = 0; i < 3; i++) {
				printf("#");
			}
			printf("\n");
		}
	}

	//printing the upper butterfly pattern
	for (row = 1; row <= n - 1; row++) {
		printf("#");
		for (i = 1; i <= row; i++) {
			printf("*");
		}
		printf("#");
		for (space = 1; space <= (2 * (n - row)) - 2; space++) {
			printf(" ");
		}
		printf("#");
		for (i = row; i >= 1; i--) {
			printf("*");
		}
		printf("#\n");
	}

	//printing the middle line
	printf("#");
	for (i = 0; i < n * 2; i++) {
		printf("*");
	}
	printf("#\n");

	//printing the lower butterfly pattern
	for (row = n - 1; row >= 1; row--) {
		printf("#");
		for (i = 1; i <= row; i++) {
			printf("*");
		}
		printf("#");
		for (space = 1; space <= (2 * (n - row)) - 2; space++) {
			printf(" ");
		}
		printf("#");
		for (i = row; i >= 1; i--) {
			printf("*");
		}
		printf("#\n");
	}

	//printing the lower # line
	if (n > 0) {

		//if user entered 1
		if (n == 1) {
			for (i = 0; i < 4; i++) {
				printf("#");
			}
			printf("\n");
		}
		//if user entered 2 or above
		if (n >= 2) {
			for (i = 0; i < 3; i++) {
				printf("#");
			}
			for (space = 1, row = 1; space <= (2 * (n - row)) - 2; space++) {
				printf(" ");
			}
			for (i = 0; i < 3; i++) {
				printf("#");
			}
			printf("\n");
		}
	}
}

/***********************************************************************************
* Function Name: maxDigit
* Input: unsigned long num (num >= 0)
* Output: int (max value digit of the number)
* Function Operation: the function goes over all digits in the number and returns the maximum one
***********************************************************************************/
int maxDigit(unsigned long num) {
	int max = 0;
	while (num > 0) {
		if ((num % 10) > max) {
			max = num % 10;
			num /= 10;
			continue;
		}
		num /= 10;
	}
	return max;
}

/***********************************************************************************
* Function Name: digit1Counter
* Input: unsigned long num (number with digits 0 or 1 only)
* Output: int (counter of digit 1 appearances in the number)
* Function Operation: the function counts the number of times digit 1 appears in the binary form
*					  by comparing the last digit to 1 using bitWise and if true add to count.
*					  after each iteration it cuts the last binary digit.
***********************************************************************************/
int digit1BinaryCounter(unsigned long num) {
	int count = 0;

	while (num > 0) {
		if (num & 1) {
			count++;
		}
		num >>= 1;
	}
	return count;
}
