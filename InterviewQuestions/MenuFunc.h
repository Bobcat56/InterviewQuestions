#pragma once

#ifndef MENUFUNC_H
#define MENUFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include "StructAndFunc.h"

void displayMenu() {
    printf("\n**********************************\n");
    printf("\nInterview Questions\n");
    printf("1. View All Questions\n");
    printf("2. Ask a Question\n");
    printf("3. Add a Question\n");
    printf("4. Delete a Question\n");
    printf("5. Shuffle Questions\n");
    printf("6. Save to File and Exit\n");
    printf("\n**********************************\n");
}

void viewAllQuestions(struct interviewQuestions* questionColl, int collectionSize) {
    for (int i = 0; i < collectionSize; i++) {
        //If question is deleted skip iteration
        if (questionColl[i].deleted) {
            continue;
        }

        //If no question exists in location leave function
        if (questionColl[i].questionId == 0){
            return;
        }

        printf("\n%d.)", questionColl[i].questionId);
        printf("%s", questionColl[i].question);
    }
    printf("\n");
}

bool deleteQuestion(struct interviewQuestions* questionColl, int collectionSize) {
    int check;
    int questionNum;

    printf("\nEnter the question number you wish to delete: ");
    //Can keep at 2d since not more than 99 question will be added
    check = scanf("%2d", &questionNum);

    for (int i = 0; i < collectionSize; i++) {
        if (questionColl[i].questionId == questionNum) {
            if (questionColl[i].deleted == false) {
                questionColl[i].deleted = true;
                printf("Question has been deleted");
                
                return true;
            }
            else {
                printf("Question has already been deleted.");
                return false;
            }
        }
        else {
            printf("Question does not exist\n");
            return false;
        }
    }
    return false;
}

void addQuestion(struct interviewQuestions* questionColl, int collectionSize , int* collectionSizePtr, int availableCollIndex, int* availableCollIndexPtr, int questionNum, int* questionNumptr) {
    //FIX UP 
    struct interviewQuestions questions;

    printf("Enter the new question: ");
    char* newQuestion = (char*)malloc(MAX_LENGTH * sizeof(char));
    scanf("%250s", newQuestion);

    // If no available slot is found, reallocate memory and increase the collection size
    if (availableCollIndex > collectionSize) {
        printf("Collection full, adding more memory\n");
        *collectionSizePtr = collectionSize + 5;

        reallocateMemory(collectionSize, questionColl);
    }

    // Update the question in the data structure
    struct interviewQuestions currentQuestion = { questionNum, questions.question, false };
    questionColl[availableCollIndex] = currentQuestion;

    *availableCollIndexPtr = availableCollIndex + 1;
    *questionNumptr = questionNum++;


    printf("Question added successfully.\n");
}

void shuffleQuestions(struct interviewQuestions* questionColl, int collectionSize) {
    //Fisher-Yates shuffle
    for (int i = collectionSize - 1; i > 0; i--) {
        // Generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);

        // Swap the questions at index i and j
        struct interviewQuestions temp = questionColl[i];
        questionColl[i] = questionColl[j];
        questionColl[j] = temp;
    }

    printf("Questions shuffled successfully.\n");
}

void askQuestion(struct interviewQuestions* questionColl, int collectionSize) {
    //Array to store the indices of non-deleted questions
    int* nonDeletedIndices = (int*)malloc(collectionSize * sizeof(int));
    int count = 0;

    // Finding indices of non-deleted questions and stroing them into a list
    for (int i = 0; i < collectionSize; i++) {
        if (questionColl[i].deleted == false) {
            nonDeletedIndices[count] = i;
            count++;
        }
    } 

    // If no non-deleted questions are found
    if (count == 0) {
        printf("No available questions to ask.\n");
        free(nonDeletedIndices);
        return;
    }

    // Select a random index from the undeleted questions (Fetches from list)
    int randomIndex = nonDeletedIndices[rand() % count];

    int questionNumber = questionColl[randomIndex].questionId;
    char question[250] = { questionColl[randomIndex].question };

    // Print the selected question
    printf("%d.) %s", questionNumber, question);

    free(nonDeletedIndices);
}

struct interviewQuestions* timeForNewList(struct interviewQuestions* questionColl, int collectionSize, int availableCollIndex, int* availableCollIndexPtr) {
    //If 5 questions are set to delete, copy undeleted and free old collection
    int newCollectionSize = collectionSize - 5;
    struct interviewQuestions* newQuestionColl = allocateMemory(newCollectionSize);
    availableCollIndex = 0;

    for (int i = 0; i < newCollectionSize; i++) {
        if (questionColl[i].deleted == true) {
            continue;
        }
        else if (questionColl[i].questionId == 0) {
            free(questionColl);
            return newQuestionColl;
        }
        else {
            newQuestionColl[availableCollIndex] = questionColl[i];
            *availableCollIndexPtr = availableCollIndex + 1;
        }
    }
}

#endif