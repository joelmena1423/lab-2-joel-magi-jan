#include "game.h"


/**** LAB 1 - given functions ****/
void print_options(){
    printf("Options:\n");
    printf("\t%d. Up | %d. Right | %d. Down | %d. Left |\n", MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT);
    printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
    printf("\t%d. Quit game\n", QUIT_GAME);
}

bool is_valid_option(Option o){
    return ((MOVE_UP <= o) && (o<=QUIT_GAME));
}

bool set_level(State *s, unsigned level){
   switch(level){
    case 1:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 3;
        s->columns = 8;
        s->grid = make_grid(s->rows, s->columns+1);
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#.A.B.G#");
        strcpy(s->grid[2], "########");
        break;
    case 2:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 5;
        s->columns = 8;
        s->grid = make_grid(s->rows, s->columns+1);
        strcpy(s->grid[0], "########");
        strcpy(s->grid[1], "#....###");
        strcpy(s->grid[2], "#.B#.#A#");
        strcpy(s->grid[3], "#..B.GG#");
        strcpy(s->grid[4], "########");
        break;
    case 3:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 7;
        s->columns = 7;
        s->grid = make_grid(s->rows, s->columns+1);
        strcpy(s->grid[0], "#######");
        strcpy(s->grid[1], "###G###");
        strcpy(s->grid[2], "###B###");
        strcpy(s->grid[3], "#GBABG#");
        strcpy(s->grid[4], "###B###");
        strcpy(s->grid[5], "###G###");;
        strcpy(s->grid[6], "#######");
        break;
    case 4:
        printf("[INFO]: loading level #%d\n", level);
        s->rows = 6;
        s->columns = 8;
        s->grid = make_grid(s->rows, s->columns+1);
        strcpy(s->grid[0], "#######.");
        strcpy(s->grid[1], "#.B.AG##");
        strcpy(s->grid[2], "#.XXG..#");
        strcpy(s->grid[3], "#....B.#");
        strcpy(s->grid[4], "#..#####");
        strcpy(s->grid[5], "####....");
        break;
    default:
        printf("[ERROR]: level not found!\n");
        return false;
   };
   
   return true;
}

void init_game(Game *game){
    game->score = 0;
    game->level = 0;
    // LAB 1
    /*
    game->state.rows = MAX_ROWS;
    game->state.columns = MAX_COLUMNS;
    for(int i=0; i<MAX_ROWS; ++i)
        for(int j=0; j<MAX_COLUMNS; ++j)
            game->state.grid[i][j] = '.';
    */
    // LAB 2
    game->state.rows = 0;
    game->state.columns = 0;
    game->state.grid = NULL;
}

void choose_level(Game *game){
    game->score = 0;    
    do{
        printf("[INFO] Choose the level [1-4]: ");
        game->level = read_int();
    }while(!set_level(&game->state, game->level));
}


/**** LAB 1 - functions to program (start here) ****/
void print_state(State s){
    for(int i=0; i<s.rows; i++){ //recorre les files
        for(int j = 0; j < s.columns; j++){ //recorre les columnes
            printf("%c", s.grid[i][j]); //imprimeix el caracter que hi ha a la posició i,j del tauler, que pot ser una paret, un espai buit, una caixa, etc.
        }
        printf("\n"); //imprimeix un salt de línia després d'imprimir cada fila del tauler, per tal de que el tauler es vegui com una matriu.
    }
}

void print_game(Game game){
    printf("Puntuació: %d\n", game.score); //imprimeix la puntuació
    printf("Nivell: %d\n", game.level); //imprimeix el nivell
    print_state(game.state);  //imprimeix el tauler
}


bool is_terminal(State s){
    int i, j;    
    for(i = 0; i < s.rows; i++){ // recorre les files
        for(j = 0; j < s.columns; j++){ // recorre les columnes
            if(s.grid[i][j] == 'B') //si hi ha una caixa que no està en una posició de meta, el joc no ha acabat
                return false;
        }
    }
    return true;  //si no hi ha cap caixa que no estigui en una posició de meta, el joc ha acabat
}

State move(State s, Option o){
	int dr = 0, dc = 0; //representen el canvi de coordenades de la posició de l'agent segons la direcció del moviment
    switch(o){ //segons la direcció del movimient, s'asigna un valor a dr i dc per indicar el canvi de les coord 
        case MOVE_UP:  //cap amunt, la fila de l'agent disminuirà en 1 i la columna no canviarà
            dr = -1;
            break;
        case MOVE_RIGHT://cap a la dreta, la fila de l'agent no canviarà i la columna augmentarà en 1
            dc = 1;
            break;
        case MOVE_DOWN://cap avall, la fila de l'agent augmentarà en 1 y la columna no canviarà
            dr = 1;
            break;
        case MOVE_LEFT://cap a l'esquerra, la fila de l'agent no canviarà y la columna disminuirà en 1
            dc = -1;
            break;
        default:   //si l'opció no és un moviment vàlid, es retorna el mateix estat sense canvis
            return s;
    }
    int r = -1;   //inicialitza les coordenades de la posició de l'agent a -1, -1, que és un valor no vàlid per al tauler
    int c = -1;  
    for(int i = 0; i < s.rows; i++){ //recorre les files del tauler per trobar la posició actual de l'agent
        for(int j = 0; j < s.columns; j++){ //recorre las columnes del tauler per trobar la posición actual de l'agent
            if(s.grid[i][j] == 'A' || s.grid[i][j] == 'Y'){ //si troba el caràcter 'A' o 'Y', s'asignen les coord a r i c
                r = i;
                c = j;
            }
        }
    }

    int nr = r + dr; //calcula les coordenades de la posició a la que es vol moure l'agent
    int nc = c + dc;

    int nnr = r + 2*dr; //calcula les coordenades de la posició a la que es vol moure l'agent si hi ha una caixa en el camí
    int nnc = c + 2*dc;

    if( nr < 0 || nr >= s.rows || nc < 0 || nc >= s.columns) //si la posició a la que es vol moure l'agent està fora del tauler, retorna el mateix estat
        return s;

    char next = s.grid[nr][nc]; //guarda el caràcter que hi ha a la posició a la que es vol moure l'agent

    if(next == '.' || next == 'G'){ //si la posició a la que es vol moure l'agent és un espai buit o una posició de meta, es mou l'agent a aquesta posició
        if(s.grid[r][c] == 'Y') //si l'agent està en una posició de meta, es deixa un 'G' a la posició anterior, sinó es deixa un '.' a la posició anterior
            s.grid[r][c] = 'G';
        else
            s.grid[r][c] = '.';
        if(next == 'G')       //si la posició a la que es vol moure l'agent és una posició de meta, es deixa un 'Y' a aquesta posició, sinó es deixa un 'A'
            s.grid[nr][nc] = 'Y';
        else
            s.grid[nr][nc] = 'A';

        return s;
    }
    if(next == 'B' || next == 'X'){ //si la posició a la que es vol moure l'agent és una caixa, es comprova si es pot empenyer la caixa a la següent posició
        if(nnr < 0 || nnr >= s.rows || nnc < 0 || nnc >= s.columns) //si la posició a la que es vol moure la caixa está fora del tauler, retorna el mateix estat
            return s;

        char next2 = s.grid[nnr][nnc]; //guarda el caràcter que hi ha a la posició a la que es vol moure la caixa
            if(next2 == 'G') //si la posició a la que es vol moure la caixa és una posició de meta, es mou la caixa a aquesta posició i es mou l'agent a la posició anterior de la caixa
                s.grid[nnr][nnc] = 'X';
            else
                s.grid[nnr][nnc] = 'B';
            

            if(next == 'X') //si la posició a la que es vol moure el agent és una caixa que ya está en una posició de meta, es deixa un 'G' a la posició anterior de la caixa, sinó se deixa un '.' a la posició anterior de la caixa
                s.grid[nr][nc] = 'Y';
            else
                s.grid[nr][nc] = 'A';
            
            if(s.grid[r][c] == 'Y') //si el agent está en una posición de meta, es deixa una 'G' a la posició anterior de l'agent, sinó es deixa un '.' a la posició anterior
                s.grid[r][c] = 'G';
            else
                s.grid[r][c] = '.';

            return s;//si es pot moure la caixa, es mou l'agent a la posició anterior de la caixa i es retorna el nou estat del tauler
    }
    return s; //si la posició a la que es vol moure l'agent és una paret o qualsevol altre caràcter que no sigui un espai buit, meta o caixa, retorna el mateix estat sense canvis
}

/**** LAB 1 - functions to program (end here) ****/



/**** LAB 2 - functions to program (start here) ****/
void free_state(State *s){
    // ToDo - Lab 2
}

void free_game(Game *g){
    // ToDo - Lab 2
}

char** make_grid(int rows, int columns){
    // ToDo - Lab 2
    return NULL;

}
/**** LAB 2 - functions to program (end here) ****/

