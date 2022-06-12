//
// Created by Jasonkay on 2022/6/12.
//

#include <cstdlib>
#include <cstdio>
#include <setjmp.h>

int max_iteration = 9;
int iter;

jmp_buf Main;
jmp_buf PointPing;
jmp_buf PointPong;

void Ping(void);
void Pong(void);

int main(int argc, char* argv[]) {
    iter = 1;
    if (setjmp(Main) == 0) Ping();
    if (setjmp(Main) == 0) Pong();
    longjmp(PointPing, 1);
}

void Ping(void) {
    if (setjmp(PointPing) == 0) longjmp(Main, 1); // 可以理解为重置，reset the world
    while (1) {
        printf("%3d : Ping-", iter);
        if (setjmp(PointPing) == 0) longjmp(PointPong, 1);
    }
}

void Pong(void) {
    if (setjmp(PointPong) == 0) longjmp(Main, 1);
    while (1) {
        printf("Pong\n");
        iter++;
        if (iter > max_iteration) exit(0);
        if (setjmp(PointPong) == 0) longjmp(PointPing, 1);
    }
}
