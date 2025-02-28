# Solution Explanation 

Code inspired by Dijkstra's solution in Wikipedia article: https://en.wikipedia.org/wiki/Dining_philosophers_problem

Dijkstra's solution: This algorithm allows philosophers to think, try to grab both forks when available, and eat at the same time (following multithreading) as long as two philosophers do not share a left and right fork and both forks are available. Furthermore, deadlocks are avoided by having a mutex lock that protect philosophers in a critical section to finish and not intefere with their current state without any race conditions. A philosopher can be thinking (state defined as 0), trying to reach for left and right available forks (state defined as 1), and eat as long as this philosopher is not sharing a fork with another (state defined as 2). 