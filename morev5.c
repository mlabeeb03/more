//	v0	read a single file
//	v1 	read multiple files
//	v2	read one page at a time and handle ' ', '\n', 'q'
// 	v3 	reverse video
//	v4	io redirection skipped
//	v5	display % of file displayed

#include <stdio.h>
#include <stdlib.h>

#define LINELEN 512
#define PAGELEN 20

int toatlLines;			//stores total lines in a file
int numOfLinesDone;		//stores total lines that have been displayed from the file, gets used to calculate percentage of file displayed

int findLines(char filename[]){		//returns total number of lines in file
	int lines = 0;
	FILE *fp = fopen(filename, "r");
	char chr = getc(fp);
	while(chr != EOF){
		if(chr == '\n'){
			lines++;
		}
		chr = getc(fp);
	}
	fclose(fp);
	return lines;
}

int get_input(){
	int c;
	int perc = ((float)numOfLinesDone/toatlLines)*100;	//stores percentage of lines displayed
	printf("\033[7m --more-- (%d%%) \033[m", perc);
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
	numOfLinesDone = 0;
	int num_of_lines = 0; 	//number of lines displayed on the screen, increase when new line printed, reset when 20 more lines need to be printed
	int rv;		//store user input

	char buffer[LINELEN];	//reading this much data from each line, it is assumed that line size will not be larger than this

	while(fgets(buffer, LINELEN, fp)){
		fputs(buffer, stdout);
		num_of_lines++;
		numOfLinesDone++;

		if(num_of_lines == PAGELEN){
			rv = get_input();
			//user pressed q
			if(rv == 0){
				printf("\033[1A \033[2K \033[1G");
				break;
			}
			//user pressed space						
			else if(rv == 1){
				printf("\033[1A \033[2K \033[1G");
				num_of_lines -= PAGELEN;	
			}	
			//user pressed enter
			else if(rv == 2){
				printf("\033[1A \033[2K \033[1G");
				num_of_lines -= 1;	
			}	
			//invalid character	
			else if(rv == 3){
				printf("\033[1A \033[2K \033[1G");
				break;	
			}					
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
		toatlLines = findLines(argv[i]);
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