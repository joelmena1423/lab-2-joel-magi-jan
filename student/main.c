#include "main.h"

void run_game(Session *session){
    Game *game = &session->current_game;

    do{
        print_session(session);

        Option game_option;
        do{
            print_options();
            printf("[INFO] Enter a game option [%d-%d]: ", MOVE_UP, QUIT_GAME);
            game_option = read_int();
        }while(!is_valid_option(game_option));
        
        switch(game_option){
            case MOVE_UP:
            case MOVE_RIGHT:
            case MOVE_DOWN:
            case MOVE_LEFT:
                game->state = move(game->state, game_option);
                game->score++;
                break;
            case SHOW_BEST_MOVE:
                // ToDo in Lab 3
                break;
            case QUIT_GAME:
                printf("[INFO] QUIT GAME!\n");
                return;
        }
        
    }while(!is_terminal(game->state));
    
    new_game_score(session);
    print_session(session);
    printf("[INFO] LEVEL COMPLETED!!!\n");
}

void new_game(Session *session){
    restart_session_game(session);
    choose_level(&(session->current_game));
    run_game(session);
}

void save_game(Session *session){
    char filename[100]; // array que emagatzema una memoria
    FILE * f; //punter que apunta a un fitxer obert
    scanf("%s", filename);   
    f = fopen(filename, "w"); //obri el fitxer 
    if (f == NULL){ //agafa l'error de fopen, si no hi ha res es null i no retorna res, voldrà dir que el fitxer no s'ha pogut obrir.
        return;
    }
    fprintf(f, "Score:  %d\n", session-> current_game.score);
    fprintf(f, "Level: %d\n", session -> current_game.level);  //el fprintf permet guardar les dades dins el fitxer
    fprintf(f,"State: \n");
    fprintf(f, "Rows: %d\n", session -> current_game.state.rows);
    fprintf(f, "Columns: %d\n", session -> current_game.state.columns);

    for (int i = 0; i < session-> current_game.state.rows; i++) {            //guarda el taulell del joc
        for (int j = 0; j < session-> current_game.state.columns; j++) {
            fprintf(f, "%c", session-> current_game.state.grid[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);  // ToDo - Lab 2
}


void load_game(Session *session) {

    char filename[100]; // allibera espai per al fitxer
    printf("Enter file name to load: "); //demana al usuari quin fitxer hem de carregar
    scanf("%s", filename);

    FILE *file = fopen(filename, "r"); // Aquesta funció ens permet accedir al fitxer en mode lectura

    if (file == NULL) {                     //controlem que no hi hagi problemes i que els fitxer estigui
        printf("Error opening file.\n");    // correctament creat si no ho està sortiria
        return;
    }
    free_game(&session->game);

    Game *g = &session->game; //creem un punter anomenat g que ens permet accedir de manerà més àgil al game que hi ha dins sessions al data struct.

    fscanf(file, "Score: %d\n", &g->score); //amb scanf permet llegir el score, el lvl i el state.
    fscanf(file, "Level: %d\n", &g->level);
    fscanf(file, "State:\n");

    int rows, columns; //establim dues variables sense reservar memoria

    fscanf(file, "rows: %d\n", &rows); 
    fscanf(file, "columns: %d\n", &columns);

    g->state.rows = rows;
    g->state.columns = columns;

    g->state.grid = make_grid(rows, columns);

    for (int i = 0; i < rows; i++) {        //recorrem cada fila i analitzem cada caracter i el que fa es guardarlo en la posició adequada.
        for (int j = 0; j < columns; j++) {
            fscanf(file, "%c", &g->state.grid[i][j]);
        }
        fscanf(file, "\n");
    }
fclose(file); // sortim del fitxer

printf("Game loaded successfully.\n");
}

void resume_game(Session *session) {

    Game *g = &session->game; //manera d'accedir al game que hi ha dins els session, utilitzat previament a la la funció anterior.

    if (g->state.grid == NULL) {       //Aquesta funció ens permet analitzar l'estat de la graella, si es nula 
        printf("No game to resume.\n"); //ens dira simplement que no hi hagut cap sessió de joc
        return;
    }

    if (is_terminal(&g->state)) {     //En aquest cas comprovem si segueix activa o no; ja que si la comprovació
        printf("Game already finished.\n"); //ens diu que el joc esta acabat no hem de continuar.
        return;
    }

    play_game(session);  // mateixa funció que uses a New Game
}
    // ToDo - Lab 2  	

void print_menu(){
    printf("[INFO] Menu options:\n");
    printf("\t1. New game.\n");  // LAB1 - basic lab for creating grid and moves
    printf("\t2. Save game.\n"); // LAB2 - Writing file
    printf("\t3. Load game.\n"); // LAB2 - Reading file
    printf("\t4. Resume game.\n"); // LAB2 - Continue game after reading file
    printf("\t5. Exit.\n");  // Free all reserved memory!
}


void run(Session *session){
    int option;
    do{
        print_menu();
        do{
            printf("[INFO] Enter an integer [%d-%d]: ", NEW_GAME, EXIT);
            option = read_int();
        }while(option < NEW_GAME || option > EXIT);

        switch (option){
        case NEW_GAME:
            new_game(session);
            break;
        case SAVE_GAME:
            save_game(session);
            break;
        case LOAD_GAME:
            load_game(session);
            break;
        case RESUME_GAME:
            resume_game(session);
            break;
        case EXIT:
            break;
        }
    }while(option != EXIT);
    
    // Lab 2
    free_session(session);
}

int main(){
    Session session;
    init_session(&session);
    run(&session);
}
