#include "player.hpp"
#include <climits>
//made a change
// testing - mn

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
 int MINIMAX_DEPTH = 2;
 Board *temp_board;
Player::Player(Side side) 
{
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
     
     //initialize board
     board = Board();
     player_side = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() 
{
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
 
Move *minimax(Move *currentMove, int msLeft, int depth){
	// Assign sides to each player
     Side oppSide = WHITE;
     if(player_side == WHITE)
     {
		 oppSide = BLACK; 
	 }
	 
	//base case: if depth is MINIMAX_DEPTH - return move with lowest score
	if(depth == MINIMAX_DEPTH){
		int max_score = INT_MIN;
		Move *max_score_move = nullptr;
		vector<Move *> possible_moves;
		 for(int i = 0; i < 8; i++)
		{
		 for(int j = 0; j < 8; j++)
			{
				move = new Move(i, j);
			 
				// If the move is valid
				if(board.checkMove(move, player_side))
					{
						possible_moves.push_back(move);	 
				 
					}
			}		
		}
		
		for(int i = 0; i < possible_moves.size(); i++){
			//Board *temp_board = board.copy();
			temp_board->doMove(possible_moves[i], oppSide);
				 
				 // Assign a base score based on the difference between 
				 // number of pieces on the board after the move has been made
			int score = temp_board->count(player_side) - temp_board->count(oppSide);
			if(score > min_score){
				max_score = score;
				max_score_move = move;
			}
		}
		
		return min_score_move;
	}

	 
     
     // Initialize variables
	
	 vector<Move *> possible_moves;
	 // Iterate through all board cells to get all possible player moves
	 for(int i = 0; i < 8; i++)
	 {
		 for(int j = 0; j < 8; j++)
		 {
			 player_move = new Move(i, j);
			 
			 // If the move is valid
			 if(board.checkMove(player_move, player_side))
			 {
				 possible_moves.push_back(player_move);	 
				 
				}
	}	
		
	}
	
	for(int i = 0; i < possible_moves.size(); i++){
		Board *temp_board = new Board();
		temp_board.doMove(possible_moves[i], player_side);
		//int score = temp_board->count(player_side) - temp_board->count(oppSide);
		minimax(possible_moves[i], msLeft, depth + 1);
		
	}
}

Move *Player::doMove(Move *opponentsMove, int msLeft) 
{

     // Assign sides to each player
     Side oppSide = WHITE;
     if(player_side == WHITE)
     {
		 oppSide = BLACK; 
	 }
	 
	 // Process opponent's move
     board.doMove(opponentsMove, oppSide);
     
     // Initialize variables
	 Move *highest_scoring = nullptr;
	 Move *player_move;
	 int highest_score = INT_MIN;
	 
	 // Iterate through all board cells
	 for(int i = 0; i < 8; i++)
	 {
		 for(int j = 0; j < 8; j++)
		 {
			 player_move = new Move(i, j);
			 
			 // If the move is valid
			 if(board.checkMove(player_move, player_side))
			 {
				 // Create temp board to simulate the move
				 Board *temp_board = board.copy();
				 temp_board->doMove(player_move, player_side);
				 
				 // Assign a base score based on the difference between 
				 // number of pieces on the board after the move has been made
				 int score = temp_board->count(player_side) - temp_board->count(oppSide);
				 
				 // Apply multipliers based on the cell location on the board
				 // and how favorable a move at that location would be.
				 
				 // Corner squares are most preferable since these can never be captured
				 if((i==0 && j==0) || (i == 7 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 7))
				 {
					score *= 5; 
				 }
				 // Squares adjacent to corners are worse - negative multiplier
				 // quadrant 1
				 else if((i == 0 && j == 1 )|| (i == 1 && (j == 0 || j == 1)))
				 {
					 score *= -3;
				 } 
				 // quadrant 2
				 else if((i == 6 && (j == 0 || j == 1)) || (i == 7 && j == 1))
				 {
					 score *= -3;
				 }
				 // quadrant 3
				 else if((i == 0 && j == 6 )|| (i == 1 && (j == 6 || j == 7)))
				 {
					 score *= -3;
				 }
				 // quadrant 4
				 else if((i == 6 && (j == 6 || j == 7) )|| (i == 7 && j == 6))
				 {
					 score *= -3;
				 }
				 
				 // Squares at the edge of the board can only be captured
				 // by other edge pieces - slightly favorable
				 else if((i == 0) || (i == 7) || (j == 0) || (j == 7))
				 {
					 score *= 3;
				 }

				 // Set the highest score to this possible move
				 if(score > highest_score)
				 {
					 highest_scoring = player_move;
					 highest_score = score;
				 }
				 
				 // Clean up
				 delete temp_board;
			 }
		 }
	 }
	 
	//cerr << "move: " << highest_scoring->x, << ", " << highest_scoring->y << endl;
	board.doMove(highest_scoring, player_side);
	
    return highest_scoring;
}
