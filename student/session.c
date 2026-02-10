#include "session.h"

// LAB 1 - functions 
void restart_session_game(Session *session){
   init_game(&session ->current_game);
}

void init_session(Session *session){
    for(int level = 0; level < MAX_LEVELS; level++){
        session ->best_score[level] = 0;
    }
    restart_session_game(session);
}

void print_session(Session *session){
     unsigned level = session -> current_game.level;
    printf("Millor puntuació: %d\n", session-> best_score[level]);
    print_game(session -> current_game);
}

void new_game_score(Session *session){
    unsigned level = session -> current_game.level;
    int score = session -> current_game.score;
    if(session -> best_score[level] == 0 || score < session -> best_score[level]){ 
        session -> best_score[level] = score;
    }
}

// LAB 2 - functions
void free_session(Session *s){
	// ToDo - Lab 2
}
