Observations:
1. In basic prevention using while loop
    -> No atomicity, race condition happens
    -> Preemption problem
    -> while() loop keeps cpu usage 100% ie. it doesn't sleep/wait the thread

    output looks like this
    Thread 0 counter: 1
    Thread 8Thread 6 counter: 2
    Thread 4 counter: 3
    Thread 2 counter: 3
     counter: 3
    Thread 3 counter: 3
    Thread 9Thread 1 counter: 3
    Thread 5 counter: 3
     counter: 3
    Thread 7 counter: 3

2. In advance preemption technique
    -> mutex enables atomicity
    -> condition variable sleeps/waits the process
    -> Race condition handled properly

    output looks like this:
    Thread: 0 counter 1
    Thread: 2 counter 2
    Thread: 1 counter 3
    Thread: 3 counter 4
    Thread: 4 counter 5
    Thread: 5 counter 6
    Thread: 6 counter 7
    Thread: 7 counter 8
    Thread: 8 counter 9
    Thread: 9 counter 10