#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int status = 0;

static void simple_signal_proc(int num)
{
    printf("%d\n", num);
    status = 1;
}

static void simple_signalaction_proc(int num, siginfo_t * info, void * data)
{
    printf("%d\n", num);
    printf("code: %d\n", info->si_code);
    printf("errno: %d\n", info->si_errno);
    printf("no: %d\n", info->si_signo);
    printf("pid: %d\n", info->si_pid);
    printf("data => %p\n", data);
    printf("value: %d\n", info->si_value.sival_int);

    status = 1;
}

static void simple_sigaction_restorer(void){

}

int main(int argc, char ** argv)
{
    printf("%d\n", SIGRTMAX);
    // xeventengine
    // xevent
    /**
     * 
     */
    struct sigaction action = (struct sigaction) { 0, };
    action.sa_sigaction = simple_signalaction_proc;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &action, NULL);
    // action.__sigaction_handler = &simple_signalaction_proc;
//    action.sa_mask;

    //            struct sigaction {
    //            void     (*sa_handler)(int);
    //            void     (*sa_sigaction)(int, siginfo_t *, void *);
    //            sigset_t   sa_mask;
    //            int        sa_flags;
    //            void     (*sa_restorer)(void);
    //        };

    // signal(SIGINT, simple_signal_proc);
           
    while(status == 0)
    {
        sleep(1);

        // sigqueue(getpid(), SIGINT, (union sigval) { 1 });
    }

    return 0;
}