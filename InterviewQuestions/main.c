#define _CRT_SECURE_NO_WARNINGS //only for visual studio compiler

#include <stdio.h>
#include <stdlib.h>

#include "StructAndFunc.h"
#include "FileIO.h"
#include "MenuFunc.h"


int main(void) {
    int collectionSize = 10;
    int* collectionSizePtr = &collectionSize;

    int questionNum = 1;
    int* questionNumPtr = &questionNum;

    int availableCollIndex = 0;
    int* availableCollIndexPtr = &availableCollIndex;

    int numOfDeleted = 0;
    _Bool trueOrFalse = false;

    int choice;
    int check;

    /*
    //HardCoded filename 
    //char fileName[50] = "questions.dat";

    //gettiing binary data file
    printf("Don't forget to enter '.dat' to symbolize its a binary file!\nEnter your binary data file: ");
    char* fileName = (char*)malloc(50 * sizeof(char));
    check = scanf("%50s", fileName);
    */

    //ALLOCATE THE MEMORY
    struct interviewQuestions* questionCollection = allocateMemory(collectionSize);

    //LOAD FILE
    loadFile(questionCollection, questionNum, questionNumPtr, collectionSize, collectionSizePtr, availableCollIndex, availableCollIndexPtr);

    do {
        displayMenu();
        printf(">> ");
        check = scanf("%1d", &choice);

        switch (choice) {
        case 1:
            viewAllQuestions(questionCollection, collectionSize);
            break;
        case 2:
            //Went through w debugger, and works everytime, but breaks sometimes when its not??
            askQuestion(questionCollection, collectionSize);
            break;
        case 3:
            //IMPLEMENT
            addQuestion(questionCollection, collectionSize, collectionSizePtr, availableCollIndex, availableCollIndexPtr, questionNum, questionNumPtr);
            break;
        case 4:
            trueOrFalse = deleteQuestion(questionCollection, collectionSize);
            if (trueOrFalse == true) {
                trueOrFalse = false;
                numOfDeleted++;

                if (numOfDeleted == 5) {
                    questionCollection = timeForNewList(questionCollection, collectionSize, availableCollIndex, availableCollIndexPtr);
                    numOfDeleted = 0;
                    collectionSize = collectionSize - 5;
                }
            }
            break;
        case 5:
            shuffleQuestions(questionCollection, collectionSize);
            break;
        case 6:
            saveFile(questionCollection, collectionSize);
            printf("Questions saved successfully.\n\nExiting...\n");
            break;
        default:
            printf("Invalid option. Please choose from the provided.\n");
            break;
        }
    } while (choice != 6);


}