#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

struct header {
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[8];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
} header;


int main() {
	int exit = 0;
	int cw;
	cw = dup(1);
	int f = creat("files.txt", S_IRUSR | S_IWUSR);
	dup2(f, 1);
	pid_t p1 = fork();
	if (p1 == 0) {
		execlp("ls", "ls", "-la", "--time-style", "full-iso", NULL);
	}
	else {
		wait(NULL);
	}
	int f1 = creat("usermap.txt", S_IRUSR | S_IWUSR);
	dup2(f1, 1);
	pid_t p2 = fork();
	if (p2 == 0) {
		execlp("cat", "cat", "/etc/passwd", NULL);
	}
	else {
		wait(NULL);
	}
	dup2(cw, 1);

	pid_t p3 = fork();
	if (p3 == 0) {
		execlp("mkdir", "mkdir", "dir", NULL);
	}
	else {
		wait(NULL);
	}

	pid_t p4 = fork();
	if (p4 == 0) {
		execlp("cp", "cp", "-r", ".", "./dir/", NULL);
	}
	else {
		wait(NULL);
	}


	do {

		char input[200];
		char file[50], dir[50];
		fgets(input, 200, stdin);
		int i = 0, space = 0, tar = 0;
		int a = 0, b = 0, slash = 0;
		for (i = 0; input[i] != '\0'; i++) {
			if (input[i] == '/') {
				slash++;
			}
			if (input[i] == ' ') {
				space++;
			}
			if (input[i] == '.') {
				if (input[i + 1] == 't' && input[i + 2] == 'a' && input[i + 3] == 'r')
					tar++;
			}
			if (input[i] == 'e') {
				if (input[i + 1] == 'x' && input[i + 2] == 'i' && input[i + 3] == 't')
					exit++;
			}
		}
		if ((space != 2 || tar != 1 || slash != 1) && exit == 0) {
			printf("\nWrong Input\n");
		}
		else if (exit != 1) {
			for (i = 0; input[i] != '\0'; i++) {
				if (input[i] == ' ') {
					i++;
					while (input[i] != ' ') {
						file[a++] = input[i++];
					}
					file[a] = '\0';
					i++;
					while (input[i] != '/') {
						dir[b++] = input[i++];
					}
					dir[b] = '\0';
				}
			}
			pid_t p;
			p = fork();
			if (p == 0) {
				execlp("tar", "tar", "cvf", file, dir, NULL);
			}
			else {
				wait(NULL);
				printf("\nDone\n");
			}
		}
	} while (exit == 0);
	return 0;
}
