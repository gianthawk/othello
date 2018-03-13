#include "player.hpp"
#include <climits>
#include <vector>
//made a change
// testing - mn

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
 int MINIMAX_DEPTH = 5;
 Board *temp_board;
Player::Player(Side side) 
{
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;
     
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
 * The minimax function implements a recursive algorithm for selecting
 * the Othello move that will maximize our eventual score, where the
 * base case is a previously selected depth of the decision tree, and
 * the recursive step repeatedly calls the minimax function at 
 * increasing depths. This also incorporates our previous heuristic 
 * algorithm based on Othello strategy.
 */
 
Move *Player::minimax(Move *currentMove, int msLeft, int depth){
	
	//Assign sides to each player
    Side oppSide = WHITE;
    if(player_side == WHITE)
    {
		 oppSide = BLACK; 
	}
	 
	// base case: if depth is MINIMAX_DEPTH - return move with lowest score
	if(depth == MINIMAX_DEPTH)
	{
		int min_score = INT_MAX;
		Move *min_score_move = nullptr;
		vector<Move *> possible_moves;
		Move *temp_move;
		
		// Get all possible moves
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				 temp_move = new Move(i, j);
			 
				// If the move is valid
				if(board.checkMove(temp_move, player_side))
				{
					possible_moves.push_back(temp_move);	 
				}
			}		
		}
		
		// use heuristic to return the move with minimum score
		for(unsigned int i = 0; i < possible_moves.size(); i++)
		{
			Board *temp_board = board.copy();
			temp_board->doMove(possible_moves[i], player_side);
				 
			// Assign a base score based on the difference between 
			// number of pieces on the board after the move has been made
			int score = temp_board->count(player_side) - temp_board->count(oppSide);
			
			int move_x = possible_moves[i]->x;
			int move_y = possible_moves[i]->y;
			
			// Apply multipliers based on the cell location on the board
			// and how favorable a move at that location would be.
				 
			// Corner squares are most preferable since these can never be captured
			if((move_x == 0 && move_y ==0) || 
			(move_x == 7 && move_y == 0) || 
			(move_x == 0 && move_y == 7) || 
			(move_x == 7 && move_y == 7))
			{
				score *= 5; 
			}
			// Squares adjacent to corners are worse - negative multiplier
			// quadrant 1
			else if((move_x == 0 && move_y == 1 )|| 
			(move_x == 1 && (move_y == 0 || move_y == 1)))
			{
				score *= -3;
			} 
			// quadrant 2
			else if((move_x == 6 && (move_y == 0 || move_y == 1)) || 
			(move_x == 7 && move_y == 1))
			{
				score *= -3;
			}
			// quadrant 3
			else if((move_x == 0 && move_y == 6 ) || 
			(move_x == 1 && (move_y == 6 || move_y == 7)))
			{
				score *= -3;
			}
			// quadrant 4
			else if((move_x == 6 && (move_y == 6 || move_y == 7) ) ||
			 (move_x == 7 && move_y == 6))
			{
				score *= -3;
			}
				 
			// Squares at the edge of the board can only be captured
			// by other edge pieces - slightly favorable
			else if((move_x == 0) || (move_x == 7) || (move_y == 0) || (move_y == 7))
			{
				score *= 3;
			}
			
			if(score < min_score)
			{
				min_score = score;
				min_score_move = possible_moves[i];
			}
		}
		
		return min_score_move;
	}

	 else // not base case
	 
	 {
		// Initialize variables
		vector<Move *> possible_moves;
		
		// Iterate through all board cells to get all possible player moves
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				Move *player_move = new Move(i, j);
			 
				// If the move is valid
				if(board.checkMove(player_move, player_side))
				{
					possible_moves.push_back(player_move);	 
				 
				}
			}	
		
		}
	
		int max_score = INT_MIN;
		unsigned int max_move_index = 0;
		
		// Use heuristic to return the move with maximum score
		// Iterate thru all possible moves
		for(unsigned int i = 0; i < possible_moves.size(); i++)
		{
			Board *temp_board = board.copy();
			
			// Recursive call at depth + 1
			temp_board->doMove(minimax(possible_moves[i], msLeft, depth + 1), this->player_side);
			
			int score = temp_board->count(player_side) - temp_board->count(oppSide);
			
			int move_x = possible_moves[i]->x;
			int move_y = possible_moves[i]->y;
			
			// Apply multipliers based on the cell location on the board
			// and how favorable a move at that location would be.
				 
			// Corner squares are most preferable since these can never be captured
			if((move_x == 0 && move_y ==0) || 
			(move_x == 7 && move_y == 0) || 
			(move_x == 0 && move_y == 7) || 
			(move_x == 7 && move_y == 7))
			{
				score *= 5; 
			}
			// Squares adjacent to corners are worse - negative multiplier
			// quadrant 1
			else if((move_x == 0 && move_y == 1 )|| 
			(move_x == 1 && (move_y == 0 || move_y == 1)))
			{
				score *= -3;
			} 
			// quadrant 2
			else if((move_x == 6 && (move_y == 0 || move_y == 1)) || 
			(move_x == 7 && move_y == 1))
			{
				score *= -3;
			}
			// quadrant 3
			else if((move_x == 0 && move_y == 6 ) || 
			(move_x == 1 && (move_y == 6 || move_y == 7)))
			{
				score *= -3;
			}
			// quadrant 4
			else if((move_x == 6 && (move_y == 6 || move_y == 7) ) ||
			 (move_x == 7 && move_y == 6))
			{
				score *= -3;
			}
				 
			// Squares at the edge of the board can only be captured
			// by other edge pieces - slightly favorable
			else if((move_x == 0) || (move_x == 7) || (move_y == 0) || (move_y == 7))
			{
				score *= 3;
			}
			
			// Set the highest score to this possible move
			if(score > max_score)
			{
				max_move_index = i;
				max_score = score;
			}
				 
			// Clean up
			delete temp_board;
		}
		
		if (depth == 1) 
		{
            board.doMove(possible_moves[max_move_index], player_side);
            return possible_moves[max_move_index];
        }

        else 
        {
            return possible_moves[max_move_index];
        }	
		
	}
	
	return NULL;
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
     
     if(testingMinimax)
     {
		return minimax(opponentsMove, msLeft, 1);
	 }
     
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
