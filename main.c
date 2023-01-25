/*       LIBRERIE        */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*      VARIABILI GLOBALI       */
int riga;
int colonna;
int inizio[2] = {-2,-2};
int vinto[2] = {-2,-2};
char **campo;
int pos[2] = {-2,-2};
int *passi_pos_array;
int passi = 0;
int bonus = 0;
int trapano = 0;
int coda = 0;
char *passi_pos;
char spostamento;
_Bool verifica=0;
_Bool mettiMuro=0;
_Bool finish=0;

/*          RIEMPIMENTO TABELLA         */
void inizializzaTabella(void){
    int muro[16][2] = {{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{8,13},{7,13},{6,13},{5,13},{4,13},{3,13},{2,13},{2,12},{2,11},{3,11}};
    int guadagno[8][2] = {{8,6},{8,7},{8,8},{8,9},{1,17},{2,17},{3,17},{4,17}};
    int imprevisto[1][2] = {{4,10}};
    int trapano[1][2] = {{2,3}};
    
    for (int i =0; i<riga; i++) {
        for (int j=0; j<colonna; j++) {
            _Bool a=0, b=0, c=0, d=0;
            for (int k=0; k<16; k++) {
                if(muro[k][0]==i&&muro[k][1]==j)
                    a=1;
            }
            for (int k=0; k<8; k++) {
                if(guadagno[k][0]==i&&guadagno[k][1]==j)
                    b=1;
            }
            for (int k=0; k<1; k++) {
                if(imprevisto[k][0]==i&&imprevisto[k][1]==j)
                    c=1;
            }
            for (int k=0; k<1; k++) {
                if(trapano[k][0]==i&&trapano[k][1]==j)
                    d=1;
            }
            if(a==1)
                campo[i][j]='#';
            else if(b==1)
                campo[i][j]='$';
            else if(c==1)
                campo[i][j]='!';
            else if(d==1)
                campo[i][j]='T';
            else if(i==0||i==riga-1)
                campo[i][j]='#';
            else if(j==0||j==colonna-1)
                campo[i][j]='#';
            else
                campo[i][j]=' ';
        }
    }
    campo[vinto[0]][vinto[1]]='_';
}

/*           STAMPA TABELLA          */
void stampaTabella(void){
    if(finish==1){
        int pos_cursore[2] = {vinto[0], vinto[1]};
        for(int i=passi-2; i>=0; i--){
            if(passi_pos[i]=='N'){
                campo[pos_cursore[0]+1][pos_cursore[1]]='.';
                pos_cursore[0] = pos_cursore[0]+1;
            }else if(passi_pos[i]=='S'){
                campo[pos_cursore[0]-1][pos_cursore[1]]='.';
                pos_cursore[0] = pos_cursore[0]-1;
            }else if(passi_pos[i]=='E'){
                campo[pos_cursore[0]][pos_cursore[1]-1]='.';
                pos_cursore[1] = pos_cursore[1]-1;
            }else if(passi_pos[i]=='O'){
                campo[pos_cursore[0]][pos_cursore[1]+1]='.';
                pos_cursore[1] = pos_cursore[1]+1;
            }
        }
        for (int i=0; i<riga; i++) {
            for (int j=0; j<colonna; j++) {
                if(i==pos[0]&&j==pos[1]){
                    printf("@");
                }else{
                    printf("%c", campo[i][j]);
                }
            }
            printf("\n");
        }
    }else{
        int pos_coda[2] = {pos[0], pos[1]};
        if(bonus>0){
            passi_pos_array=realloc(passi_pos_array, sizeof(int)*(coda*2));
            for (int i=0; i<coda; i++) {
                if(passi_pos[passi-i-2]=='N'){
                    pos_coda[0]=pos_coda[0]+1;
                    campo[pos_coda[0]][pos_coda[1]]='*';
                    passi_pos_array[i*2] = pos_coda[0];
                    passi_pos_array[i*2+1] = pos_coda[1];
                }else if(passi_pos[passi-i-2]=='S'){
                    pos_coda[0]=pos_coda[0]-1;
                    campo[pos_coda[0]][pos_coda[1]]='*';
                    passi_pos_array[i*2] = pos_coda[0];
                    passi_pos_array[i*2+1] = pos_coda[1];
                }else if(passi_pos[passi-i-2]=='E'){
                    pos_coda[1]=pos_coda[1]-1;
                    campo[pos_coda[0]][pos_coda[1]]='*';
                    passi_pos_array[i*2] = pos_coda[0];
                    passi_pos_array[i*2+1] = pos_coda[1];
                }else if(passi_pos[passi-i-2]=='O'){
                    pos_coda[1]=pos_coda[1]+1;
                    campo[pos_coda[0]][pos_coda[1]]='*';
                    passi_pos_array[i*2] = pos_coda[0];
                    passi_pos_array[i*2+1] = pos_coda[1];
                }
            }
        }
        
        for (int i=0; i<riga; i++) {
            for (int j=0; j<colonna; j++) {
                if(i==pos[0]&&j==pos[1]){
                    printf("@");
                }else{
                    printf("%c", campo[i][j]);
                }
            }
            printf("\n");
        }
        
        if(bonus>0){
            for (int i=0; i<coda; i++) {
                for(int k=0; k<2; k++){
                    campo[passi_pos_array[i*2]][passi_pos_array[i*2+1]]=' ';
                }
            }
        }
    }

}

/*          CONTROLLO SPOSTAMENTI         */
void spostamentoFunction(void){
    int pos2[2]={pos[0], pos[1]};
    
    if(spostamento=='n'){
        spostamento='N';
    }else if(spostamento=='s'){
        spostamento='S';
    }else if(spostamento=='o'){
        spostamento='O';
    }else if(spostamento=='e'){
        spostamento='E';
    }
    
    switch (spostamento){
        case 'N':
            pos[0] = pos[0]-1;
            break;
        case 'S':
            pos[0] = pos[0]+1;
            break;
        case 'O':
            pos[1] = pos[1]-1;
            break;
        case 'E':
            pos[1] = pos[1]+1;
            break;
        default:
            verifica=1;
            break;
    }
    if(campo[pos[0]][pos[1]]=='#'||(pos[0]<0||pos[1]<0||pos[0]>=riga||pos[1]>=colonna)){
        if(campo[pos[0]][pos[1]]=='#'&&trapano>0){
            trapano-=1;
            campo[pos[0]][pos[1]]= ' ';
            passi++;
        }else{
            pos[0] = pos2[0];
            pos[1] = pos2[1];
            verifica=1;
        }
    }else if(campo[pos[0]][pos[1]]=='$'){ //controllo bonus
        campo[pos[0]][pos[1]] = ' ';
        bonus = bonus+10;
        coda++;
        passi++;
    }else if(campo[pos[0]][pos[1]]=='!'){ //controllo imprevisti
        campo[pos[0]][pos[1]] = ' ';
        bonus = bonus/2;
        coda = coda/2;
        passi++;
    }else if(campo[pos[0]][pos[1]]=='_'){ //controllo fine
        finish=1;
        passi++;
    }else if(campo[pos[0]][pos[1]]=='T'){ //controllo trapano
        campo[pos[0]][pos[1]]=' ';
        trapano+=3;
        passi++;
    }else{
        if(bonus>0){
            if(passi_pos_array==NULL) passi_pos_array = (int*) malloc(sizeof(int)*2);
            for (int i=0; i<coda; i++) {
                if(passi_pos_array[i*2]==pos[0]&&passi_pos_array[i*2+1]==pos[1]){
                    passi_pos_array=realloc(passi_pos_array, sizeof(int)*(i*2));
                    coda=i;
                    bonus=i*10;
                }
            }
        }
        passi++;
    }
    if(verifica!=1){
        if(mettiMuro==1){
            if(spostamento=='N'){
                campo[pos[0]+1][pos[1]]='#';
            }else if(spostamento=='S'){
                campo[pos[0]-1][pos[1]]='#';
            }else if(spostamento=='E'){
                campo[pos[0]][pos[1]-1]='#';
            }else if(spostamento=='O'){
                campo[pos[0]][pos[1]+1]='#';
            }
        }
        passi_pos = (char*) realloc(passi_pos, sizeof(char)*passi);
        if(passi_pos==NULL) exit(EXIT_FAILURE);
        passi_pos[passi-2] = spostamento;
        passi_pos[passi-1] = spostamento;
    }
}

/*        MODALITA RANDOM         */
void automaticoRand(char inputV){
    if(pos[0]==0||pos[0]==riga-1||pos[1]==0||pos[1]==colonna-1){
        if(pos[0]==0){
            spostamento='S';
        }else if(pos[0]==riga-1){
            spostamento='N';
        }else if(pos[1]==0){
            spostamento='E';
        }else if(pos[1]==colonna-1){
            spostamento='O';
        }
    }else{
        if(campo[pos[0]+1][pos[1]]=='_') //vittoria sotto
            spostamento='S';
        else if(campo[pos[0]-1][pos[1]]=='_') //vittoria alto
            spostamento='N';
        else if(campo[pos[0]][pos[1]-1]=='_') //vittoria sx
            spostamento='O';
        else if(campo[pos[0]][pos[1]+1]=='_') //vittoria dx
            spostamento='E';
        else{
            switch (rand()%4) {
                case 0: //verso Sud
                    spostamento='S';
                    break;
                case 1: //verso Est
                    spostamento='E';
                    break;
                case 2: //verso Ovest
                    spostamento='O';
                    break;
                case 3: //verso Nord
                    spostamento='N';
                    break;
                default:
                    spostamento='a';
                    break;
            }
        }
    }
}

/*      MODALITA INTELLIGENTE       */
//modalita anticlockwise
void strategia1(char spostamentoV){
    _Bool muroN = 0, muroS = 0, muroE = 0, muroO = 0;
    _Bool diag1=0, diag2=0, diag3=0, diag4=0;
    if(pos[0]==inizio[0]&&pos[1]==inizio[1]){
        if(pos[0]==0)
            spostamento='S';
        else if(pos[0]==riga-1)
            spostamento='N';
        else if(pos[1]==0)
            spostamento='E';
        else if(pos[1]==colonna-1)
            spostamento='O';
    }else{
        if(campo[pos[0]+1][pos[1]]=='#') //muro sotto
            muroS=1;
        if(campo[pos[0]-1][pos[1]]=='#') //muro alto
            muroN=1;
        if(campo[pos[0]][pos[1]-1]=='#') //muro sx
            muroO=1;
        if(campo[pos[0]][pos[1]+1]=='#') //muro dx
            muroE=1;
        if(campo[pos[0]-1][pos[1]-1]=='#') //angolo alto sx
            diag1=1;
        if(campo[pos[0]-1][pos[1]+1]=='#') //angolo alto dx
            diag2=1;
        if(campo[pos[0]+1][pos[1]-1]=='#') //angolo basso sx
            diag3=1;
        if(campo[pos[0]+1][pos[1]+1]=='#') //angolo basso dx
            diag4=1;
        
        if(campo[pos[0]+1][pos[1]]=='_') //vittoria sotto
            spostamento='S';
        else if(campo[pos[0]-1][pos[1]]=='_') //vittoria alto
            spostamento='N';
        else if(campo[pos[0]][pos[1]-1]=='_') //vittoria sx
            spostamento='O';
        else if(campo[pos[0]][pos[1]+1]=='_') //vittoria dx
            spostamento='E';
        else if(muroN==0&&muroS==0&&muroE==0&&muroO==0){
            if(diag1==1){
                spostamento='O';
            }else if(diag4==1){
                spostamento='E';
            }else if(diag3==1){
                spostamento='S';
            }else if(diag2){
                spostamento='N';
            }
        }else if(muroS==1){
            if(muroE==1){
                if(muroN==1){
                    spostamento='O';
                    mettiMuro=1;
                }else if(muroN==0){
                    spostamento='N';
                }
            }else if(muroE==0){
                spostamento='E';
            }
        }else if(muroS==0){
            if(muroE==1){
                if(muroN==1){
                    if(muroO==1){
                        spostamento='S';
                        mettiMuro=1;
                    }else if(muroO==0){
                        spostamento='O';
                    }
                }
            }else if(muroE==0){
                if(muroN==1){
                    if(muroO==1){
                        spostamento='S';
                    }else if(muroO==0){
                        if(diag4==1){
                            spostamento='E';
                        }else if(diag3==1){
                            spostamento='S';
                        }else{
                            spostamento='O';
                        }
                    }
                }
            }
        }
    }
}

//modalita clockwise
void strategia2(char spostamentoV){
    _Bool muroN = 0, muroS = 0, muroE = 0, muroO = 0;
    _Bool diag1=0, diag2=0, diag3=0, diag4=0;
    if(campo[pos[0]+1][pos[1]]=='#') //muro sotto
        muroS=1;
    if(campo[pos[0]-1][pos[1]]=='#') //muro alto
        muroN=1;
    if(campo[pos[0]][pos[1]-1]=='#') //muro sx
        muroO=1;
    if(campo[pos[0]][pos[1]+1]=='#') //muro dx
        muroE=1;
    if(campo[pos[0]-1][pos[1]-1]=='#') //angolo alto sx
        diag1=1;
    if(campo[pos[0]-1][pos[1]+1]=='#') //angolo alto dx
        diag2=1;
    if(campo[pos[0]+1][pos[1]-1]=='#') //angolo basso sx
        diag3=1;
    if(campo[pos[0]+1][pos[1]+1]=='#') //angolo basso dx
        diag4=1;
    
    if(campo[pos[0]+1][pos[1]]=='_') //vittoria sotto
        spostamento='S';
    else if(campo[pos[0]-1][pos[1]]=='_') //vittoria alto
        spostamento='N';
    else if(campo[pos[0]][pos[1]-1]=='_') //vittoria sx
        spostamento='O';
    else if(campo[pos[0]][pos[1]+1]=='_') //vittoria dx
        spostamento='E';
    else if(muroN==0&&muroS==0&&muroE==0&&muroO==0){
        if(diag1==1){
            spostamento='N';
        }else if(diag2==1){
            spostamento='E';
        }else if(diag4==1){
            spostamento='S';
        }else if(diag3==1){
            spostamento='O';
        }
        
    }else if(muroS==1){
        if(muroN==1){
            if(muroE==1){
                spostamento='O';
                mettiMuro=1;
            }else if(muroE==0){
                if(muroS==0){
                    spostamento='S';
                }else if(muroS==1){
                    spostamento='E';
                }
            }
        }else if(muroN==0){
            if(muroO==1){
                if(spostamentoV=='O')
                    spostamento='N';
                else if(spostamentoV=='N')
                    spostamento='E';
            }else if(muroO==0){
                if(muroE==1)
                    spostamento='O';
                else if(muroE==0){
                    if(diag2==1)
                        spostamento='E';
                    else if(diag1==1)
                        spostamento='N';
                    else
                        spostamento=spostamentoV;
                }
            }
        }
    }else if(muroS==0){
        if(muroN==1){
            if(muroE==1){
                if(muroO==1){
                    spostamento='S';
                    mettiMuro=1;
                }else if(muroO==0){
                    if(spostamentoV=='N'){
                        spostamento='O';
                    }else if(spostamentoV=='E'){
                        spostamento='S';
                    }
                }
                    
            }else if(muroE==0){
                spostamento='E';
            }
        }else if(muroN==0){
            if(muroO==1)
                spostamento='N';
            else if(diag1==1)
                spostamento='N';
            else if(muroE==1)
                spostamento=spostamentoV;
        }
    }
}

int main() {
    system("clear");
    printf("\t\t\t - - - - - - - - - - - -\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t||     SNAKE GAME @     ||\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t||                      ||\n");
    printf("\t\t\t - - - - - - - - - - - -\n");
    sleep(3);
    system("clear");
    printf("------------ Welcome to Snake Labyrint ------------\n\n");
    printf("Game instructions:\n\nThe objective of the game is to get out of the maze losing fewer points than the other players.\nThe game score starts from 1000 points.\n\nGame controls:\n- N -> move up;\n- E -> shift to the right;\n- O -> shift to the left;\n- S -> move down.\n\nInside the map there are some objects:\n- $ -> add 3 points at your score and stretches out the serpent's tail;\n- ! -> halve the points and the serpent's tail accumulated up to then;\n- T -> adds three drills to go through walls.\nWhen the head of the snake bites the tail the snake will lose a piece of the tail.\n\nIt is possible to play in three modes:\n- individual mode, the user decides the moves;\n- random mode, the computer decides the moves randomly;\n- intelligent mode, the computer decides the moves following two strategies: \n\t- clockwise;\n\t- anticlockwise.\n\nPress ENTER to start playing.");
    while(getchar() != '\n');
    int modalita=-1;
    do{
        system("clear");
        printf("Snake Labyrinth\n\nChoose which map to play on:\n1. standard map\n2. manual entry\nDigit the number: ");
        if(scanf(" %d", &modalita)==0){
            fflush(stdin);
        }
    }while(modalita!=1&&modalita!=2);
    switch (modalita) {
        case 1:     //inizializza mappa 1
            riga=10;
            colonna=20;
            campo=(char**) malloc(sizeof(char*)*riga);
            for (int i=0; i<riga; i++) {
                campo[i]=(char*) malloc(sizeof(char)*colonna);
            }
            if(!campo) exit(EXIT_FAILURE);
            inizio[0]=1;
            inizio[1]=0;
            vinto[0]=5;
            vinto[1]=19;

            inizializzaTabella(/*16, muro1, 8, guadagno1, 1, imprevisto1, 1, trapano1*/);
            break;
        case 2:     //inserimento manuale della mappa
            system("clear");
            printf("Snake Labyrinth\n\n");
            do{
                printf("Insert number of rows: ");
                if(scanf(" %d", &riga)==0){
                    fflush(stdin);
                }
            }while(riga<=0);
            do{
                printf("Insert number of columns: ");
                if(scanf(" %d", &colonna)==0){
                    fflush(stdin);
                }
            }while(colonna<=0);
            campo=(char**) malloc(sizeof(char*)*riga);
            for (int i=0; i<riga; i++) {
                campo[i]=(char*) malloc(sizeof(char)*colonna);
            }
            if(!campo){
                printf("\nMap creation failed!");
                exit(EXIT_FAILURE);
            }
            system("clear");
            char inputs[colonna];
            printf("Snake Labyrinth\n\nDivide the original map into rows and insert one row at a time.\nIf the inserted row is longer than the available columns it will be cut.\nAfter each line press ENTER.\n\nTo indicate a muor type '#';\nTo indicate the initial position of the cursor type 'o';\nTo indicate the end of the path type '_';\nTo indicate a coin type '$';\nTo indicate something unexpected type '!';\nTo indicate a drill type 'T';\nTo indicate an empty box type a space.\nThe start and end of the route must be established within the map otherwise the game will end.\nSymbols other than those indicated will be displayed on the map but will not be used.\n\nInsert now your table:\n\n");
            for (int i=0; i<riga; i++) {
                fflush(stdin);
                scanf(" %[^\n]s", inputs);
                for (int j=0; j<colonna; j++) {
                    if(inputs[j]=='o'){
                        inizio[0]=i;
                        inizio[1]=j;
                        campo[i][j]='#';
                    }else{
                        if(inputs[j]=='_'){
                            vinto[0]=i;
                            vinto[1]=j;
                        }
                        campo[i][j]=inputs[j];
                    }
                    if((i==riga-1&&j==colonna-1)&&(inizio[0]==-2&&inizio[1]==-2)&&(vinto[0]==-2&&vinto[1]==-2)){
                        printf("Error: no beginning and end of the maze entered.");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            break;
    }
    pos[0] = inizio[0];
    pos[1] = inizio[1];
    passi_pos = (char*) malloc(sizeof(char)*1);
    if(!passi_pos)  exit(EXIT_FAILURE);

    //scelta modalità
    modalita=-1;
    do{
        system("clear");
        printf("Snake Labyrinth\n\nChoose modaliy:\n1. individual\n2. random\n3. artificial intelligence\nDigit the number: ");
        if(scanf(" %d", &modalita)==0){
            fflush(stdin);
        }
    }while(modalita!=1&&modalita!=2&&modalita!=3);
        
    if(modalita==1){ //manuale
        while(finish==0){
            system("clear");
            if(verifica==1){
                printf("Error: input not valid.\n");
                verifica = 0;
            }
            stampaTabella();
            printf("\nInsert the direction: ");
            scanf(" %c", &spostamento);
            spostamentoFunction();
        }
        verifica = 0;
    }else if(modalita==2){ //random
        system("clear");
        printf("Route calculation in progress\n\nAttention:\n- this process can take a few minutes and will produce a lot of moves;\n- the algorithm involves a lot of memory expenditure\n");
        srand((unsigned) time(NULL));
        while(finish==0){
            if(passi>=15000){
                system("clear");
                printf("----------- Game completed -----------\n\nThe steps taken have exceeded the threshold limit.\n Sorry, but the path out of the maze could not be found.\n\n");
                printf("---- thanks for playing and see you next time ----\n\n");
                break;
            }
            verifica = 0;
            automaticoRand(spostamento);
            spostamentoFunction();
        }
        verifica=1;
    }else if(modalita==3){ //intelligente
        modalita=-1;
        do{
            system("clear");
            printf("Snake Labyrinth\n\nChoose the strategy:\n1. clockwise\n2. anticlockwise\nDigit the number: ");
            if(scanf(" %d", &modalita)==0){
                fflush(stdin);
            }
        }while(modalita!=1&&modalita!=2);
        printf("Route calculation in progress\n\nAttention:\n- this process can take a few minutes and will produce a lot of moves;\n- the algorithm involves a lot of memory expenditure\n");
        if(modalita==2){
            while(finish==0){
                if(passi>=15000){
                    system("clear");
                    printf("----------- Game completed -----------\n\nThe steps taken have exceeded the threshold limit.\n Sorry, but the path out of the maze could not be found.\n\n");
                    printf("---- thanks for playing and see you next time ----\n\n");
                    break;
                }
                mettiMuro=0;
                verifica = 0;
                strategia1(spostamento);
                spostamentoFunction();
            }
            verifica = 0;
        }else if(modalita==1){
            while(finish==0){
                if(passi>=15000){
                    system("clear");
                    printf("----------- Game completed -----------\n\nThe steps taken have exceeded the threshold limit.\n Sorry, but the path out of the maze could not be found.\n\n");
                    printf("---- thanks for playing and see you next time ----\n\n");
                    break;
                }
                mettiMuro=0;
                verifica = 0;
                strategia2(spostamento);
                spostamentoFunction();
            }
            verifica = 0;
        }
    }
    if(finish==1){
        system("clear");
        printf("----------- Game completed -----------\n\nRoute taken:\n");
        stampaTabella();
        if(verifica==0){
            printf("\nMovements made:\n");
            for (int i=0; i<passi; i++) {
                if(i!=0) printf(", %c", passi_pos[i]);
                else    printf("%c", passi_pos[i]);
            }
        }
        printf("\nYour score: %d\n\n", 1000+bonus-passi);
        printf("---- thanks for playing and see you next time ----\n\n");
        
    }
    return 0;
}
