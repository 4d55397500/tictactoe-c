# tictactoe-c
---

A minimax implementation of tic tac toe. See Russell and Norvig as a reference for the minimax algorithm and related concepts.


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
