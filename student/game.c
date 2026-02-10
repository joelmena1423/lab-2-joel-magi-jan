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
    for(int i=0; i<s.rows; i++){
        for(int j = 0; j < s.columns; j++){ 
            printf("%c", s.grid[i][j]); 
        }
        printf("\n"); 
    }
}

void print_game(Game game){
    printf("Puntuació: %d\n", game.score);
    printf("Nivell: %d\n", game.level);
    print_state(game.state);
}


bool is_terminal(State s){
    int i, j;    
    for(i = 0; i < s.rows; i++){
        for(j = 0; j < s.columns; j++){ 
            if(s.grid[i][j] == 'B')
                return false;
        }
    }
    return true;
}

State move(State s, Option o){
    int dr = 0, dc = 0; 
    switch(o){ 
        case MOVE_UP:
            dr = -1;
            break;
        case MOVE_RIGHT:
            dc = 1;
            break;
        case MOVE_DOWN:
            dr = 1;
            break;
        case MOVE_LEFT:
            dc = -1;
            break;
        default:   
            return s;
    }

    int r = -1;
    int c = -1;  
    for(int i = 0; i < s.rows; i++){ 
        for(int j = 0; j < s.columns; j++){
            if(s.grid[i][j] == 'A' || s.grid[i][j] == 'Y'){ 
                r = i;
                c = j;
            }
        }
    }
	
    int nr = r + dr;
    int nc = c + dc;

    int nnr = r + 2*dr;
    int nnc = c + 2*dc;

    if( nr < 0 || nr >= s.rows || nc < 0 || nc >= s.columns)
        return s;

    char next = s.grid[nr][nc];

    if(next == '.' || next == 'G'){
        if(s.grid[r][c] == 'Y')
            s.grid[r][c] = 'G';
        else
            s.grid[r][c] = '.';
        if(next == 'G') 
            s.grid[nr][nc] = 'Y';
        else
            s.grid[nr][nc] = 'A';

        return s;
    }
    if(next == 'B' || next == 'X'){ 
        if(nnr < 0 || nnr >= s.rows || nnc < 0 || nnc >= s.columns)
            return s;

        char next2 = s.grid[nnr][nnc];
            if(next2 == 'G') 
                s.grid[nnr][nnc] = 'X';
            else
                s.grid[nnr][nnc] = 'B';
            
            if(next == 'X') 
                s.grid[nr][nc] = 'Y';
            else
                s.grid[nr][nc] = 'A';
            
            if(s.grid[r][c] == 'Y') 
                s.grid[r][c] = 'G';
            else
                s.grid[r][c] = '.';

            return s;
    }
    return s;
}

/**** LAB 1 - functions to program (end here) ****/



/**** LAB 2 - functions to program (start here) ****/
void free_state(State *s){
    // ToDo - Lab 2
}

void free_game(Game *g){
    g -> score = 0; // resetegem score
    g -> level = 0; // resetegem level
    free(&g -> state); // alliberem la memòria del state
}

char** make_grid(int rows, int columns){
    char **matrix = malloc(columns *sizeof(char*)); // reservem memòria per les columnes
    for(int i = 0; i < columns; i++){ // recorrem les columnes
        matrix[i] = malloc(rows * sizeof(char)); // reservem memòria per les files de cada columna
    }
    return matrix; // retornem la matriu
}
/**** LAB 2 - functions to program (end here) ****/

