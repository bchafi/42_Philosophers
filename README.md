## 🧠 **What You’re Building**

You are simulating philosophers sitting at a table:
- They alternate between **thinking**, **eating**, and **sleeping**.
- Each philosopher must **pick up two forks** (mutexes) to eat.
- The challenge is to make sure:
  - They don’t **die** from not eating in time.
  - There are **no deadlocks**.
  - The simulation runs **safely with threads**.

---
## ✅ **Step-by-Step Plan**
---

### 🟦 STEP 1: Parsing the Input
You already did this. ✅  
Example:  
```bash
./philo 5 800 200 200 7
```
Means:
- 5 philosophers
- 800 ms to die
- 200 ms to eat
- 200 ms to sleep
- each philosopher eats 7 times (optional)

---

### 🟦 STEP 2: Create Your Structs

#### Create `t_philo` and `t_data` structs:

```c
// philo.h
typedef struct s_data {
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_required;
    long start_time;
    int someone_died;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
} t_data;

typedef struct s_philo {
    int id;
    int meals_eaten;
    long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
} t_philo;
```

---

### 🟦 STEP 3: Initialize Data and Mutexes

- Allocate `t_philo` array for all philosophers.
- Allocate `pthread_mutex_t` array for forks.
- A mutex (mutual exclusion) is a lock that prevents multiple threads from modifying the same resource at the same time.
```
  pthread_mutex_t my_mutex; // Declare a mutex
  pthread_mutex_init(&my_mutex, NULL); // Initialize the mutex
  pthread_mutex_lock(&my_mutex); // Lock it (wait if already locked)
  pthread_mutex_unlock(&my_mutex); // Unlock it
  pthread_mutex_destroy(&my_mutex); // Free resources
```
We also use a mutex for printing to prevent messages from overlapping.
```c
  d_dataP->forks = malloc(sizeof(pthread_mutex_t) * d_dataP->num_philos);
  if (!d_dataP->forks)
  {
      free(d_dataP);
      exit(1);
  }
  i = 0;
  while (i < d_dataP->num_philos)
  pthread_mutex_init(&d_dataP->forks[i++], NULL);
  pthread_mutex_init(&d_dataP->print_lock, NULL);
```

---
###  4️⃣ Allocating and Initializing Philosophers
We now allocate an array of philosophers (t_philo) and assign:
- Their IDs
- Their forks (left & right)
- Their shared data pointer

```c
  int i;

  d_dataP->philos = malloc(sizeof(t_philo) * d_dataP->num_philos);
  if (!d_dataP->philos)
  {
	free(d_dataP);
	free(d_dataP->forks);
	exit(1);
  }
  i = 0;
  while (i < d_dataP->num_philos)
  {
	d_dataP->philos[i].id = i + 1;
	d_dataP->philos[i].left_fork = &d_dataP->forks[i];
	d_dataP->philos[i].right_fork = &d_dataP->forks[(i + 1) % d_dataP->num_philos];
	d_dataP->philos[i].meals_eaten = 0;
	d_dataP->philos[i].last_meal = get_time_in_ms();
	d_dataP->philos[i++].data = d_dataP;
  }
```
🔍 What’s Happening Here?
✅ Allocate memory for all philosophers.
✅ Assign philosopher IDs (starting from 1, not 0).
✅ Link left and right forks correctly (last philosopher takes fork 0).
✅ Store initial meal timestamp to track starvation.

### 🟦 STEP 4: Creating Threads (in depth)
🎯 Goal:
You want each philosopher to run in parallel, doing their own thing (thinking, eating, sleeping).
To do this, you’ll use pthread_create() to launch a thread per philosopher.
✅ pthread_t — the thread identifier
```
   pthread_t thread;
```
✅ pthread_create() — to create a thread
```
   int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
       void *(*start_routine) (void *), void *arg);
  // 🧱 thread: variable to hold the thread
  // 🧱 start_routine: function that the thread will run
  // 🧱 arg: pointer to a struct containing data for that thread
```

### 🟦 STEP 5: Write the Philosopher Routine

Each philosopher thread runs this function:

```c
void *philo_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;

    while (!philo->data->someone_died) {
        // Think
        // Pick up forks (mutex lock)
        // Eat
        // Put down forks (mutex unlock)
        // Sleep
    }
    return NULL;
}
```

---

### 🟦 STEP 6: Eating and Forks

Use `pthread_mutex_lock()` to pick up forks.

```c
pthread_mutex_lock(philo->left_fork);
pthread_mutex_lock(philo->right_fork);

// Eat
philo->last_meal = current_time();
philo->meals_eaten++;

pthread_mutex_unlock(philo->right_fork);
pthread_mutex_unlock(philo->left_fork);
```

Also use `usleep(time_to_eat * 1000);` to simulate eating.

---

### 🟦 STEP 7: Add Death Monitor Thread

This thread checks if any philosopher hasn’t eaten in time.

```c
while (1) {
    for (int i = 0; i < data->num_philos; i++) {
        if (current_time() - philo[i].last_meal > data->time_to_die)
        {
            pthread_mutex_lock(&data->print_lock);
            printf("%ld %d died\n", current_time() - data->start_time, philo[i].id);
            data->someone_died = 1;
            return;
        }
    }
    usleep(1000);
}
```

---

### 🟦 STEP 8: Join Threads & Clean Up

After starting threads, use `pthread_join()` to wait for them:

```c
for (int i = 0; i < data->num_philos; i++) {
    pthread_join(philo[i].thread, NULL);
}
```

Then destroy all mutexes.

---

## 🚀 You're Done!

At this point:
- All philosophers are threads.
- Forks are protected with mutexes.
- A monitor detects death.
- Simulation ends cleanly.

---

### 📦 Summary of What You Build

| Part               | Concept |
|--------------------|--------|
| `pthread_create()` | Starts a new thread (philosopher). |
| `pthread_mutex_lock()` | Used to pick up a fork. |
| `pthread_mutex_unlock()` | Used to put down a fork. |
| `usleep()`         | Wait (simulate eating/sleeping). |
| `pthread_join()`   | Wait for threads to finish. |
| `gettimeofday()`   | Track current time. |

---

Would you like to go into any of these parts **one by one** with code examples?  
For example:  
- Just setting up threads  
- Writing the eat/thinking/sleep logic  
- How to track time and detect death  

Let me know where you'd like to zoom in 🔍
