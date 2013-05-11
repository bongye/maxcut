#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <math.h>

time_t start_time;
int i,j,k;
double ans = 0.0;

void signal_handler(int sig) {
	printf("alarm!!\n");
	printf("i=%d, j=%d, k=%d, ans=%f\n", i, j, k, ans);
	exit(EXIT_SUCCESS);
}

int main() {
	start_time = time(NULL);
	printf("It will stop in 5 seconds after beginning ..\n");
	signal(SIGALRM, signal_handler);

	alarm(5);

	for(i=0; i<10000; i++){
		for(j=0; j<10000; j++){
			for(k=0; k<10000; k++){
				ans = ans + sqrt(i) + sqrt(j) + sqrt(k);
			}
		}
	}

	return 0;
}
