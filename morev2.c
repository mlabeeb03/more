//	v0	read a single file
//	v1 	read multiple files
//	v2	read one page at a time and handle ' ', '\n', 'q'

#include <stdio.h>
#include <stdlib.h>

#define LINELEN 512
#define PAGELEN 20

int get_input(){
	int c;
	c = getchar();
	if(c == 'q')
		return 0;
	if(c == ' ')
		return 1;
	if(c == '\n')
		return 2;
	return 3;
}

void do_more(FILE* fp){
	int num_of_lines = 0; 	//number of lines displayed on the screen, increase when new line printed, reset when 20 more lines need to be printed
	int rv;		//store user input
	char buffer[LINELEN];
	while(fgets(buffer, LINELEN, fp)){
		fputs(buffer, stdout);
		num_of_lines++;
		if(num_of_lines == PAGELEN){
			rv = get_input();
			if(rv == 0)		//user pressed q
				break;
			else if(rv == 1)	//user pressed space
				num_of_lines -= PAGELEN;
			else if(rv == 2)	//user pressed enter
				num_of_lines -= 1;
			else if(rv == 3)	//invalid character
				break;
		}
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