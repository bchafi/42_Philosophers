- Every philosopher needs to eat and should never starve.
- Philosophers do not communicate with each other.
- Philosophers do not know if another philosopher is about to die.
- Needless to say, philosophers should avoid dying!
## Global rules:
    ◦ Global variables are forbidden!
    ◦ Num_P time_die time_eat time_sleep [Num_times_P_must_eat](Optionel).
        => "number_of_P": The number of philosophers and also the number of forks.
        => "time_to_die (in milliseconds)": If a philosopher has not started eating within time_to_die milliseconds 
            since the start of their last meal or the start of the simulation, they die.
        => "time_to_eat (in milliseconds)": The time it takes for a philosopher to eat.
            During that time, they will need to hold two forks.
        => "time_to_sleep (in milliseconds)": The time a philosopher will spend sleeping.
        => "number_of_times_each_philosopher_must_eat (optional argument)": If all philosophers have eaten at least 
            number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation 
            stops when a philosopher dies.
    ◦ Each philosopher has a number ranging from 1 to number_of_P. (IF P = 0 => Ret 1;).
    ◦ Philosopher number 1 sits next to philosopher number number_of_P.
        => that is mean (if P = 5) : then the philos look at the table like this 5->[1]->2.=> "CIRCULAR".
    ◦ Any other philosopher, numbered N, sits between philosopher N - 1 and philosopher N + 1.
        => that is mean (if P = 5) : then the philos look at the table like this 3->[4]->5.
## Status Philosopher:
    > Any state change of a philosopher must be formatted as follows:
       ◦ timestamp_in_ms X has taken a fork.
       ◦ timestamp_in_ms X is eating.
       ◦ timestamp_in_ms X is sleeping.
       ◦ timestamp_in_ms X is thinking.
       ◦ timestamp_in_ms X died.
   > A displayed state message should not overlap with another message
   > A message announcing a philosopher’s death must be displayed within 10 ms of their actual death.
   > Your program must not have any data races. "to Show data Race: -fsanitize=thread".
   




if (num_philos * time_to_eat > time_to_die)
    printf("at least one philosopher will always die.\n");