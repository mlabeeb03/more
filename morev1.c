//	v0	read a single file
//	v1 	read multiple files

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

	int i = 0; //counter for number of files
	FILE* fp;
	while(++i < argc){
		fp = fopen(argv[i], "r");	
		if(fp ==NULL){
			perror("Can't open file");
			exit(1);
		}
		do_more(fp);
		fclose(fp);
	}
	return 0;
	
}