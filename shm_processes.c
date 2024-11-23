//Russell Langham Jr
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/* Semaphore wait operation */
struct sembuf Pop = {0, -1, 0};
/* Semaphore signal operation */
struct sembuf Vop = {0, 1, 0};

void ParentProcess(int ShmPTR[], int semID, int id);
void ChildProcess(int ShmPTR[], int semID, int id);
void MomProcess(int ShmPTR[], int semID);

int main(int argc, char *argv[]) {
    int num_parents, num_children, ShmID, semID, *ShmPTR;
    pid_t pid;
    int i;

    if (argc < 3) {
        printf("Usage: %s <num_parents> <num_children>\n", argv[0]);
        exit(1);
    }

    num_parents = atoi(argv[1]);
    num_children = atoi(argv[2]);

    /* Create shared memory for BankAccount */
    ShmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (ShmID < 0) {
        perror("shmget error");
        exit(1);
    }
    ShmPTR = (int *)shmat(ShmID, NULL, 0);

    /* Initialize BankAccount */
    *ShmPTR = 0;

    /* Create semaphore set (1 semaphore for mutual exclusion) */
    semID = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (semID < 0) {
        perror("semget error");
        exit(1);
    }
    semctl(semID, 0, SETVAL, 1);

    /* Fork parent processes (Dad and optional Mom) */
    for (i = 0; i < num_parents; i++) {
        pid = fork();
        if (pid == 0) {
            if (i == 0) {
                ParentProcess(ShmPTR, semID, i); /* Dear Old Dad */
            } else {
                MomProcess(ShmPTR, semID); /* Lovable Mom */
            }
            exit(0);
        }
    }

    /* Fork child processes (Poor Students) */
    for (i = 0; i < num_children; i++) {
        pid = fork();
        if (pid == 0) {
            ChildProcess(ShmPTR, semID, i);
            exit(0);
        }
    }

    /* Wait for all child processes to finish */
    while (wait(NULL) > 0);

    /* Cleanup */
    shmdt(ShmPTR);
    shmctl(ShmID, IPC_RMID, NULL);
    semctl(semID, 0, IPC_RMID, 0);

    return 0;
}

/* ParentProcess: Implements Dear Old Dad's behavior */
void ParentProcess(int ShmPTR[], int semID, int id) {
    int localBalance, action, deposit;
    srand(time(NULL) ^ getpid());
    while (1) {
        sleep(rand() % 6);
        printf("Dear Old Dad: Attempting to Check Balance\n");

        semop(semID, &Pop, 1); /* Lock semaphore */
        localBalance = *ShmPTR;
        action = rand();
        if (action % 2 == 0) {
            if (localBalance < 100) {
                deposit = rand() % 101;
                if (deposit % 2 == 0) {
                    localBalance += deposit;
                    printf("Dear Old Dad: Deposits $%d / Balance = $%d\n", deposit, localBalance);
                    *ShmPTR = localBalance;
                } else {
                    printf("Dear Old Dad: Doesn't have any money to give\n");
                }
            } else {
                printf("Dear Old Dad: Thinks Student has enough Cash ($%d)\n", localBalance);
            }
        } else {
            printf("Dear Old Dad: Last Checking Balance = $%d\n", localBalance);
        }
        semop(semID, &Vop, 1); /* Unlock semaphore */
    }
}

/* MomProcess: Implements Lovable Mom's behavior */
void MomProcess(int ShmPTR[], int semID) {
    int localBalance, deposit;
    srand(time(NULL) ^ getpid());
    while (1) {
        sleep(rand() % 11); /* Random sleep between 0-10 seconds */
        printf("Lovable Mom: Attempting to Check Balance\n");

        semop(semID, &Pop, 1); /* Lock semaphore */
        localBalance = *ShmPTR;
        if (localBalance <= 100) {
            deposit = rand() % 126;
            localBalance += deposit;
            printf("Lovable Mom: Deposits $%d / Balance = $%d\n", deposit, localBalance);
            *ShmPTR = localBalance;
        } else {
            printf("Lovable Mom: Balance sufficient ($%d)\n", localBalance);
        }
        semop(semID, &Vop, 1); /* Unlock semaphore */
    }
}

/* ChildProcess: Implements Poor Student's behavior */
void ChildProcess(int ShmPTR[], int semID, int id) {
    int localBalance, action, need;
    srand(time(NULL) ^ getpid());
    while (1) {
        sleep(rand() % 6); /* Random sleep between 0-5 seconds */
        printf("Poor Student[%d]: Attempting to Check Balance\n", id);

        semop(semID, &Pop, 1); /* Lock semaphore */
        localBalance = *ShmPTR;
        action = rand();
        if (action % 2 == 0) {
            need = rand() % 51;
            printf("Poor Student[%d] needs $%d\n", id, need);
            if (need <= localBalance) {
                localBalance -= need;
                printf("Poor Student[%d]: Withdraws $%d / Balance = $%d\n", id, need, localBalance);
                *ShmPTR = localBalance;
            } else {
                printf("Poor Student[%d]: Not Enough Cash ($%d)\n", id, localBalance);
            }
        } else {
            printf("Poor Student[%d]: Last Checking Balance = $%d\n", id, localBalance);
        }
        semop(semID, &Vop, 1); /* Unlock semaphore */
    }
}
