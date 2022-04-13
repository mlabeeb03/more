//	v0	read a single file
//	v1 	read multiple files
//	v2	read one page at a time and handle ' ', '\n', 'q'
// 	v3 	reverse video

#include <stdio.h>
#include <stdlib.h>

#define LINE_L 512
#define LINES 29

int get_input(){
	char c;
	printf("\033[7m--More--(%%)\033[m");
	c = getchar();
	if(c == 'q'){
		return 0;
	}
	else if(c == ' ')
		return 1;
	else if(c == '\n')
		return 2;
	else
		return 3;
}

void show(FILE *fp){
	char buffer[LINE_L];
	int num_of_lines = 0;
	int usr_inp;
	while(fgets(buffer, LINE_L, fp)){
		fputs(buffer, stdout);
		num_of_lines++;
		if(num_of_lines == LINES){
			usr_inp = get_input();
			if(usr_inp == 0){
				printf("\033[1A \033[2K \033[1G");
				break;
			}
			else if(usr_inp == 1){
				printf("\033[1A \033[2K \033[1G");
				num_of_lines -= LINES;
			}
			else if(usr_inp == 2){
				printf("\033[1A \033[2K \033[1G");
				num_of_lines -= 1;
			}
			else if(usr_inp == 3){
				printf("\033[1A \033[2K \033[1G");
				break;
			}
		}
	}
}

int main(int argc, char *argv[]){
	if(argc == 1){
		printf("more: bad usage\nTry 'more --hlep' for more information.\n");
		exit(0);
	}
	FILE *fp;
	int i = 0;	//counter for num of files
	while(++i < argc){
		fp = fopen(argv[i], "r");
		if(fp == NULL){
			perror("Can't open file");
			exit(1);
		}	
		show(fp);
		fclose(fp);
	}
	return 0;
}