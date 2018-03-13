#include "player.hpp"
#include <climits>
#include <vector>
using namespace std;
//made a change
// testing - mn

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
 
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

Move *Player::minimax_iterative(){
	
	// Assign sides to each player
     Side oppSide = WHITE;
     if(player_side == WHITE)
     {
		 oppSide = BLACK; 
	 }
	
	int max_score = INT_MIN;
	Move *max_score_move = nullptr;
	
	vector<Move *> possible_moves;
	for(int i = 0; i < 8; i++)
		{
		 for(int j = 0; j < 8; j++)
			{
				Move *move = new Move(i, j);
			 
				// If the move is valid
				if(board.checkMove(move, player_side))
					{
						possible_moves.push_back(move);	 
				 
					}
			}		
		}
		
		if(possible_moves.size() == 1){
			board.doMove(possible_moves[0], player_side);
			return possible_moves[0];
			
		}
		cerr << "Num possible move: " << possible_moves.size() << endl;

	
	for(unsigned int i = 0; i < possible_moves.size(); i++){
		Board *temp_board = board.copy();
		 temp_board->doMove(possible_moves[i], player_side);
		 int depth_1_score = temp_board->count(player_side) - temp_board->count(oppSide);
		 
		 vector<Move *> possible_opp_moves;
		 for(int i = 0; i < 8; i++)
		{
		 for(int j = 0; j < 8; j++)
			{
				Move *opp_move = new Move(i, j);
			 
				// If the move is valid
				if(temp_board->checkMove(opp_move, oppSide))
					{
						possible_opp_moves.push_back(opp_move);	 
				 
					}
			}		
		}
				cerr << "Num possible opp move: " << possible_opp_moves.size() << endl;

		for(unsigned int j = 0; j < possible_opp_moves.size(); j++){
			Board *temp2 = temp_board->copy();
			temp2->doMove(possible_opp_moves[j], oppSide);
			int depth_2_score = temp2->count(player_side) - temp2->count(oppSide);
			if(depth_1_score + depth_2_score > max_score){
				max_score = depth_1_score + depth_2_score;
				max_score_move = possible_moves[i];
			}
			
			delete temp2;
			
			
		}
		
		delete temp_board;
	}
	
	//cerr << "move: " << max_score_move->x << ", " << max_score_move->y << endl;
	
	board.doMove(max_score_move, player_side);
	return max_score_move;
	
}

/*
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
*/


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
     
     if(testingMinimax){
		 
		 return minimax_iterative();
	 }
	 else
	 {
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
}
