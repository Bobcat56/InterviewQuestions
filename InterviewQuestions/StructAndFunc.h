#pragma once

#ifndef STRUCTANDFUNC_H
#define STRUCTANDFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LENGTH 250

struct interviewQuestions {
    int questionId; //QuestionNumber
    char question[MAX_LENGTH];
    _Bool deleted;
};

//Function to allocate memory to a struct
struct interviewQuestions* allocateMemory(int numOfQuestions) {
    struct interviewQuestions* questionColl = (struct interviewQuestions*)malloc(numOfQuestions * sizeof(struct interviewQuestions));
    return questionColl;
};

//Function to re-allocate memory to a struct
void reallocateMemory(int newSize, struct interviewQuestions* questionColl) {
    questionColl = (struct interviewQuestions*)realloc(questionColl, newSize * sizeof(struct interviewQuestions));
};

#endif

