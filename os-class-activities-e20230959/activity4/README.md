# Class Activity 4 — Shared File API

- **Student Name:** PUM BRUSMUNY
- **Student ID:** e20230959
- **Partner Name:** [TODO: Partner Name]
- **Partner Student ID:** [TODO: Partner ID]
- **Server Machine Owner:** [TODO: Your Name or Partner Name]
- **Server IP Address:** [TODO: e.g. 192.168.1.25]

---

## Task 1: C++ Before Mutex

![C++ before mutex](screenshots/cpp_before_mutex.png)

- **Expected score after 20 total client requests:** 20
- **Actual score:** [TODO: observed value from `shared_score.txt`]
- **What happened:** [TODO: Describe the race condition observed — e.g., multiple detached threads read the same score before sleeping 200ms and overwrote each other's updates]

---

## Task 2: C++ After Mutex

![C++ after mutex](screenshots/cpp_after_mutex.png)

- **Expected score after 20 total client requests:** 20
- **Actual score:** [TODO: observed value from `shared_score.txt`, should be 20]
- **What changed after adding mutex:** [TODO: Describe what changed — `std::lock_guard<std::mutex>` serialized access to `update_score()` so every increment was preserved]

---

## Task 3: Java Before Synchronized

![Java before synchronized](screenshots/java_before_synchronized.png)

- **Expected score after 20 total client requests:** 20
- **Actual score:** [TODO: observed value from `shared_score.txt`]
- **What happened:** [TODO: Describe the race condition observed across concurrent Java handler threads]

---

## Task 4: Java After Synchronized

![Java after synchronized](screenshots/java_after_synchronized.png)

- **Expected score after 20 total client requests:** 20
- **Actual score:** [TODO: observed value from `shared_score.txt`, should be 20]
- **What changed after adding synchronized:** [TODO: Describe what changed — adding `synchronized` to `updateScore()` ensured mutual exclusion so the final score reliably reached 20]

---

## Questions

1. **Why should clients send requests to the server instead of writing the file directly?**
   > Centralizing file access in a single server API guarantees only one program owns and touches `shared_score.txt`. Clients do not need direct filesystem access or distributed file-locking coordination across different machines; the server acts as a single control point that validates requests and enforces synchronization in one place.

2. **Why does the server still have a race condition before mutex or synchronized?**
   > Even though only the server touches `shared_score.txt`, the server spawns a separate thread for each incoming client connection (`std::thread(...).detach()` in C++ and `new Thread(...).start()` in Java). Without synchronization, multiple worker threads execute `update_score()` / `updateScore()` concurrently—reading the same old score before the 200 ms sleep and overwriting one another's writes (lost updates).

3. **In the C++ fixed version, what does `std::lock_guard<std::mutex>` protect?**
   > `std::lock_guard<std::mutex> lock(file_mutex);` protects the entire critical section inside `update_score()`—specifically reading the current score from `shared_score.txt`, sleeping 200 ms, incrementing `score`, and writing the new score back to `shared_score.txt`. It acquires `file_mutex` on construction and automatically releases it when `lock` goes out of scope (RAII), ensuring only one thread executes `update_score()` at a time.

4. **In the Java fixed version, what does `synchronized` protect?**
   > Marking `private static synchronized int updateScore(String name)` acquires the intrinsic monitor lock on the `ScoreServerSync.class` object for the duration of the method. It protects the critical section (reading `shared_score.txt`, sleeping 200 ms, incrementing `score`, and writing the updated value back) so only one thread at a time can execute `updateScore()`.

5. **Why is the final score expected to be 20 when Student A sends 10 requests and Student B sends 10 requests?**
   > `shared_score.txt` is reset to `0` before each test, and each client connection sends one request that triggers `score++` (an increment by `1`). With 10 requests from Student A and 10 requests from Student B (`10 + 10 = 20` total atomic updates starting from `0`), the expected final value is `20`.

6. **What could happen if two separate servers update the same file at the same time?**
   > An in-process `std::mutex` or Java `synchronized` monitor only coordinates threads **within the same process**. Two separate server processes have separate memory spaces and separate locks, so they could still read stale values and overwrite `shared_score.txt` simultaneously—causing race conditions, lost updates, or file corruption unless an OS-level inter-process lock (such as `flock()`/file locking) or an external database is used.

---

## Reflection

_TODO: Compare your observed C++ (`std::mutex` + `std::lock_guard`) and Java (`synchronized`) results and reflect on what this activity taught you about protecting shared resources._
