#Philosophers

### *This project has been created as part of the 42 curriculum by slimvutt*

# Description
> The **Philosophers** project is all about learning the basics of **threading a process**.
> We need to learn how to create **threads** and discover **mutexes**.

> The **Dining Philosophers Problem**:
> A group of philosophers sit around a round table. There is a large bowl of spaghetti in the middle.
> For a philosopher to eat, they need **2 forks** (one on the left, one on the right).
> However, there are only as many forks as there are philosophers.
> The philosophers cycle through **Eating, Sleeping, and Thinking**.
> If a philosopher doesn't eat within a specific time ('time_to_die'), they will **starve to death**.

# Instructions
### Mandatory
> The mandatory part is about **Threads** and **Mutexes**.
> - Each philosopher is a **thread**.
> - There is one fork between each pair of philosophers.
> - Forks are protected by **mutexes** to prevent data races.

# Usage
### Mandatory
> cd philo
> make
> ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

### Arguments
- **number_of_philosophers**: The number of philosophers and also the number of forks.
- **time_to_die**: (in ms) If a philosopher doesn’t start eating 'time_to_die' after their last meal, they die.
- **time_to_eat**: (in ms) The time it takes for a philosopher to eat.
- **time_to_sleep**: (in ms) The time a philosopher will spend sleeping.
- **[number_of_times_must_eat]**: (Optional) If all philosophers eat at least this many times, the simulation stops.

# Examples
> ./philo 4 410 200 200
> *Philosophers should not die.*

> ./philo 4 310 200 100
> *A philosopher should die.*

# Resources
- **Core Concepts**
    - https://youtu.be/d9s_d28yJq0
    - https://42-cursus.gitbook.io/guide/3-rank-03/philosophers
    - https://www.youtube.com/watch?v=VSkvwzqo-Pk
    - https://www.youtube.com/watch?v=NbwbQQB7xNQ
    - https://expert-programming-tutor.com/tutorial/article/KC0010133004_what_is_Multi-Thread_in_C_language.php

