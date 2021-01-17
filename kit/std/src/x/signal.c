// /**
//  * @file    x/signal.c
//  * @brief
//  * 
//  */

// #include <unistd.h>
// #include <signal.h>

// #include "std.h"

// /**
//  * @fn      void xinterrupt(void)
//  * 
//  */
// void xinterrupt(void)
// {
//     // TODO: sigqueue 함수의 결과를 체크하고 로그를 남깁니다.
//     sigqueue(getpid(), SIGINT, (union sigval) { 0 });
// }