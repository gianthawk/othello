Othello - Week 10 - Ramya Deshpande & Maitreyi Nair
Team: Dark Mink

Describe how and what each group member contributed for the past
 two weeks. If you are solo, these points will be part of the next section.

At the beginning of week 9, Ramya set up the Github repository. We
worked concurrently to develop a functional AI that used the 
heuristic approach. During Week 10, we worked together to improve our
minimax algorithm, ultimately implementing a recursive algorithm.

Document the improvements that your group made to your AI to make it 
tournament-worthy. Explain why you think your strategy(s) will work. Feel 
free to discuss any ideas were tried but didn't work out.

Initially, when implementing minimax, Ramya tried an iterative 2-ply method,
which was functional but we decided to improve it further. Maitreyi adapted 
the exiting iterative method to a recursive approach, with variable depth
(currently 5), that combines the previous heuristic algorithm (contains multipliers
based on Othello strategy) with a decision tree that ultimately selects the optimal 
move at each step. 