#include "player.hpp"
#include <climits>
//made a change
// testing - mn
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     
     //initialize board
     board = Board();
     player_side = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
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
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     Side oppSide = WHITE;
     if(player_side == WHITE){
		 oppSide = BLACK; 
	 }
     board.doMove(opponentsMove, oppSide);
     
	 Move *highest_scoring = nullptr;
	 Move *player_move;
	 
	 int highest_score = INT_MIN;
	 for(int i = 0; i < 8; i++){
		 for(int j = 0; j < 8; j++){
			 player_move = new Move(i, j);
			 if(board.checkMove(player_move, player_side)){
				 int score = board.count(player_side) - board.count(oppSide);
				 //corner
				 if((i==0 && j==0) || (i == 7 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 7)){
					score *= 3; 
				 // quadrant 1
				 }else if((i == 0 && j == 1 )|| (i == 1 && (j == 0 || j == 1))){
					 score *= -3;
				// quadrant 2
				 } else if((i == 6 && (j == 0 || j == 1)) || (i == 7 && j == 1)){
					 score *= -3;
				 //quadrant 3
				 }else if((i == 0 && j == 6 )|| (i == 1 && (j == 6 || j == 7))){
					 score *= -3;
					 // quadrant 4
				 }else if((i == 6 && (j == 6 || j == 7) )|| (i == 7 && j == 6)){
					 score *= -3;
				 }
				 
				 if(score > highest_score){
					 highest_scoring = player_move;
					 highest_score = score;
				 }
			 }
			 
		 }
		 
		 
	 }
	 
	//cerr << "move: " << highest_scoring->x << ", " << highest_scoring->y << endl;
	board.doMove(highest_scoring, player_side);
    return highest_scoring;
     
    
}
