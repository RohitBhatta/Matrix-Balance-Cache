#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>

#include "matrix.h"

int matrix[N][N];

double getFrequencyGHz() {
    /* use lscpu to get the CPU frequency in MHz. Only works on Linux */
    /* writes the frequency in freq.txt */
    int t = 0;
    for (int i=0; i<100000000; i++) {
        t += rand();
    }
    printf("t=%d\n",t);
    int rc = system("cpupower frequency-info | grep 'available frequency steps: ' | sed -e s'/^.*: //' | sed -e 's/ .*//' > freq.txt");
    if (rc != 0) {
        perror("system");
        exit(-1);
    }

    /* open freq.txt */
    FILE *file = fopen("freq.txt","r");
    if (file == 0) {
        perror("open freq.txt");
        exit(-1);
    }

    /* read frequency from freq.txt */
    double freqGHz = 0;
    rc = fscanf(file,"%lf",&freqGHz);
    if (rc != 1) {
        perror("scanning file");
        exit(-1);
    }
    fclose(file);

    return freqGHz;
}

#define T 6

void report(uint64_t count, double cycleNS) {
    double nsPerThing = (T * 1e9) / count;
    double cyclesPerThing = nsPerThing / cycleNS;

    printf("    latency: %f ns %f cycles\n",nsPerThing,cyclesPerThing);
    printf("    rate: %f/ns %f/cycle\n",1/nsPerThing,1/cyclesPerThing);
}

volatile int done = 0;

void handler() {
    done = 1;
}

/* run one test */
void one(char* what, long (*func)(), double cycleNS) {
    uint64_t count = 0;

    done = 0;
    printf("%s ...\n",what);
    signal(SIGALRM,handler);
    alarm(T);
    
    while (!done) {
        count += func();
    }

    report(count,cycleNS);
}


extern long indepAdds();
extern long depAdds();

extern long indepMuls();
extern long depMuls();

extern long indepDivs();
extern long depDivs();

extern long indepLoads();
extern long depLoads();

extern long uncond();
extern long condTaken();
extern long condNotTaken();

int main(int argc, char* argv[]) {
    double freqGHz = getFrequencyGHz();
    double cycleNS = 1 / freqGHz;

    printf("freq = %fGHz, cycle_time = %fns\n",freqGHz,cycleNS);

    one("independent add instructions",indepAdds, cycleNS);
    one("dependent add instructions",depAdds, cycleNS);

    one("independent loads instructions",indepLoads, cycleNS);
    one("dependent load instructions",depLoads, cycleNS);

    one("independent multiply instrutions",indepMuls, cycleNS);
    one("dependent multiply instrutions",depMuls, cycleNS);

    one("independent divide instructions",indepDivs, cycleNS);
    one("dependent divide instructions",depDivs, cycleNS);

    one("unconditional jumps",uncond, cycleNS);
    one("conditional taken",condTaken, cycleNS);
    one("conditional not taken",condNotTaken, cycleNS);

    int c1 = 0;
    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            int b = rand() & 1;
            int x = rand();
            int y = b ? x : x+1;
            matrix[i][j] = x;
            matrix[j][i] = y;
            c1 += b;
        }
    }

    printf("matrix balance (per comparison) ...\n");

    signal(SIGALRM,handler);
    uint64_t count = 0;
    done = 0;

    alarm(T);

    while (!done) {
        int c2 = balance();
        count ++;
        if (c1 != c2) {
            printf("expected=%d found=%d\n",c1,c2);
            break;
        }
    }

    report((((N * N) - N) / 2) * count, cycleNS);

    return 0;
}
