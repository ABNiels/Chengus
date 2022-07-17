### Structure
- GameBoard
  - Game state
    - array of 64 squares
    - en passant square
    - current turn order
    - current number
    - current 50 move rule plies
  - array of 2 players
  - evalutation
- Square
  - Pointer to piece type on the square
  - Pointer back to board (probably useless and can be removed)
  - index
- Piece
  - Pointer to player
  - Movement/Eval function pointers
    - legal moves
    - controlled squares
    - potential
  - type id
  - value of piece?
  - pointer back to square (possibly useless)
- Player
  - really only exists to have a list of pieces/locations so I don't have to iterate over the entire board


### Functionality
- Position
  - Get position from FEN
- Evaluation
  - Eval CURRENT board state - no look arounds
  - Needs to recognize repetition
- Depth search
  - Evaluate all possible moves to a certain depth
    - Consider repetitions/move order
    - Cut off once position is no longer dynamic / position is much different from other options
  - Evaluate to the end of all capture chains
  - min/max from end of all branches back to main position
