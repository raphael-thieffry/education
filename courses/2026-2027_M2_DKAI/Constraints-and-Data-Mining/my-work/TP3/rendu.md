# E1

## Q2
In dataset you just choose the dataset

In model you select your constraints you want to work with

In dashboard you get the results and the speed at which it runned (+ some propagation stats)

SPMF is if you want to use the spmf library

History is the list of your previous runs

## Q3

I set a min relative freq of 20% 

lazaar.txt

9 solutions 0.0s

## Q4
mushrooms

1169 solutions
1.6s

chess-kr-vs-kp

216907 solutions
30s (TO)

## Q5

(keeping mushrooms)

```bash
[11:54:18] Running SPMF LCM (closed itemsets) [0.2] on /home/user/cours/DKAI/CP/TP3/mushrooms.txt...
[11:54:18] >/home/user/Téléchargements/spmf.jar
[11:54:19] ========== LCM - STATS ============
[11:54:19]  Freq. closed itemsets count: 1169
[11:54:19]  Total time ~: 745 ms
[11:54:19]  Max memory:74.89189147949219
[11:54:19] =====================================
[11:54:19] 1169 pattern(s) found - 745ms, 74,9MB
```

It matches what we found with CP, and it's faster but the comparison is not fair because this is a basic task, for which the algorithm was specifically tailored
As seen in class, the CP version becomes interesting when used in addition with other constraints


# E2

## Q2

```bash
❯ mvn compile exec:java -Dexec.mainClass=com.example.App
[INFO] Scanning for projects...
[INFO] 
[INFO] --------------------------< com.example:tp3 >---------------------------
[INFO] Building tp3 1.0-SNAPSHOT
[INFO] --------------------------------[ jar ]---------------------------------
[INFO] 
[INFO] --- maven-resources-plugin:3.3.1:resources (default-resources) @ tp3 ---
[INFO] skip non existing resourceDirectory /home/user/cours/DKAI/CP/TP3/tp3/src/main/resources
[INFO] 
[INFO] --- maven-compiler-plugin:3.13.0:compile (default-compile) @ tp3 ---
[INFO] Nothing to compile - all classes are up to date.
[INFO] 
[INFO] --- exec-maven-plugin:3.6.4:java (default-cli) @ tp3 ---
Database: lazaar.txt
Time: 5ms
Number of solutions: 9
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  0.719 s
[INFO] Finished at: 2026-10-15T12:29:57+02:00
[INFO] ------------------------------------------------------------------------
```

=> This execution used a frequency lowerbound of 20% of the size of the dataset (via the domain)

It matches what I did in exercise 1

## Q3
### 1
Already done in the last question, but using the domain directly

### 2
For this question, keeping only patterns of size 3 or more (with frequency of 20%), on laazar I get 4 solutions and on pasquier, O get 3 solutions; 

```bash
Solution 1: 1 2 4 Solution 2: 0 1 2 4 Solution 3: 0 2 3 Database: contextPasquier99.dat
Time: 6ms
Number of solutions: 3
--------------------------------------------------
Solution 1: 0 4 5 Solution 2: 0 2 3 7 Solution 3: 1 4 5 6 Solution 4: 1 2 6 7 Database: lazaar.txt
Time: 3ms
Number of solutions: 4
```


## Q4

Applied to lazaar, my implementation, with $catSize = 3$ and $m = 2$ gives a total of 4 solutions.

```bash
❯ mvn compile exec:java -Dexec.mainClass=com.example.App
[...]
Solution 1: 0 3 ; Freq : 2
Solution 2: 0 4 5 ; Freq : 1
Solution 3: 0 2 3 7 ; Freq : 1
Solution 4: 1 4 5 6 ; Freq : 1
Time: 2ms
Number of solutions: 4
Database: lazaar.txt
[...]
```

And these results are coherent

## Q5

To have this "category constraint" combined with the SPMF library without editing the algorithms into a specific method, you would need to apply the LCM algorithm, and them filter out the ouputs to keep only relevant ones.
This option creates a huge amount of useless candidate solutions, and the search space explodes, making the approach impractical for larger datasets.

It is for such use cases that constraint programing applied to data mining find its strength.