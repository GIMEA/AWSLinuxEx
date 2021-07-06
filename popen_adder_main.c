#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	FILE *read_fp;
	char buffer[BUFSIZ + 1];
	long result = 0;
	
	memset(buffer, '\0', sizeof(buffer));

	read_fp = popen("./popen_adder", "r");
	result = atoi(read_fp);
	printf("%ld", result);


}
