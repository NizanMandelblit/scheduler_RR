
#include "string.h"
#include "stdio.h"

/**
 * procsses control block to hold all relevent information about a procses
 */
struct pcb {
    int pid;         /* ID of the proces */
    int priority;    /* process priority */
    int is_attached; /* 1 if attached to processlist, else 0 */
    int *function;   /* pointer to the process function */
    char name[10];   /* Name of the process */
} typedef pcb;

pcb processlist[2];

//proccses for testing
int process0();

int process1();

/**
 * @brief  the function attach a proccses to the proceses list
 * @note
 * @param  *name: name of the procses
 * @param  priority: priority number of the procses
 * @param  *function: pointer to procses function
 * @retval 0 if all went well, -1 for errors.
 */
int process_attach(char *name, int prio, void *function) {
    int i = 0;
    printf("\nbeginning process_attach\n");
    while (i < 2) {
        //looking for a vacant spot in the proccses list to attach the procsess to
        if (processlist[i].is_attached != 1) {

            printf("\nattach process at %d", i);
            processlist[i].pid = i;
            strcpy(processlist[i].name, name);
            processlist[i].priority = prio;
            processlist[i].function = function;
            processlist[i].is_attached = 1;
            break;
        }
        printf("\n");
        i++;
    }
    return 0;
}

/**
 * @brief  the function is deatching a proccses from the procsess list.
 * @note   please be aware the procsess object is not being removed from the list,
 *         rather the function simply changes its 'is_attached' attribute to false.
 * @param  pid: the procsess id number
 * @retval 0 if all went well.
 */
int process_detach(int pid) {
    processlist[pid].is_attached = 0;
    return 0;
}

int process0() {
    printf("\ntest procsses 0\n");
    return 0;
}

int process1() {
    printf("\ntest procsess 1\n");
    return 0;
}

/**
 * @brief  a function to simulate a simple RR non-preemptive scheduler .
 * @note
 * @retval
 */
int scheduler() {
    int i = 0;
    void (*p)(void);

    while (1) {
        for (i = 0; i < 2; i++) {
            if (processlist[i].is_attached == 1) {
                p = (void *) processlist[i].function;
                (*p)();
            }
        }
        break;
    }
    return 0;
}


int main() {

    //testing the scheduler
    process_attach("process0", 10, process0);
    process_attach("process1", 9, process0);
    scheduler();
    getchar( );


}