# tictactoe-c
---

A minimax implementation of tic tac toe. See Russell and Norvig as a reference for the minimax algorithm and related concepts.
Since tic tac toe is a 'non-reversible' game: that is, it's not possible to revisit the same game state twice in a given game, 
it's not necessary to actually build up the game play tree structure for minimax. Rather, it's sufficient to simply compute the (unique) score for each game state, recursively, by visiting all next game states according to the rules of the game. In this way the entire game tree is visited, even though it's not created nor is its structure known in advance. 

### Run

Run the main program. The output should look something like below. With player 'x' playing minimax and player 'o' playing randomly, player 'x' always wins. However (you can try by uncommenting a line in the code) if both players play the minimax strategy from the same tree, the result is always a stalemate, as expected for both players playing an ideal strategy in tic tac toe.

```

training minimax ...
best: 0
playing game, with player x using minimax, player o playing randomly.
player x played:
x e e
e e e
e e e
player o played:
x e o
e e e
e e e
player x played:
x e o
x e e
e e e
player o played:
x e o
x o e
e e e
player x played:
x e o
x o e
x e e
player x wins.

```
