/**
 * 
 * sigaction
 * 
 * examine and change a signal action.
 * 
 * ```
 * #include <signal.h>
 * 
 * int sigaction(int signum, const struct sigaction * act, struct sigaction * old);
 * ```
 * 
 * The `sigaction()` system call is used to change the action taken by a process on receipt of a specific signal.
 * `signum` specifies the signal and can be any valid signal except `SIGKILL` and `SIGSTOP`.
 * If `act` is non null, the new action for signal `signum` is installed from act.
 * If `oldact` is non null, the previous action is saved in oldact.
 * The sigaction struct is defind as something like:
 * 
 * ```
 * struct sigaction {
 *     void     (*sa_handler)(int);
 *     void     (*sa_sigaction)(int, siginfo_t *, void *);
 *     sigset_t   sa_mask;
 *     int        sa_flags;
 *     void     (*sa_restorer)(void);
 * };
 * ```
 * 
 * On some architectures a union is involed: do not assign to both `sa_hander` and `sa_sigaction`.
 * 
 * The `sa_restorer` field is not intended for application use.
 * POSIX does not specify a sa_restorer field.
 * Some further details of the purpose of this field can be found in `sigreturn`.
 * 
 * `sa_handler` specifies the action to be associated with `signum` and may be `SIG_DFL` for the default action, `SIG_IGN` to ignore this signal, or a pointer to a signal handling function.
 * This function receives the signal number as its only argument.
 * 
 * If `SA_SIGINFO` is specified in sa_flags,
 * then `sa_sigaction` (instread of `sa_handler`) specifies the signal handling function for `signum`.
 * 
 * This function receives three arguments, as described below.
 * 
 * `sa_mask` specifies a mask of signals which should be blocked (i.e., added to the signal mask of the thread in which the signal handler is invoked) during execution of the signal handler.
 * In addition, the signal which triggered the handler will be blocked, unless the `SA_NODEFER` flag is used.
 * 
 * 
 * @see overview of signals.
 */




    //    sa_flags specifies a set of flags which modify the behavior of the signal.  It is formed by the bitwise OR of zero or more of the following:

    //        SA_NOCLDSTOP
    //               If signum is SIGCHLD, do not receive notification when child processes stop (i.e., when they receive one of SIGSTOP, SIGTSTP, SIGTTIN, or SIGTTOU) or resume (i.e., they receive SIGCONT) (see wait(2)).  This flag is
    //               meaningful only when establishing a handler for SIGCHLD.

    //        SA_NOCLDWAIT (since Linux 2.6)
    //               If signum is SIGCHLD, do not transform children into zombies when they terminate.  See also waitpid(2).  This flag is meaningful only when establishing a handler for SIGCHLD, or when setting that signal's  disposi‐
    //               tion to SIG_DFL.

    //               If the SA_NOCLDWAIT flag is set when establishing a handler for SIGCHLD, POSIX.1 leaves it unspecified whether a SIGCHLD signal is generated when a child process term


// #include <stdio.h>
// #include <stdlib.h>

// #include "event.h"

// /**
//  * @fn      xevent * xeventnew(xuint32 type, xeventobj * target, xeventgenerator * generator)
//  * @brief   이벤트를 생성합니다.
//  * @details 동적할당으로 생성해야 할까?
//  * 
//  * @param   type      | xuint32 | in | 이벤트 타입 |
//  * @param   target    | xeventobj * | in | 이벤트 타겟 |
//  * @param   generator | xeventgenerator * | in | 이벤트를 생성한 제네레이터 |
//  * 
//  * @return  | event * | 이벤트 객체 |
//  */
// xevent * xeventnew(xuint32 type, xeventobj * target, xeventgenerator * generator)
// {
//     xevent * o = (xevent *) malloc(sizeof(xevent));

//     o->type = type;
//     o->target = target;
//     o->generator = generator;

//     return o;
// }

// /**
//  * @fn      void * xeventrem(void * p)
//  * @brief   이벤트 객체를 메모리에서 해제합니다.
//  * @details
//  * 
//  * @param   p | void * | in | 이벤트 객체의 포인터 주소 |
//  * 
//  * @return  | void * | 해제된 이벤트 객체의 주소로 언제나 널을 리턴합니다. |
//  */
// void * xeventrem(void * p)
// {
//     xassertion(p == xnil, "null pointer exception");

//     free(p);

//     return xnil;
// }


// int main(int argc, char ** argv)
// {
//     xeventengine engine = xeventengineinit();
//     return xeventengine_run(&engine);
// }

