#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

int words(char line[]) {
    int count = 0;
    int foundLetter = 0;
    for (int i=0; i<strlen(line); i++) {
        if (line[i] == ' ') {
            foundLetter=0;
        } else {
            if (foundLetter == 0) {
                count++;
            }
            foundLetter=1;
        }
    }
    return count;
}

void print_call_list(Array * callListp) {
    printf("CallList: ");
    char prefix;
    for (int i=0; i<CURRENT_INDEX(callListp); i++) {
        if (GET(callListp, i)>60) {
            prefix='X';
        } else if (GET(callListp, i)>45) {
            prefix='U';
        } else if (GET(callListp, i)>30) {
            prefix='N';
        } else if (GET(callListp, i)>15) {
            prefix='I';
        } else if (GET(callListp, i)>0) {
            prefix='L';
        }
        printf("%c%d ",prefix , GET(callListp, i));
    }
    printf("\n");
}

void print_card(Array * cardListp, Array * marksListp) {
    printf(" L   I   N   U   X\n");
    int index=0;
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (GET(marksListp, index) && index!=12) {
                printf("%02dm ", GET(cardListp, index));   
            } else {
                printf("%02d  ", GET(cardListp, index));
            }
            index++;
        }
        printf("\n");
    }
}

int check_win(Array * marksListp) {
    for (int i=0; i<25; i+=5) {
        int count=0;
        for (int j=0; j<5; j++) {
            if (GET(marksListp, i+j)) {
                count++;
            }
        }
        if (count == 5) {
            return 1;
        }
    }

    for (int j=0; j<5; j++) {
        int count=0;
        for (int i=0; i<25; i+=5) {
            if (GET(marksListp, i+j)) {
                count++;
            }
        }
        if (count == 5) {
            return 1;
        }
    }

    if (GET(marksListp, 0) && GET(marksListp, 4) && GET(marksListp, 24) && GET(marksListp, 20)) {
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    int seed;
    FILE *fp=fopen(argv[2],"r");
    char buffer[200];
    Array cardList;
    INITIALIZE(&cardList, 25);
    int n1, n2, n3, n4, n5;

    // check number of aguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s seed cardFile\n", argv[0]);
        exit(1);
    }

    // check seed type
    for (int i=0; i<strlen(argv[1]); i++) {
        if(!isdigit(argv[1][i])){
            fprintf(stderr, "Expected integer seed, but got %s\n", argv[1]);
            exit(2);            
        }
    }
    
    // check file readability
    if (fp == NULL) {
        fprintf(stderr, "%s is nonexistent or unreadable\n", argv[2]);
        exit(3);
    }

    // read file
    for (int i=0; i<5; i++) {
        fgets(buffer, sizeof(buffer), fp);
        if(buffer[14] != '\n') {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
        if (words(buffer) != 5) {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
        sscanf(buffer, "%d %d %d %d %d", &n1, &n2, &n3, &n4, &n5);
        if (CHECK(&cardList, n1)) {
            ADD(&cardList, n1);
        } else {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
        if (CHECK(&cardList, n2)) {
            ADD(&cardList, n2);
        } else {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
        if (CHECK(&cardList, n3)) {
            ADD(&cardList, n3);
        } else {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
        if (CHECK(&cardList, n4)) {
            ADD(&cardList, n4);
        } else {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
        if (CHECK(&cardList, n5)) {
            ADD(&cardList, n5);
        } else {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fprintf(stderr, "%s has bad format\n", argv[2]);
        exit(4);
    }

    for (int i=0; i<25; i+=5) {
        for (int j=0; j<5; j++) {
            if (GET(&cardList, i+j)<15*j+1 || GET(&cardList, i+j)>15*j+15) {
                if (GET(&cardList, i+j)!=0 || 12!=i+j) {
                    fprintf(stderr, "%s has bad format\n", argv[2]);
                    exit(4);
                }
            } else if (GET(&cardList, i+j)!=0 && 12==i+j) {
                fprintf(stderr, "%s has bad format\n", argv[2]);
                exit(4);
            }
        }
    }

    char input[4];
    int call;
    srand(seed);
    Array callList;
    INITIALIZE(&callList, 75);
    Array marksList;
    INITIALIZE(&marksList, 25);
    for (int i=0; i<25; i++) {
        ADD(&marksList, 0);
    }
    SET(&marksList, 12, 1);
    while (1) {
        system("clear");

        print_call_list(&callList);

        print_card(&cardList, &marksList);

        if (check_win(&marksList)) {
            printf("WINNER\n");
            exit(0);
        }

        printf("Enter any non-enter key for call (q to quit): ");
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "q\n") == 0) {
            break;
        } else if (strcmp(input, "\n") != 0) {
            while (1) {
                call = (rand() % (75)) + 1;
                if (CHECK(&callList, call)) {
                    break;
                }
            }

            ADD(&callList, call);
            
            if (!CHECK(&cardList, call)) {
                SET(&marksList, INDEX_OF(&cardList, call), 1);
            }
        }
    }

    return 0;
}