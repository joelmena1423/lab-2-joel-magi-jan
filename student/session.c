#include "session.h"

// LAB 1 - functions 
void restart_session_game(Session *session){
    //OBJECTIU DE LA FUNCIÓ --> Finalitzar la partida i reiniciar-la de nou
    if(session != NULL){        //OBSERVEM SI LA SESSIÓ ACTUAL JA ESTÀ EN PARTIDA O NO (SI EN CARA NO HA COMENÇAT NO CAL FINALITZAR-LA, SINÓ QUE INICIAR-LA)
        free_session(&session);  //FINALITZEM LA PARTIDA ACTUAL
    }
    init_game(&session ->current_game); //INICIEM LA PARTIDA DE NOU
}


void init_session(Session *session){
    //ACTUALITZAR
    for(int level = 0; level < MAX_LEVELS; level++){
        session ->best_score[level] = 0;
    }
    init_game(&session ->current_game);
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
	
    //OBJECTIU HA DE SER ALLIBERAR LA MEMÒRIA OCUPADA PER AQUESTA PARTIDA
    //s->current_game.state.grid;

    if(s != NULL){
        free_game(&(s->current_game));
    }

}
