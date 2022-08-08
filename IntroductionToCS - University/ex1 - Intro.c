/*********************
* Topaz Avraham
* 206842627
* ex_1
*********************/

#include <stdio.h>
#include <math.h>

void hello() {
	// Task 1 = a command to print the following string: "hello \/\/orld %d\n" as is.
	printf("\"hello \\/\\/orld %%d\\n\"\n");
}

void distance() {
	// Task 2 = print distance between 2 points
	double x1, y1, x2, y2, distance;

	printf("Enter x1:\n");
	scanf("%lf", &x1);
	printf("Enter y1:\n");
	scanf("%lf", &y1);
	printf("Enter x2:\n");
	scanf("%lf", &x2);
	printf("Enter y2:\n");
	scanf("%lf", &y2);

	//the formula to calculate the distance
	distance = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

	printf("The distance between the points is: %.4lf\n", distance);
}

void conversions() {
	// Task 3 = print conversions of an nm number 
	int nm;
	double mm, cm, dm, m, km;
	printf("Please enter nm:\n");
	scanf("%d", &nm);
	//casting the nm to double beacuse we need the exact precision of the division after the dot
	mm = ((double)nm / 1000000);
	cm = mm / 10;
	dm = cm / 10;
	m = dm / 10;
	km = m / 1000;

	// %010.4 = meaning we pad with zeros from the left, we print 10 chars (width 10), and 4 digits after the dot.
	printf("%010.4lf km\n%010.4lf m\n%010.4lf dm\n%010.4lf cm\n%010.4lf mm\n%010d nm\n", km, m, dm, cm, mm, nm);
}

void baking() {

	// Task 4 = print when the cake will be ready 

	// declaring variables and assign them according to the user 
	int bakingTimeHour, bakingTimeMinutes, bakingTimeSeconds,
		startingTimeHour, startingTimeMinutes, startingTimeSeconds,
		readyTimeHour, readyTimeMinutes, readyTimeSeconds;

	printf("Please enter the baking time: [hh:mm:ss]\n");
	scanf("%d:%d:%d", &bakingTimeHour, &bakingTimeMinutes, &bakingTimeSeconds);

	printf("When did you put the cake into the oven? [hh:mm:ss]\n");
	scanf("%d:%d:%d", &startingTimeHour, &startingTimeMinutes, &startingTimeSeconds);


	readyTimeSeconds = startingTimeSeconds + bakingTimeSeconds;
	//if the seconds are bigger than 60, it would add it to minutes
	readyTimeMinutes = (startingTimeMinutes + bakingTimeMinutes) + (readyTimeSeconds / 60);
	//if the minutes are bigger than 60, it would add it to hours
	readyTimeHour = (startingTimeHour + bakingTimeHour) + (readyTimeMinutes / 60);

	//after we added time to who is neccesary, now we adjust it to show standard time format
	readyTimeSeconds %= 60;
	readyTimeMinutes %= 60;
	readyTimeHour %= 24;

	//if the hours/minutes/seconds time is smaller than 10, the 02%d will put a 0 before the digit
	printf("The cake will be ready at %02d:%02d:%02d o'clock.\n", readyTimeHour, readyTimeMinutes, readyTimeSeconds);
}

void main() {
	hello();
	distance();
	conversions();
	baking();
}