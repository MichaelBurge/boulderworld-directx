#include "main.h"
int GetDirection(int x,int y,int x2,int y2) {	
	double temp = asin((x-x2)/sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2)));//Divide bottom length by hypotenuse to get sine, and asin() it
	if (temp < 0) temp *=-1;
	int ret = ((temp*180)/3.1415926535897932384626433832795);//Convert radians to degrees, and return
	
	if (x >= x2 && y <= y2) ret+=180;
	else if (x <= x2 && y >= y2) ret+=0;
	else if (x >= x2 && y >= y2) ret+=90;
	else ret+=270;
	
	return ret;
}

double DistanceToPoint(int x,int y,int x2,int y2) {
	double result=sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
	if (result<0) result*=-1;
	return result;
}

double degtorad(int deg) {
	return (deg*3.1415926535897932384626433832795)/180;
}
