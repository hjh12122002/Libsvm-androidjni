#include <jni.h>
#include <string.h>
#include <stdio.h>
#include "log.h"
#include "train.h"
#include "./svm/svm-train.h"

#define LOG_TAG "TRAIN"
#define PARA_LEN 10 // Max length for each parameter

int train(const char *trainingFile, int kernelType, int cost, float gamma,
        const char *modelFile) {
    int cmdLen = 9;
    char *cmd[cmdLen];

    LOGD("Coming into training\n");

    cmd[0] = "donotcare";

    cmd[1] = "-t";
    cmd[2] = (char *)calloc(PARA_LEN, sizeof(char));
    sprintf(cmd[2], "%d", kernelType); // Too lazy to implement a itoa ^_^

    cmd[3] = "-c";
    cmd[4] = (char *)calloc(PARA_LEN, sizeof(char));
    sprintf(cmd[4], "%d", cost);

    cmd[5] = "-g";
    cmd[6] = (char *)calloc(PARA_LEN, sizeof(char));
    sprintf(cmd[6], "%.2f", gamma);

    int len = strlen(trainingFile);
    cmd[7] = (char *)calloc(len+1, sizeof(char));
    strncpy(cmd[7], trainingFile, len);
    cmd[7][len] = '\0';

    len = strlen(modelFile);
    cmd[8] = (char *)calloc(len+1, sizeof(char));
    strncpy(cmd[8], modelFile, len);
    cmd[8][len] = '\0';

    int result = svmtrain(cmdLen, cmd);
    for (int i = 2; i < cmdLen-2; i *= 2) { free(cmd[i]); }

    return result;
}