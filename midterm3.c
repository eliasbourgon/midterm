#include "stdio.h"
#include "stdlib.h"

#define SYMBOL_FOR_EMPTY ' '
#define SYMBOL_FOR_CROSS 'X'
#define SYMBOL_FOR_ZERO 'O'

int current_turn = 1;
//impair: joueur 1, pair: joueur 2 ou bot

struct Position {
     int row;
     int col;
};




void init_board(int height, int width, char board[height][width]); //5pt
int is_valid_board(int height, int width); //5pt
int is_valid_game(int n_symbols2win, int height, int width); //5pt
void visualize_board(int height, int width, char board[height][width]); //10pt
int is_valid_pos( struct Position pos, int height, int width, char board[height][width]); //5pt
int did_player_win(struct Position pos, int n_symbols2win, int height, int width, char board[height][width]); //15 pt
struct Position get_bot_pos(int height, int width, char board[height][width]); //10pt
struct Position step(int height, int width, char board[height][width], int play_with_pc); //15pt
int is_game_winnable(int n_symbols2win, int height, int width, char board[height][width]);//15pt
void play();//15pt

int main(){
     play();
     return 0;
}

//start: play
void play(){
     
     char play_bot;
     int play_with_pc;
     int height, width, n_symbols2win;
     current_turn=1;
     play_with_pc=-1;

     printf("Please input the height and the width of the board:\n");
     scanf("%d %d",&height, &width);
     while(is_valid_board(height, width)==0){
          printf("Please input the height and the width of the board:\n");
          scanf("%d %d",&height, &width);
     }
     char board[height][width];
     printf("Please input the number of consecutive symbols to win:\n");
     scanf("%d",&n_symbols2win );
     while(is_valid_game(n_symbols2win, height, width)==0){
          printf("Please input the number of consecutive symbols to win:\n");
          scanf("%d",&n_symbols2win);
     }
     printf("Do you want to play with a bot? Write ‘y’ for yes and ‘n’ for no:\n");
     
     scanf("%s", &play_bot);
     if (play_bot=='y'){
          play_with_pc=1;
     }
     else if (play_bot=='n'){
          play_with_pc=0;
     }
     while (play_with_pc==-1)
     {
     printf("Wrong input!\n");
     printf("Do you want to play with a bot? Write ‘y’ for yes and ‘n’ for no:\n");
     
     scanf("%s", &play_bot);
     if (play_bot=='y'){
          play_with_pc=1;
     }
     else if (play_bot=='n'){
          play_with_pc=0;
     }
     }
     
     
     init_board(height, width,board);
     visualize_board(height, width, board);
     struct Position pos=step(height, width, board, play_with_pc);
     board[pos.row][pos.col]=SYMBOL_FOR_CROSS;
     visualize_board(height, width, board);
     
     while (did_player_win(pos, n_symbols2win, height, width, board)!=1 && is_game_winnable(n_symbols2win, height, width, board)==1){
          pos= step(height, width, board, play_with_pc);
          if (pos.row<0){
               break;
          }
          
          else if(current_turn % 2==0){
               board[pos.row][pos.col]=SYMBOL_FOR_CROSS;
          }
          else {
               board[pos.row][pos.col]=SYMBOL_FOR_ZERO;}
          visualize_board(height, width, board);
     }
     if (did_player_win(pos, n_symbols2win, height, width, board)==1){
          if (board[pos.row][pos.col]==SYMBOL_FOR_CROSS){
               printf("Congratulations! Player #1 won!\n");
          }
          else {
               printf("Congratulations! Player #2 won!\n" );
          }
     }
     else if (is_game_winnable(n_symbols2win, height, width, board)==0){
          printf("Thank you for playing, it is a tie!\n");
     }
     char respons='y';
     printf("Do you want to play again? Write ‘y’ for yes and ‘n’ for no:\n");
     scanf("%s", &respons);
     
     if (respons=='y'){
          play();
     }
     else {
          
     }

}
//end: play





//start: init_board
void init_board(int height, int width, char board[height][width]) {
     for(int i=0; i<height;i++){
          for (int j=0; j<width; j++){
               board[i][j]=SYMBOL_FOR_EMPTY;
          }
     }
     // chaque case tu tableau initialisee comme vide
}
//end: init_board

//start: is_valid_board
int is_valid_board(int height, int width){
     if(height<3|| width<3){
          printf("Wrong input!\n");
          return 0;}
     else {
          return 1;
     }
     //largeur et hauteur du tableau doit etre superieur ou egale a 3
     }

//end: is_valid_board

//start: is_valid_game
int is_valid_game(int n_symbols2win, int height, int width){
     if(n_symbols2win>2 && n_symbols2win<=height && n_symbols2win<=width){
          return 1;
     }
     else {
          printf("Wrong input!\n");
          return 0;
     }
     // le nombre de symboles consecutifs pour gagner doir etre superieur a 2, et inferieur ou egale a la taille du tableau
}
//end: is_valid_game

//start: visualize_board
void visualize_board(int height, int width, char board[height][width]) {
     /* TODO: Write your implementation of the function here */
          /* TODO: Write your implementation of the function here */
     
     printf("  ");
     //deux premiers espaces

     for(int i=1; i<=width;i++){
          printf("%d ", i);
     }
     printf("\n ");
     //enumeration des colonnes 

     for (int i=1; i<=height; i++){
          for (int j=1; j<=width; j++){
               printf("+-");}
               //ligne de +-

          printf("+\n%d",i);
          //dernier + de la ligne et saut de ligne avec numero de la nouvelle ligne

          for (int j=1; j<=width; j++){
               printf("|%c", board[i-1][j-1]);
          }
          //enumeration des valeurs du tableau separes par des |

          printf("|\n ");
          // dernier | de la ligne et saut de ligne
          }
     
     for (int j=1; j<=width; j++){
          printf("+-");}
          //ligne de +-

     printf("+\n");
     //dernier +


     //permet de montrer le tableau sur le terminal
}
//end: visualize_board

//start: is_valid_pos
int is_valid_pos(struct Position pos, int height, int width, char board[height][width]) {
     /* TODO: Write your implementation of the function here */
     if (pos.row<1 || pos.col<1|| pos.row>height || pos.col>width){
          return 0;}
     else if(board[pos.row-1][pos.col-1]!=SYMBOL_FOR_EMPTY){
          return -1;
     }
     else {
          return 1;
     }
     
     }

//end: is_valid_pos

//start: did_player_win
int did_player_win(struct Position pos, int n_symbols2win,int height, int width, char board[height][width]) {

     /* TODO: Write your implementation of the function here */
char symbol;
     
     if(board[pos.row][pos.col]==SYMBOL_FOR_CROSS){
          symbol=SYMBOL_FOR_CROSS;
          }
     else {
          symbol=SYMBOL_FOR_ZERO;
     }
    // definition du symbole a rechercher

     int i, k;
     i=1;
     k=1;
     while (board[pos.row][pos.col-i]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row][pos.col+i]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification des lignes 

     i=k=1;
     while (board[pos.row-i][pos.col]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row+i][pos.col]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification des colonnes

     i=k=1;
     while (board[pos.row+i][pos.col-i]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row-i][pos.col+i]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification des diag haut bas

     i=k=1;
     while (board[pos.row-i][pos.col-i]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     i=1;
     while (board[pos.row+i][pos.col+i]==symbol){
          k++;
          i++;
          if(k==n_symbols2win){
               return 1;
          }
     }
     //verification diagonale de bas a haut




     return 0;
     }
//end: did_player_win


//start: get_bot_pos
struct Position get_bot_pos(int height, int width, char board[height][width]) {
     /* TODO: Write your implementation of the function here */
     struct Position pos_bot;
     pos_bot.row=rand() % height;
     pos_bot.col=rand() % width;
     return pos_bot;
     // peermet de faire jouer le bot aleatoirement
}
//end: get_bot_pos

//start: step
struct Position step(int height, int width, char board[height][width], int play_with_pc) {
     /* TODO: Write your implementation of the function here */
     int i;
     struct Position pos;
     pos.row=0;
     pos.col=0;


     if (current_turn % 2==0){
          i=2;
          //current turn pair: au joueur 2 ou au bot de jouer
     }
     else {
          i=1;
          // current turn impair: au joueur 1 de jouer 
     }
     printf("Player #%d's turn:\n",i);
     if (play_with_pc==1){
          //on joue avec le bot
          if (i==1){
               //au joueur 1 de jouer
               scanf("%d %d", &pos.row, &pos.col);
               while (is_valid_pos(pos, height, width, board)!=1 ){
               //verifie si la position rentre est valide
               if(is_valid_pos(pos, height, width, board)==0){
               //position rentre est hors tableau
               printf("Wrong input!\n");
               printf("Do you want to forfeit the game? Write ‘y’ for yes and ‘n’ for no:\n");
               //proposition abandonner partie
               char respons='y';
               scanf("%s", &respons);
               switch (respons)
               {
               case 'y':
                    
                    break;
               
               default :
                    scanf("%d %d", &pos.row, &pos.col);
               }

               }
               else if(is_valid_pos(pos, height, width, board)==-1){
                    //position n'est pas vide
                    printf("Wrong input! The cell is not empty!\n");
               }
               scanf("%d %d", &pos.row, &pos.col);
               
               }
               
          }
          else{
               //au bot de jouer
               pos=get_bot_pos(height, width, board);
               while (is_valid_pos(pos, height, width, board)!=1 )
               {
                    //permet de faire jouer le bot sur une position valide
                    pos=get_bot_pos(height, width, board);
               }
               current_turn++;//permet de changer de tour a prochaine execution
               return pos; //retourne une position ou un joueur y mettra un symbole
          }

     }
     else {
          //on ne joue pas avec le bot
          scanf("%d %d", &pos.row, &pos.col);
               while (is_valid_pos(pos, height, width, board)!=1 ){
                    //permet obtenir position valide
               if(is_valid_pos(pos, height, width, board)==0){
                    //position en dehors du tableau
                    printf("Do you want to forfeit the game? Write ‘y’ for yes and ‘n’ for no:\n");
                    //proposition abandonner
                    char respons='y';
                    scanf("%c", &respons);
                    switch (respons)
                    {
                    case 'y':

                         return pos;

                    default :
                    ;
                    }    }
               scanf("%d %d", &pos.row, &pos.col);
               
               
          }}
          current_turn++;
          pos.row--;
          pos.col--;//permet de retranscrire au tableau les bonnes valeurs
          return pos; //retourne position

     }

//end: step

//start: is_game_winnable
int is_game_winnable(int n_symbols2win, int height, int width, char board[height][width]) {
     /* TODO: Write your implementation of the function here */
     char symbol;
     for (int s=1;s<3; s++){

     if (s==1){
          symbol=SYMBOL_FOR_ZERO;
     }
     else {
          symbol=SYMBOL_FOR_CROSS;
     }


     int poss_par_ligne=width-n_symbols2win;
     for (int k=0; k<width; k++){
        //premiere boucle qui permet de changer de ligne 
     for (int i = 0; i <= poss_par_ligne; i++){
        // deuxieme boucle qui permet de determiner combien de possibilites de victoire sur une ligne et qui permet de les tester
        // une fois toute tester on change de ligne
          for (int j=0; j<n_symbols2win; j++){
            // troisieme boucle qui verifie le nb de symboles consecutifs
               if (board[k][i+j]!=symbol){
                    if(j==n_symbols2win-1){
                    return 1;
                    // si n_symbols2win consecutifs, victoire 
                    }
               }
               
               else {
                    break;}
                    //si une  possibilite de la ligne n'est plus valide, on passe a la prochaine poss de la ligne
          }
     }
     }
    //verification des lignes 


int poss_par_colonne=height-n_symbols2win;
     for (int t=0; t<height; t++){
        //premiere boucle qui permet de changer de colonne  
     for (int i = 0; i <= poss_par_colonne; i++){
          // deuxieme boucle qui permet de determiner combien de possibilites theoriques de victoire sur une colonne
          //permet de toutes les tester
          // une fois toute tester on change de ligne
          for (int j=0; j<n_symbols2win; j++){
          // troisieme boucle qui verifie le nb de symboles consecutifs
          if (board[i+j][t]!=symbol){
               if(j==n_symbols2win-1){
                    return 1;}
                    // si n_symbols2win consecutifs, victoire 
          }

          else {
               break;}
                //si une  possibilite de la colonne n'est plus valide, on passe a la prochaine possibilite de la colonne
          }
     }
     }
    //verification des colonnes


int poss_par_diag, nb_cases_diag, largeur=0;
     for (int hauteur=height-3; hauteur>=-1; hauteur--){
        // boucle qui permet de changer de diagonale
          
          if (hauteur<0){
               hauteur=0;
               largeur++;
          }
          if (largeur==width-2){
               break;
          }
          if (hauteur>largeur){
               nb_cases_diag=height-hauteur;
          }
          else {
               nb_cases_diag=width-largeur;
          }
          poss_par_diag=nb_cases_diag-n_symbols2win;
          for(int i=0; i<=poss_par_diag;i++){

               for (int j=0; j<n_symbols2win; j++){
                    if (board[hauteur+i+j][largeur+i+j]!=symbol){
                         if (j==n_symbols2win-1){
                              return 1;
                         }  
                    } 
                    else {
                    break;}

               }
          }
     }
// verification des diagonales de haut en bas

int hauteur=height-1;
largeur=width-3;
     for (largeur=width-3; largeur >=-1; largeur--){
          // boucle qui permet de changer de diagonale
          
          if (largeur<0){
               largeur=0;
               hauteur--;
          }
          if (hauteur==1){
               return 0;
          }
          if (hauteur>largeur){
               nb_cases_diag=width-largeur;
          }
          else {
               nb_cases_diag=height-hauteur;
          }
          poss_par_diag=nb_cases_diag-n_symbols2win;
          for(int i=0; i<=poss_par_diag;i++){

               for (int j=0; j<n_symbols2win; j++){
                    if (board[hauteur-i-j][largeur+i+j]!=symbol){
                         if (j==n_symbols2win-1){
                              return 1;}
                    
                    }
                    else {
                    break;}
               }
          }
     }
    //verification des diagonales de bas en haut
     }
     return 0;
     }
//end: is_game_winnable

//End of the script