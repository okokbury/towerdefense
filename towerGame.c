#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

//globais 
#define TAM_MAPA 10
#define MAX_INIMIGOS 5
#define TAM_MAX_ROTA 20
#define MAX_TORRES 80

char mapaI[TAM_MAPA][TAM_MAPA] = {
        {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'},
        {'1', '/', '/', '/', '/', '/', '/', '/', '/', '/'},
        {'2', '/', '/', '/', '/', '/', '/', '/', '/', '/'},
        {'3', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'4', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'5', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'6', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'7', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'8', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'9', '/', '/', '/', '/', '/', '/', '/', '/', 'B'}  
    };

    //struct do inimigo p ter a vida e as coordenadas do bicho
    typedef struct {
        int x;
        int y;
        int vida;
    } Inimigo;

    //struct pra criacao da rota do inimigo
    typedef struct {
        int x;
        int y;
    } PontoRota;

    typedef struct {
        int x;
        int y;
        int danoTorre;
        int alcance;
        int valorPagoTorre;
        int alvoAtual;
    } Torre;
    
    //funcao de delay
    void delay(int milliseconds) {
    struct timespec req;
    req.tv_sec = milliseconds / 1000;
    req.tv_nsec = (milliseconds % 1000) * 1000000;

    nanosleep(&req, NULL);
}
   
    //funcao pra fazer a rota entre a primeira casa ate a base
    void gerarRota(PontoRota* rota, int* tamanhoRota) {
        int x = 1, y = 1;
        int xFinal = 9, yFinal = 9; 
        int i = 0;

        srand(time(NULL));

        while (x != xFinal || y != yFinal) {
            rota[i].x = x;
            rota[i].y = y;
            i++;

            // decide p que lado mexe
            int direcao = rand() % 2;

            //mexe na horizontal aleatoriamente
            if (direcao == 0 && x != xFinal) {
                if (x < xFinal) {
                    x++;
                } else {
                    x--;
                }
            }
            // Movimento vertical, verifica se y ainda não atingiu o limite
            else if (direcao == 1 && y != yFinal) {
                if (y < yFinal) {
                    y++;
                } else {
                    y--;
                }
            }
        }

        // Marca o ponto final da rota
        rota[i].x = xFinal;
        rota[i].y = yFinal;
        *tamanhoRota = i + 1;
    }

    //funcao pra criar rota
    void desenharRota(char mapaI[TAM_MAPA][TAM_MAPA], PontoRota* rota, int tamanhoRota) {
        for (int i = 0; i < tamanhoRota; i++) {
            int x = rota[i].x;
            int y = rota[i].y;
            if (mapaI[x][y] == '/') { //marcando o caminho q o inimigo vai passar
                mapaI[x][y] = ' ';
            }
        }
    }
    void desenharInimigo(char mapaI[TAM_MAPA][TAM_MAPA], PontoRota* rota, int tamanhoRota) {
        for (int i = 0; i < tamanhoRota; i++) {
            int x = rota[i].x;
            int y = rota[i].y;
            if (mapaI[x][y] == '/') { //marcando o caminho q o inimigo vai passar
                mapaI[x][y] = ' ';
            }
        }
    }
    
    //funcao pra ver se ta no range e bater, o outro tava funcionando mas se o inimigo saia do range ele continuava batendo
    int torreVeInimigo(Torre *torre, Inimigo *inimigo) {
        int dx = torre->x - inimigo->x;
        int dy = torre->y - inimigo->y;
        int distancia = sqrt(dx * dx + dy * dy);
        return distancia <= torre->alcance;
    }

    //funcao pra limpar o console win e linux
    void limparConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

    void limparConsoleRestosMais(){
        gotoxy(0, 11);
        printf("                                                                               \n");
        gotoxy(0, 12);
        printf("                                                                               \n");
        gotoxy(0, 13);
        printf("                                                                               \n");
        gotoxy(0, 14);
        printf("                                                                               \n");
        gotoxy(0, 15);
        printf("                                                                               \n");
        gotoxy(0, 16);
        printf("                                                                               \n");
        gotoxy(0, 17);
        printf("                                                                               \n");
        gotoxy(0, 18);
        printf("                                                                               \n");
        gotoxy(0, 19);
        printf("                                                                               \n");
        gotoxy(0, 20);
        printf("                                                                               \n");
        gotoxy(0, 21);
        printf("                                                                               \n");
        gotoxy(0, 22);
        printf("                                                                               \n");
        gotoxy(0, 23);
        printf("                                                                               \n");
    }
    void limparConsoleRestosMenos(){
        gotoxy(0, 20);
        printf("                                                                               \n");
        gotoxy(0, 21);
        printf("                                                                               \n");
        gotoxy(0, 22);
        printf("                                                                               \n");
        gotoxy(0, 23);
        printf("                                                                               \n");
    }
    //funcao pra colocar a msg em tal posicao win e linux
    void gotoxy(int x, int y) {
    #ifdef _WIN32
        COORD coord;
        coord.X = x; // coluna
        coord.Y = y; // linha
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #else
    //foi assim q eu vi q tinha q ser no linux n sei se vai funcionar, testa no seu pc
        printf("\033[%d;%dH", y, x);
    #endif
}

    //funcao pra mostrar a tela inicial, fiz em funcao so pra ficar mais organizado
    void letreiroPrint(){                                                                            
    printf("                                                                                               \n");  
    printf("                       ------------------------------------------------------------------------\n");  
    printf("                       |                                                                      |\n");  
    printf("                       |         |xxxxxxxxxxx| |xxxxxxx| |xxx| |xxx| |xxxxx| |xxxxxx|         |\n");  
    printf("                       |         |           | |       | |   |x|   | |     | |  xxxx|         |\n");  
    printf("                       |         |xxx|   |xxx| |  xxx  | |   | |   | | xxxx| |  |             |\n");  
    printf("                       |             |   |     |  x x  | |   | |   | |    |  |  |             |\n");  
    printf("                       |             |   |     |  xxx  | |         | | xxxx| |  |             |\n");  
    printf("                       |             |   |     |       | |         | |     | |  |             |\n");  
    printf("                       |             |xxx|     |xxxxxxx| |xxxxxxxxx| |xxxxx| |xx|             |\n");  
    printf("                       |                                                                      |\n");  
    printf("                       |    |xxxxx|  |xxxxxx| |xxxxxx| |xxxxxx| |xxxx|x| |xxxxxx| |xxxxxx|    |\n");  
    printf("                       |    |     || |      | |      | |      | |    | | |      | |      |    |\n");  
    printf("                       |    | xxx  | | xxxxx| | xxxxx| | xxxxx| |    | | |  xxxx| | xxxxx|    |\n");  
    printf("                       |    | x x  | |    |   |     |  |    |   | |  | | |      | |    |      |\n");  
    printf("                       |    | xxx  | | xxxxx| | xxxx|  | xxxxx| | |    | |xxxxx | | xxxxx|    |\n");  
    printf("                       |    |      | |      | | |      |      | | |    | |      | |      |    |\n");  
    printf("                       |    |     || |      | | |      |      | | |    | |      | |      |    |\n");  
    printf("                       |    |XXXXX|  |XXXXXX| |X|      |XXXXXX| |X|XXXX| |XXXXXX| |XXXXXX|    |\n");  
    printf("                       |                       Press any key to start!                        |\n");  
    printf("                       |                                                                      |\n");  
    printf("                       ------------------------------------------------------------------------\n\n");    
    }

    void tutorialPrint() {
    printf("TOWERDEFENSE - a game by VolumeCare\n");
    printf("                                                                                                                 \n");
    printf("YOUR BASE:                                                                                                       \n");
    printf("                                                                                                                 \n");
    printf("- YOUR BASE HAVE 10HP                                                                                            \n");
    printf("- YOU HAVE TO DEFEND YOUR BASE AT ALL COST                                                                       \n");
    printf("- DONT LET THE ENEMY GET TO IT                                                                                   \n");
    printf("                                                                                                                 \n");
    printf("TOWERS:                                                                                                          \n");
    printf("                                                                                                                 \n");
    printf("- YOU CAN ONLY PUT A TOWER IN A EMPTY SLOT MARKED BY THE \"/\"                                                   \n");
    printf("- TOWER PRICE GETS HIGHER AFTER EACH WAVE                                                                        \n");
    printf("- TOWERS START AT LVL 1 MARKED AS A \"t\" ON THE MAP, IT CAN GO TO LVL 2 \"T\", AND LVL 3 \"W\"                  \n");
    printf("- THE UPGRADE PRICE DEPENDS ON THE PRICE PAID FOR THE TOWER, IF YOU PAID 25 COINS FOR THE TOWER AT ROUND 1,      \n");
    printf("THE LVL 2 UPGRADE WILL COST 4X THE PRICE, 100 COINS, IF YOU WANT TO GO EVEN HIGHER, THE LVL 3 UPGRADE WILL COST  \n");
    printf("3X THE PRICE PAID FOR THE LVL 2 UPGRADE = 300 (ALL PRICES ARE SHOWN WHEN REQUESTING AN UPGRADE)                  \n");
    printf("                                                                                                                 \n");
    printf("- LVL 1 TOWER \"t\", 3x3 ATTACK RANGE, 5DMG PER TICK                                                             \n");
    printf("- LVL 2 TOWER \"T\", 5x5 ATTACK RANGE, 20DMG PER TICK                                                            \n");
    printf("- LVL 3 TOWER \"W\", 7x7 ATTACK RANGE, 100DMG PER TICK                                                           \n");
    printf("                                                                                                                 \n");
    printf("ENEMIES:                                                                                                         \n");
    printf("                                                                                                                 \n");
    printf("- THE ENEMIES START SPAWNING AFTER YOU SELECT TO START THE WAVE                                                  \n");
    printf("- ROUND 1 - 9: 1 ENEMY                                                                                           \n");
    printf("- ROUND 10 - 19: 2 ENEMIES                                                                                       \n");
    printf("- ROUND 20 - 29: 3 ENEMIES                                                                                       \n");
    printf("- ROUND 30 - 39: 4 ENEMIES                                                                                       \n");
    printf("- AFTER ROUND 40 EVERY ROUND WILL 5 ENEMIES                                                                      \n");
    printf("- THE ENEMY LIFE WILL BE BASED ON HOW MANY WAVES YOU HAVE PASSED, CONSTANTLY GETTING HIGHER                      \n");
    printf("\npress any key to continue");
    }

    void printMapa(){
        for(int i=0;i<10;i++){
            printf("\n");
            for(int j=0;j<10;j++){
                printf("%c ", mapaI[i][j]);
            }
        }
    }


int main(){

//Variaveis
int vidaPlayer, nivelPlayer, valorTorre, valorPagoTorre, valorUpgrade, tamanhoRota, ganhoRound, perdeu, ganhou;
float moneyPlayer, vidaRound, vidaDoInimigo[5]={0};
int danoInimigo, maxTorres, ultimaTorreColocada, numInimigos, waveProgress, numTotalInimigosWave;
int mapaTorres[9][9] = {0};
char opcao;
char continuar = 's';

PontoRota rota[TAM_MAX_ROTA];
Inimigo inimigo[MAX_INIMIGOS];
Torre torre[MAX_TORRES];

//definicoes padrao:
vidaPlayer = 10;
moneyPlayer = 50;
nivelPlayer = 1;
valorTorre = 25;
valorUpgrade = valorPagoTorre*2;
waveProgress = 0;
ganhoRound = 50;
vidaRound = 5;
ultimaTorreColocada = -1;
numInimigos = 0;
perdeu = 0;

//Deixa o console limpo pra iniciar
limparConsole();

//Inicio do jogo
//Letreiro                                                                          
//printf("                                                                                               \n");  
//printf("                       ------------------------------------------------------------------------\n");  
//printf("                       |                                                                      |\n");  
//printf("                       |         |xxxxxxxxxxx| |xxxxxxx| |xxx| |xxx| |xxxxx| |xxxxxx|         |\n");  
//printf("                       |         |           | |       | |   |x|   | |     | |  xxxx|         |\n");  
//printf("                       |         |xxx|   |xxx| |  xxx  | |   | |   | | xxxx| |  |             |\n");  
//printf("                       |             |   |     |  x x  | |   | |   | |    |  |  |             |\n");  
//printf("                       |             |   |     |  xxx  | |         | | xxxx| |  |             |\n");  
//printf("                       |             |   |     |       | |         | |     | |  |             |\n");  
//printf("                       |             |xxx|     |xxxxxxx| |xxxxxxxxx| |xxxxx| |xx|             |\n");  
//printf("                       |                                                                      |\n");  
//printf("                       |    |xxxxx|  |xxxxxx| |xxxxxx| |xxxxxx| |xxxx|x| |xxxxxx| |xxxxxx|    |\n");  
//printf("                       |    |     || |      | |      | |      | |    | | |      | |      |    |\n");  
//printf("                       |    | xxx  | | xxxxx| | xxxxx| | xxxxx| |    | | |  xxxx| | xxxxx|    |\n");  
//printf("                       |    | x x  | |    |   |     |  |    |   | |  | | |      | |    |      |\n");  
//printf("                       |    | xxx  | | xxxxx| | xxxx|  | xxxxx| | |    | |xxxxx | | xxxxx|    |\n");  
//printf("                       |    |      | |      | | |      |      | | |    | |      | |      |    |\n");  
//printf("                       |    |     || |      | | |      |      | | |    | |      | |      |    |\n");  
//printf("                       |    |XXXXX|  |XXXXXX| |X|      |XXXXXX| |X|XXXX| |XXXXXX| |XXXXXX|    |\n");  
//printf("                       |                      Press any key to start!                         |\n");  
//printf("                       |                                                                      |\n");  
//printf("                       ------------------------------------------------------------------------\n\n");
letreiroPrint();
getch();
limparConsole();
tutorialPrint();
getch();
limparConsole();
//usa a funcao da rota pra gerar a rota, no towerdefense so gera 1 vez a rota.
gerarRota(rota, &tamanhoRota);
desenharRota(mapaI, rota, tamanhoRota);

//inicio das funcoes do jogo/inicio do loop
while(vidaPlayer > 0 && continuar == 's'){
    
    //imprimindo o mapa
    gotoxy(0, 0);
    printMapa();
    
    printf("\n\nBase HP: %d | Money: %0.f | Round: %d", vidaPlayer, moneyPlayer, nivelPlayer);
    printf("\nTower price: %d", valorTorre);
    printf("\n\nWhat will you do next? \n1 - Place tower. \n2 - Start the wave. \n3 - Upgrade a tower. \n4 - Quit.\n\n");
    opcao = getch();


    //ve se o usuario apertou o botao de opcao certo
    if(opcao == '1' || opcao == '2' || opcao == '3' || opcao == '4' || opcao == '#'){ 
    switch(opcao){
    case '1':
    //Coloca a torre

        //ve se o usuario tem dinheiro p colocar a torre
    if (moneyPlayer >= valorTorre){
            char columnSel;
            int rowSelNum,columnSelNum;
            limparConsoleRestosMais();
            gotoxy(0, 12);
            printf("Which position do you want to place the tower? (EX:A 1)         \n");
            scanf(" %c %d", &columnSel, &rowSelNum);

            switch(columnSel){
                case 'a': columnSel = 'A'; break;
                case 'b': columnSel = 'B'; break;
                case 'c': columnSel = 'C'; break;
                case 'd': columnSel = 'D'; break;
                case 'e': columnSel = 'E'; break;                    
                case 'f': columnSel = 'F'; break;
                case 'g': columnSel = 'G'; break;
                case 'h': columnSel = 'H'; break;
                case 'i': columnSel = 'I'; break;
            }

            //troca a letra pelo numero da coluna
            switch(columnSel){
                case 'A': columnSelNum = 1; break;
                case 'B': columnSelNum = 2; break;
                case 'C': columnSelNum = 3; break;
                case 'D': columnSelNum = 4; break;
                case 'E': columnSelNum = 5; break;                    
                case 'F': columnSelNum = 6; break;
                case 'G': columnSelNum = 7; break;
                case 'H': columnSelNum = 8; break;
                case 'I': columnSelNum = 9; break;
            }

            //verifica se a coluna ta certa.
            if (columnSel !=  mapaI[0][1] && columnSel !=  mapaI[0][2] && columnSel !=  mapaI[0][3] && columnSel !=  mapaI[0][4] && columnSel !=  mapaI[0][5] && columnSel !=  mapaI[0][6] && columnSel !=  mapaI[0][7] && columnSel !=  mapaI[0][8] && columnSel !=  mapaI[0][9]){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("Invalid position.");
                break;
            }
            //verifica se ta na rota do inimigo
            if (mapaI[rowSelNum][columnSelNum] == ' '){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("This position is in the enemy route. Please pick another one.");
                break;
            }
            //ve se o usuario ta colocando a torre em cima da base
            else if (mapaI[rowSelNum][columnSelNum] == 'B'){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("You cannot place a tower here because your base is in this position.\n");
                break;
            }
            else if (mapaI[rowSelNum][columnSelNum] == 't' || mapaI[rowSelNum][columnSelNum] == 'T' ){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("You cannot place a tower here because there is already a tower here.\n");
                break;
            }
            //se todas verificacoes tiverem certas ele coloca a torre
            else {
                // Colocar a torre
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                ultimaTorreColocada++;
                mapaI[rowSelNum][columnSelNum] = 't'; 
                torre[ultimaTorreColocada].danoTorre = 5;
                torre[ultimaTorreColocada].x = rowSelNum;
                torre[ultimaTorreColocada].y = columnSelNum;
                torre[ultimaTorreColocada].alcance = 1;
                torre[ultimaTorreColocada].valorPagoTorre = valorTorre;
                mapaTorres[rowSelNum][columnSelNum] = ultimaTorreColocada;
                moneyPlayer = moneyPlayer - valorTorre;
                printf("Tower positioned in column %c, row %d\n", columnSel, rowSelNum);
            }
        }
        else {
            limparConsole();
            gotoxy(0, 20);
            printf("You are out of founds.\n");
        }
        break;

    case '2':
    //Comeca a wave, aqui vai demorar
        waveProgress = 0;

        while(waveProgress < 100){

        if(nivelPlayer == 1) {
            numInimigos = 1;
        }
        if(nivelPlayer >= 2){
            vidaRound = vidaRound * 1.10;
            numInimigos = 1;
        }
        if (nivelPlayer >= 10){
            vidaRound = vidaRound * 1.10;
            numInimigos = 2;
        }
        if (nivelPlayer >= 20){
            vidaRound = vidaRound * 1.15;
            numInimigos = 3;
        }
        if (nivelPlayer >= 30){
            vidaRound = vidaRound * 1.20;
            numInimigos = 4;
        }
        if (nivelPlayer >= 40){
            vidaRound = vidaRound * 1.25;
            numInimigos = 5;
        }
        
        numTotalInimigosWave = numInimigos;

        
        //define p todos os inimigos os padroes
        for(int i = 0; i < numInimigos; i++) {
        vidaDoInimigo[i] = 0;
        inimigo[i].vida = vidaRound;
        inimigo[i].x = 1;
        inimigo[i].y = 1;
        }
        //dano do inimigo
        danoInimigo = inimigo->vida;
        
            while(numInimigos > 0) {
            for(int inimigosVzs = 0; inimigosVzs < numTotalInimigosWave; inimigosVzs++) {
                //bixo meche

                if (inimigo[inimigosVzs].vida > 0) {

                    if (mapaI[inimigo[inimigosVzs].x][inimigo[inimigosVzs].y] == 'N') {
                        mapaI[inimigo[inimigosVzs].x][inimigo[inimigosVzs].y] = ' ';
                    }

                    if (mapaI[inimigo[inimigosVzs].x + 1][inimigo[inimigosVzs].y] == ' ' || mapaI[inimigo[inimigosVzs].x + 1][inimigo[inimigosVzs].y] == 'B') {
                        inimigo[inimigosVzs].x++;
                        delay(350);
                    }
                    else if (mapaI[inimigo[inimigosVzs].x][inimigo[inimigosVzs].y + 1] == ' ' || mapaI[inimigo[inimigosVzs].x][inimigo[inimigosVzs].y + 1] == 'B'){
                        inimigo[inimigosVzs].y++;
                        delay(350);
                    }

                    mapaI[inimigo[inimigosVzs].x][inimigo[inimigosVzs].y] = 'N';
                    

                    for(int k = 0; k <= ultimaTorreColocada; k++) {
                        if(torreVeInimigo(&torre[k], &inimigo[inimigosVzs])) {
                            vidaDoInimigo[k] = inimigo[inimigosVzs].vida;
                            inimigo[inimigosVzs].vida -= torre[k].danoTorre;

                            if (inimigo[inimigosVzs].vida <= 0) {
                                mapaI[inimigo[inimigosVzs].x][inimigo[inimigosVzs].y] = ' ';
                                inimigo[inimigosVzs].x = inimigo[inimigosVzs].y = 10;
                                numInimigos--;
                                gotoxy(0, 11);
                                printf("\nEnemy killed!");
                                limparConsoleRestosMais();
                            }
                        }
                    }
                    vidaDoInimigo[inimigosVzs] = inimigo[inimigosVzs].vida;

                    if(inimigo[inimigosVzs].x == 9 && inimigo[inimigosVzs].y == 9) {
                    mapaI[inimigo[inimigosVzs].x][inimigo[inimigosVzs].y] = 'B';
                    vidaPlayer = vidaPlayer - vidaDoInimigo[inimigosVzs];
                    numInimigos--;
                    if(vidaPlayer <= 0) perdeu = perdeu + 1;
                    gotoxy(0, 20);
                    printf("The enemy hit your base, you received %d points of damage!", inimigo[inimigosVzs].vida);
                    inimigo[inimigosVzs].vida = 0;
                }
                    limparConsole();
                    printMapa();
                    gotoxy(0, 12);
                    for(int i = 0; i < numTotalInimigosWave; i++) {
                    printf("Enemy n%d HP: %d | ", i+1, inimigo[i].vida, torreVeInimigo(&torre[ultimaTorreColocada], &inimigo[inimigosVzs]));
                    //printf("\nDano que a base vai tomar %0.2f", vidaDoInimigo[inimigosVzs]);
                    }
                }
            }

            //se inimigos acabarem, acaba a wave
            if(numInimigos <= 0) {
                waveProgress = 100;
                limparConsole();
                printMapa();
                gotoxy(0, 21);
                printf("\nYou won wave number: %d", nivelPlayer);
            }
        }

        //faz a modificacao do valor da torre referente ao round q a pessoa ta
        valorTorre = 40 * nivelPlayer;
        ganhoRound = 50 * (numTotalInimigosWave*nivelPlayer * 0.5);
        gotoxy(0, 20);
        printf("\nMoney earned in this wave: %d", ganhoRound);
        moneyPlayer += ganhoRound;
        nivelPlayer = nivelPlayer + 1;
    } 
    break;
    case '3':
    //upgrade da torre peco perdao pq aqui eu ja parei de comentar tava maluco
        if(moneyPlayer > 0){
        char columnSel;
        int rowSelNum,columnSelNum, torreMexendo = 0;
        limparConsoleRestosMais();
        gotoxy(0, 12);
        printf("What tower do you want to upgrade? (EX:A 1)         \n");
        scanf(" %c %d", &columnSel, &rowSelNum);

        switch(columnSel){
            case 'a': columnSel = 'A'; break;
            case 'b': columnSel = 'B'; break;
            case 'c': columnSel = 'C'; break;
            case 'd': columnSel = 'D'; break;
            case 'e': columnSel = 'E'; break;                    
            case 'f': columnSel = 'F'; break;
            case 'g': columnSel = 'G'; break;
            case 'h': columnSel = 'H'; break;
            case 'i': columnSel = 'I'; break;
        }

        //troca a letra pelo numero da coluna
        switch(columnSel){
            case 'A': columnSelNum = 1; break;
            case 'B': columnSelNum = 2; break;
            case 'C': columnSelNum = 3; break;
            case 'D': columnSelNum = 4; break;
            case 'E': columnSelNum = 5; break;                    
            case 'F': columnSelNum = 6; break;
            case 'G': columnSelNum = 7; break;
            case 'H': columnSelNum = 8; break;
            case 'I': columnSelNum = 9; break;
        }
            torreMexendo = mapaTorres[rowSelNum][columnSelNum];
            valorUpgrade = torre[torreMexendo].valorPagoTorre*4;

            //verifica se a coluna ta certa.
            if (columnSel !=  mapaI[0][1] && columnSel !=  mapaI[0][2] && columnSel !=  mapaI[0][3] && columnSel !=  mapaI[0][4] && columnSel !=  mapaI[0][5] && columnSel !=  mapaI[0][6] && columnSel !=  mapaI[0][7] && columnSel !=  mapaI[0][8] && columnSel !=  mapaI[0][9]){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("Invalid position.");
                break;
            }
            if (mapaI[rowSelNum][columnSelNum] != 't' && mapaI[rowSelNum][columnSelNum] != 'T' && mapaI[rowSelNum][columnSelNum] != 'W'){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("There is no tower in this position.");
                break;
            }
            if (mapaI[rowSelNum][columnSelNum] == 'W'){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("You already have max upgraded tower in this position.");
                break;
            }
            if(mapaI[rowSelNum][columnSelNum] == 't'){
                if(moneyPlayer < valorUpgrade){
                    limparConsole();
                    limparConsoleRestosMenos();
                    gotoxy(0, 20);
                    printf("You don't have enough money. Upgrade price: %d", valorUpgrade);
                    break;
                }
                else{
                    // Upgrade da torre
                    char intOpcaoUpg = ' ';
                    limparConsoleRestosMais();
                    gotoxy(0, 13);
                    do {
                    printf("Upgrade price: %d, do you really want to continue? *Upgrade LVL 2* (s/n)", valorUpgrade);
                    intOpcaoUpg = getch();

                        if(intOpcaoUpg == 's'){
                            torre[torreMexendo].alcance = 3;
                            torre[torreMexendo].danoTorre = torre[torreMexendo].danoTorre*4;
                            mapaI[rowSelNum][columnSelNum] = 'T';
                            moneyPlayer = moneyPlayer - valorTorre;
                            limparConsoleRestosMais();
                            gotoxy(0, 13);
                            printf("Tower upgraded successfully. You now have %f money.", moneyPlayer);
                            delay(2000);
                            limparConsoleRestosMais();
                            break;
                        }
                        else if (intOpcaoUpg == 'n'){
                            limparConsoleRestosMais();
                            gotoxy(0, 13);
                            printf("Action cancelled successfully. You still have %f money.", moneyPlayer);
                            delay(2000);
                            limparConsoleRestosMais();
                            break;
                        }
                        else{
                            limparConsoleRestosMais();
                            gotoxy(0, 13);
                            printf("Invalid option.");
                        }
                    } while ((intOpcaoUpg != 's') && (intOpcaoUpg != 'n'));
                }
            } else if (mapaI[rowSelNum][columnSelNum] == 'T'){
                valorUpgrade = valorUpgrade * 3;
                if(moneyPlayer < valorUpgrade){
                    limparConsole();
                    limparConsoleRestosMenos();
                    gotoxy(0, 20);
                    printf("You don't have enough money. Upgrade price: %d", valorUpgrade);
                    break;
                }
                else{
                    // Upgrade da torre
                    char intOpcaoUpg = ' ';
                    limparConsoleRestosMais();
                    gotoxy(0, 13);
                    do {
                    printf("Upgrade price: %d, do you really want to continue? *Upgrade LVL 3* (s/n)", valorUpgrade);
                    intOpcaoUpg = getch();

                        if(intOpcaoUpg == 's'){
                            torre[torreMexendo].alcance = 3;
                            torre[torreMexendo].danoTorre = torre[torreMexendo].danoTorre*5;
                            mapaI[rowSelNum][columnSelNum] = 'W';
                            moneyPlayer = moneyPlayer - valorTorre;
                            limparConsoleRestosMais();
                            gotoxy(0, 13);
                            printf("Tower upgraded successfully. You now have %f money.", moneyPlayer);
                            delay(2000);
                            limparConsoleRestosMais();
                            break;
                        }
                        else if (intOpcaoUpg == 'n'){
                            limparConsoleRestosMais();
                            gotoxy(0, 13);
                            printf("Action cancelled successfully. You still have %f money.", moneyPlayer);
                            delay(2000);
                            limparConsoleRestosMais();
                            break;
                        }
                        else{
                            limparConsoleRestosMais();
                            gotoxy(0, 13);
                            printf("Invalid option.");
                        }
                    } while ((intOpcaoUpg != 's') && (intOpcaoUpg != 'n'));
                }
            }
        }
        else{
            limparConsoleRestosMenos();
            gotoxy(0, 20);
            printf("You dont have any money. YOU ARE BROKE");
        }
    break;
    case '4':
    //Sair do jogo
    char intOpcaoUpg = ' ';
    limparConsoleRestosMais();
    do {
        gotoxy(0, 13);
        printf("Do you really want to quit? (s/n)");
        intOpcaoUpg = getch();
        if(intOpcaoUpg == 's'){
            continuar = 'n';
            limparConsole();
            //Letreiro de saida
            gotoxy(0,0);
            letreiroPrint();
            gotoxy(23, 19);
            printf("|                          Obrigado por jogar                          |");
            gotoxy(23, 20);
            printf("|                      Sua pontuacao foi de %0.f                       ", moneyPlayer*nivelPlayer);
            gotoxy(94, 20);
            printf("|");
            gotoxy(23, 21);
            printf("------------------------------------------------------------------------\n\n");
            getch();
            system("exit"); 
        }
        else if (intOpcaoUpg == 'n'){
            limparConsoleRestosMais();
            gotoxy(0, 13);
            printf("Action cancelled successfully.");
            delay(2000);
            limparConsoleRestosMais();
        }
        else{
            limparConsoleRestosMais();
            gotoxy(0, 12);
            printf("Invalid option.");
        }
    } while ((intOpcaoUpg != 's') && (intOpcaoUpg != 'n'));
    break;
    case '#':
    //debug
        moneyPlayer = moneyPlayer + 420420;
         vidaPlayer = vidaPlayer + 420420;
        nivelPlayer = nivelPlayer + 5;
    break;
    }
    }
    
    //informa q ele apertou o botao errado ou de nenhuma funcao
    else {
        limparConsole();
        gotoxy(0, 20);
        printf("Invalid option.");
        printf("%c", opcao);
    }
}   if(perdeu == 1){
        limparConsole();
        //Letreiro de saida
        gotoxy(0,0);
        letreiroPrint();
        gotoxy(23, 19);
        printf("|                            Voce perdeu :(                            |\n");
        gotoxy(23, 20);
        printf("|                      Sua pontuacao foi de %0.f                       ", moneyPlayer*nivelPlayer); 
        gotoxy(94, 20);
        printf("|");
        gotoxy(23, 21);
        printf("|                          Obrigado por jogar                          |");
        gotoxy(23, 22);
        printf("------------------------------------------------------------------------\n\n");
        getch();
        system("exit");
        }
}