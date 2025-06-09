# 🧠 Philosophers - Dining Philosophers Problem

This project is part of the 42 curriculum. It implements a multithreaded simulation of the classic Dining Philosophers problem. The goal is to prevent philosophers from starving while optimizing resource usage at the thread level.

## 🚀 Features

- Thread-based simulation using `pthread`
- Mutex synchronization for forks
- Optional eating count termination condition
- Thread-level optimization for performance
- Can simulate up to hundreds of philosophers (depending on CPU)
- Logging optimized with `write()` instead of `printf()` for better performance and output control

## ⚙️ How to Use

### 1. Build the Project

```bash
make
```

### 2. Run the Program

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument                                  | Description                                                                 |
|------------------------------------------|-----------------------------------------------------------------------------|
| `number_of_philosophers`                 | Number of philosophers (and forks); must be ≥ 1                             |
| `time_to_die` (in ms)                    | Time a philosopher can go without eating before dying                      |
| `time_to_eat` (in ms)                    | Time it takes for a philosopher to eat *(recommended minimum: 60ms)*       |
| `time_to_sleep` (in ms)                  | Time a philosopher spends sleeping *(recommended minimum: 60ms)*           |
| `number_of_times_each_philosopher_must_eat` *(optional)* | If specified, simulation ends when all philosophers have eaten this many times |

### 💡 Notes

- For a stable simulation, `time_to_die` must be sufficiently larger than `time_to_eat` and `time_to_sleep`.
    - For even numbers of philosophers, `time_to_die` should be at least **2 × time_to_eat + α**.
    - For odd numbers of philosophers, `time_to_die` should be at least **3 × time_to_eat + α**.
    - In general, `time_to_die` must be **greater than (time_to_eat + time_to_sleep + α)** to avoid starvation due to system scheduling delays.
- Once the simulation starts, philosophers begin eating in parallel threads.
- The program is designed to prevent philosophers from dying due to starvation.
- With high philosopher counts (e.g. 200+), system performance may cause timing issues.
- All output is timestamped and shows philosopher actions clearly (e.g., taking a fork, eating, sleeping, etc.)

### 🧪 Example

```bash
./philo 5 800 200 200
```

This starts a simulation with:
- 5 philosophers
- 800ms time to die
- 200ms time to eat
- 200ms time to sleep

Each philosopher picks up two forks to eat. After eating, they sleep, then think. If any philosopher fails to eat within `time_to_die`, the simulation ends with a death log.

## 📜 License

This project is licensed under the MIT License.
See the [LICENSE](./LICENSE) file for details.
