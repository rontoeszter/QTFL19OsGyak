#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void do_nothing();
void do_break();

int main(){
	int i;
	unsigned int sec = 1;
	signal(SIGINT, do_break);

	for(i = 1; i < 8; i++){
	alarm(sec);
	signal(SIGALRM, do_nothing);
	printf("%d varok\n", i);
	pause();
	}

return 0;
}

void do_nothing(){
	printf("ALARM\n"); }


void do_break(){
	printf("Megszakitas!\n");
	signal(SIGINT, SIG_IGN); }

