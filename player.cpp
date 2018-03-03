#include "player.hpp"
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
     //pick random x and random y
     //int x, y;
     //Move *player_move;
   
	 Move *highest_scoring;
	 //Move *player_move;
	 int highest_score;
	 for(i = 0; i < 8; i++){
		 for(j = 0; j < 8; j++){
			 Move player_move = Move(i, j);
			 if(board.checkMove(player_move)){
				 
			 }
			 
		 }
		 
		 
	 }
    
    /* if(board.hasMoves(player_side)){
		do{
			x = rand() % 8 + 1;
			y = rand() % 8 + 1;
			player_move = new Move(x, y);
		}while(!board.checkMove(player_move, player_side));
		
		return player_move;
	}
	*/
     
    return nullptr;
}
