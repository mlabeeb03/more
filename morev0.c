//	v0	read a single file

#include <stdio.h>
#include <stdlib.h>

#define LINELEN 512

void do_more(FILE* fp){
	char buffer[LINELEN];
	while(fgets(buffer, LINELEN, fp)){
		fputs(buffer, stdout);
	}
}

int main(int argc, char *argv[]){

	//check if any filename was passed or not
	if(argc == 1){
		printf("Help page\n");
		exit(0);
	}

	FILE* fp;
	fp = fopen(argv[1], "r");

	if(fp ==NULL){
		perror("Can't open file");
		exit(1);
	}

	do_more(fp);

	fclose(fp);
}