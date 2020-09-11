#include <stdio.h>
#include <math.h>

int i = 0;

int recursiva(){
	if(i > 365000)
		return 0;

	printf("10");
	i++;
	return recursiva();
}

int main(int argc, char const *argv[]){

	recursiva();
}
