# 42-philosophers

**Score: 100/100**

This project is about the famous dining philosophers problem and it teaches about multi-threaded programming, deadlocks, data races and mutexes.

## What is This Project

This project aims to simulate dining philosophers problem:

One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table. There are also forks on the table. There are as many forks as philosophers.

![Visual representation](./assets/philos.png)

Philosophers repeat three actions `eating -> sleeping -> thinking`. When eating, philosophers should use 2 forks one from right and one from left. After eating philosophers should put down their forks.

You can see the subject <a href="https://github.com/PeachAdam/philosophers-42/blob/main/en.subject.pdf">here</a>.

## How It Works

In my project every philosopher is a thread and every fork is a mutex. There is also one more thread (main thread) for checking if any philosopher died.

## Usage

Simply `make` and it will give the executable `philo`.

After compiling it use it like `./philo [number of philosophers] [time to die in ms] [time to eat in ms] [time to sleep in ms] {number of times each philosopher must eat}`.

The last argument is optional you can leave it blank if you want.

Some examples:
- `./philo 1 800 200 200` The philosopher should not eat and should die.
- `./philo 5 800 200 200` No philosopher should die.
- `./philo 5 800 200 200 7` No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
- `./philo 4 410 200 200` No philosopher should die.
- `./philo 4 310 200 100` One philosopher should die.
