#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void who_wins(char *name, FILE *file, int m1);
int main() {
    time_t current = time(NULL);
    struct tm *date = localtime(&current);
    printf("Date: %d-%d-%d\n", 
           date->tm_year + 1900,
           date->tm_mon + 1,
           date->tm_mday
        ); 

    FILE * rps = fopen("rps.txt", "w");
    if (rps == NULL) {
        printf("Get outta here bro ??");
        return 1;
    }
    printf("Whats your name: ");
    char name[100];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove trailing newline
    fprintf(rps, "-----PLAYER NAME : %s -----", name);
    fflush(rps);
    int x1, x2, round = 1, flag = 0, m1=0,m2=0,m3=0;  // Initialize flag to 0
    char *choices[] = {"Rock", "Paper", "Scissors"};
    printf("1.Rock - 2.Paper - 3.Scissors - 4.Exit \n");
    srand(time(NULL));
    printf("Lets Play!\n");
    do {
        printf("-ROUND %d------------------\n", round);
        fprintf(rps, "------Round %d--------\n", round);  // Remove stdin, add newline
        fflush(rps);
        printf("%s: ", name); 
        do {
            scanf("%d", &x1);
            if (x1<1 || x1>4) {
                printf("No\n");
            }
        } while (x1<1 || x1>4);
        if (x1 == 4){
            if (m1>m2) {
                who_wins(name, rps, m1 );
            } else if (m2>m1) {
                who_wins("Computer", rps, m2);
            } else {
                fprintf(rps, "TIE in all points");
            }
            printf("Exiting");
            fprintf(rps, "NO GAME....\nExited at round : %d", round -1);
            return 0;
            fclose(rps);
        }
        x2 = (rand() % 3); // Changed to 0-2 range
        printf("%s: %s - Computer: %s \n",name, choices[x1-1], choices[x2]);
        if ((x1 == 1 && x2 == 2) || (x1 == 2 && x2 == 0) || (x1 == 3 && x2 == 1)) {
            printf("%s wins!!\n", name);
            fprintf(rps, "%s wins!!\n", name);  // Write to file with newline
            fflush(rps);
            flag = 0;
        } else if (x1 == x2) {
            printf("Tie\n");
            fprintf(rps, "Tie\n");
            fflush(rps);
            flag = -1;  // Add tie case
        } else {
            printf("Computer wins!!\n");
            fprintf(rps, "Computer wins!!\n");  // Write to file with newline
            fflush(rps);
            flag = 1;
        }
        switch (flag) {
            case 0:
                m1++;
                break;
            case 1:
                m2++;
                break;
            case -1:
                m3++;
                break;
        }
        round++;
    } while (x1 != 4);
    fclose(rps);
    return 0;
}

void who_wins(char *name, FILE *file, int m1) {
    fprintf(file, "%s wins with %d correct\n", name, m1);
    fflush(file);
}