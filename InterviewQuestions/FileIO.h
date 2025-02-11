#pragma once

#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include "StructAndFunc.h"

void saveFile(struct interviewQuestions* questionColl, int collectionSize) {
    FILE* file = fopen("questions.dat", "wb");

    printf("Saving to file...\n");
    for (int i = 0; i < collectionSize; i++) {
        struct interviewQuestions question = questionColl[i];
        fwrite(&question, sizeof(struct interviewQuestions), 1, file);
    }
    fclose(file);

}

void loadFile(struct interviewQuestions* questionColl, int questionNum, int* questionNumptr, int collectionSize , int* collectionSizeptr, int availableCollIndex, int* availableCollIndexPtr) {
    FILE* file = fopen("questions.dat", "rb");

    if (!file) {
        printf("Error: File not found or cannot be opened.\nStarting with an empty question set.\n");
    }
    else {
        struct interviewQuestions questions;

        // Read the question set from the file
        while (fread(&questions, sizeof(struct interviewQuestions), 1, file)) {
            //If collection is full
            if (availableCollIndex > collectionSize) {
                printf("Collection full, adding more memory\n");
                *collectionSizeptr = collectionSize + 5;

                reallocateMemory(collectionSize, questionColl);
            }

            struct interviewQuestions* currentQuestion = {questionNum ,questions.question, false};
            questionColl[availableCollIndex] = currentQuestion;

            *availableCollIndexPtr = availableCollIndex + 1;
            *questionNumptr = questionNum++;

        }
        fclose(file);
        printf("Questions loaded from file.\n");
    }
}

#endif
