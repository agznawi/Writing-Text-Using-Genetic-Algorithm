# Writing-Text-Using-Genetic-Algorithm

Watch it on YouTube:
https://www.youtube.com/watch?v=o7J1Tzq-52s

This program uses genetic algorithm to write an excerpt from Hamlet by generating random texts, evaluating each text, combining and modifying best texts randomly, and re-evaluating. The program repeats until the perfect text is found. The program evaluates each text by comparing it with the correct solution (an excerpt from Hamlet), and gives the text a score based on this comparison.

Genetic algorithm is a type of evolutionary algorithms. It is a search heuristic, inspired from natural evolution, used to generate useful solutions to optimization and search problems. It works by producing candidate solution to a problem and evolve it to a better solution using mutation that alters solution structure.

Since the solution is already exists and is used in the program to evaluate candidates, the purpose of this program is not to find a solution for a real problem, it is rather to demonestre how genetic algorithm works. The program is a simple way of implementing genetic algorithm: selection is simple and based on the raw fitness, no elitism or any advanced parameters. I wrote the program in C++11 on Ubuntu.

The algorithm:

1. Initialize random population of individuals (solutions)
2. Calculate fitness (evaluate solutions)
3. Select parents from best individuals
4. Crossover each pair of parents to creat a new offspring
5. Mutate some offsprings
6. Repeat 2 to 5 unitl e.g. finding termination criterion
