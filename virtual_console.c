#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[16];

void setup() {
	printf("Welcome to this virtual interface made using Vim, some VS Code and C.\n");
	printf("I hope you enjoy your stay!\n");
}

void access_session() {
	FILE* access = fopen("access_names.txt", "a");
	if(access == NULL) {
		perror("ID Files could not be accessed. ");
		fclose(access);
		return;
	}
	else {
		string name;
		string passcode;
		char check_id[64];
		printf("Enter your access name: ");
		fgets(name, 15, stdin);
		printf("Great! Welcome to the program, %s", name);
		printf("Enter your access passcode (your access passcode can contain from 1 to 15 characters with no spaces): ");
		scanf("%15s", passcode);
		fprintf(access, "%s: ", name);
		fprintf(access, "%s\n", passcode);
		printf("Thank you for your information. This will be stored in an access log for data reference. The program will start shortly.\n");
		fclose(access);
	}
	return;
}

void str_to_int_array(char str1[9], int int_array[8]) {
	int chr_int;
	for(int i = 0; i <= 7; i++) {
		chr_int = str1[i] - '0';
		int_array[i] = chr_int;
	}
	return;
}

void convert(int num) {
	int local_num = num;
	int rem = 0;
	int binary_num[8] = {0};
	for(int i = 7; i >= 0; i--) {
		rem = local_num % 2;
		local_num /= 2;
		binary_num[i] = rem;
	}
	for(int n = 0; n <= 7; n++) {
		printf("%d", binary_num[n]);
	}
	printf("\n");
	return;
}

void convert_bin(int binary[8]) {
	int decimal = 0;
	int index = 7;
	for(int i = 1; i < 256; i *= 2) {
		decimal += binary[index] * i;
		index--;
	}
	printf("%d\n", decimal);
	return;
}

void convert_hex(int binary[8]) {
	char characters[] = {'A', 'B', 'C', 'D', 'E', 'F'};
	char digit1;
	char digit2;
	int decimal = 0;
	int index = 3;
	for(int i = 1; i < 16; i *= 2) {
		decimal += binary[index] * i;
		index--;
	}
	if(decimal < 10) {
		digit1 = decimal + '0';
	}
	else {
		digit1 = characters[decimal - 10];
	}
	decimal = 0;
	index = 7;
	for(int j = 1; j < 16; j *= 2) {
		decimal += binary[index] * j;
		index--;
	}
	if(decimal < 10) {
		digit2 = decimal + '0';
	}
	else {
		digit2 = characters[decimal - 10];
	}
	printf("%c%c\n", digit1, digit2);
	return;
}

void echo(char sentence[65]) {
	printf("%s\n", sentence);
	return;
}

void command_line(string directory) {
	char cmd[65];
	int decimal = 0;
	int binary[8] = {0};
	printf("%s$- ", directory);
	fgets(cmd, 64, stdin);
	char* cmds[2] = {NULL, NULL};
	char* cmd_ptr = strtok(cmd, " \n");
	if(cmd_ptr == NULL) {
		printf("No command entered. Please try again.\n");
		command_line(directory);
		return;
	}
	cmd_ptr = strtok(NULL, " \n");
	cmds[0] = strtok(cmd, " \n");
	cmds[1] = cmd_ptr;
	if(strcmp(cmds[0], "help")==0) {
		printf("Command list: \n");
		printf("help : View command list\n");
		printf("convert : Convert a decimal integer up to 255 to an 8 bit binary\n");
		printf("convert_bin : Convert an 8 bit binary back to a decimal integer\n");
		printf("convert_hex : Convert an 8 bit binary to a 2 digit hex code\n");
		printf("echo : Print a string that you enter\n");
		printf("exit : Quit the program\n");
		printf("clr : Clear the entire terminal (good for cleanup)\n");
		printf("Just type a command and your number/string argument!\n");
		printf("Just make sure that you type a space between your argument and command.\n");
		printf("More commands will be added in the future!\n");
	}
	else if(strcmp(cmds[0], "convert")==0) {
		if(cmds[1]==NULL) {
			printf("Command 'convert' expects an integer argument. Please try again.\n");
			command_line(directory);
			return;
		}
		convert(atoi(cmds[1]));
  }
	else if(strcmp(cmds[0], "convert_bin")==0) {
		if(cmds[1]==NULL) {
			printf("Command 'convert_bin' expects an 8 bit binary argument. Please try again. \n");
			command_line(directory);
			return;
		}
		str_to_int_array(cmds[1], binary);
		convert_bin(binary);
	}
	else if(strcmp(cmds[0], "convert_hex")==0) {
		if(cmds[1]==NULL) {
			printf("Command 'convert_hex' expects an 8 bit binary argument. Please try again. \n");
			command_line(directory);
			return;
		}
		str_to_int_array(cmds[1], binary);
		convert_hex(binary);
	}
	else if(strcmp(cmds[0], "echo")==0) {
		if(cmds[1]==NULL) {
			printf("Command 'echo' expects a string argument. Please try again. \n");
			command_line(directory);
			return;
		}
		echo(cmds[1]);
	}
	else if(strcmp(cmds[0], "clr")==0) {
		system("clear");
		command_line(directory);
		return;
	}
	else if(strcmp(cmds[0], "exit")==0) {
		exit(0);
	}
	else {
		printf("Unknown command: %s\n", cmds[0]);
	}
	command_line(directory);
	return;
}

int main() {
	setup();
	access_session();
	string dir;
	printf("Enter your chosen directory: ");
	scanf(" %15s", dir);
	printf("help : Show command list\n");
	command_line(dir);
	return 0;
}
