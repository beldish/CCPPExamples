#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define NUM_THREADS 5 // Define number of threads here or take as user input
#include <Windows.h>

#define BUF_SIZE 255

static volatile int done = 0;
HANDLE ghMutex;

typedef struct threadData
{
    int num;
    long int counter;
} threadData;

DWORD WINAPI workerThread(threadData *x)
{
    threadData *pth = x;
    printf("Thread %d starting \n", pth->num);
    while (!done)
    {
        WaitForSingleObject(ghMutex, INFINITE);
        pth->counter = pth->counter + 10 * pth->num;
        ReleaseMutex(ghMutex);
        // printf("Thread %d counter = %ld \n", pth->num, pth->counter);
        Sleep(10);
    }
    printf("Thread %d stopping \n", pth->num);
    return 0;
}

DWORD WINAPI reporterThread(threadData *x)
{
    threadData *pth = x;
    printf("Reporter thread starting \n");
    while (!done)
    {
        printf("\rReporter thread - ");
        WaitForSingleObject(ghMutex, INFINITE);
        for (int i = 0; i < 5; i++)
            printf("%ld ", pth[i].counter);
        // printf("\n");
        ReleaseMutex(ghMutex);
        Sleep(10);
    }
    printf("Reporter thread stopping \n");
    return 0;
}

int main()
{
    // int limit;
    // printf("How much time would you like (In secs): ");
    // scanf("%d", &limit);
    // scanf("%d", &NUM_THREADS);    //Take number of threads as Input

    ghMutex = CreateMutex(NULL, FALSE, NULL);

    HANDLE *arrayThread;
    arrayThread = (HANDLE *)malloc((NUM_THREADS + 1) * sizeof(int));
    // DWORD ThreadId;

    threadData pars[5] = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};

    for (int i = 0; i < NUM_THREADS; i++)
    {
        // printf("Creating thread %d \n", i);
        arrayThread[i] = CreateThread(NULL, 0, workerThread, &pars[i], 0, NULL);
        if (arrayThread[i] == NULL)
        {
            printf("Create Thread %d get failed. Error no: %d", i, GetLastError());
        }
    }

    arrayThread[NUM_THREADS] = CreateThread(NULL, 0, reporterThread, pars, 0, NULL);
    if (arrayThread[NUM_THREADS] == NULL)
    {
        printf("Create Reporter Thread get failed. Error no: %d", GetLastError());
    }

    printf("Press enter to terminate\n");
    getchar();

    done = 1;

    WaitForMultipleObjects(NUM_THREADS + 1, arrayThread, TRUE, INFINITE);
    // DWORD lpExitCode;
    // BOOL result;

    for (int i = 0; i <= NUM_THREADS; i++)
    {
        CloseHandle(arrayThread[i]);
    }

    // system("PAUSE");
    return 0;
}
