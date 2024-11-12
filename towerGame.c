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
    } Torre;
    
    //funcao de delay
    void delay(int milliseconds) {
    struct timespec req;
    req.tv_sec = milliseconds / 1000;  // segundos
    req.tv_nsec = (milliseconds % 1000) * 1000000;  // nanosegundos

    nanosleep(&req, NULL);  // Chama o nanosleep
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
int vidaPlayer, moneyPlayer, nivelPlayer, valorTorre, valorPagoTorre, valorUpgrade, tamanhoRota, ganhoRound, perdeu, ganhou;
int vidaRound, danoInimigo, maxTorres, ultimaTorreColocada, inimigoNoMapa;
int mapaTorres[9][9]={0};
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
ganhoRound = 50;
vidaRound = 5;
ultimaTorreColocada = -1;
inimigoNoMapa = 0;
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
//usa a funcao da rota pra gerar a rota, no towerdefense so gera 1 vez a rota.
gerarRota(rota, &tamanhoRota);
desenharRota(mapaI, rota, tamanhoRota);

//inicio das funcoes do jogo/inicio do loop
while(vidaPlayer > 0 && continuar == 's'){
    
    //imprimindo o mapa
    gotoxy(0, 0);
    printMapa();
    
    printf("\n\nBase HP: %d | Money: %d | Round: %d", vidaPlayer, moneyPlayer, nivelPlayer);
    printf("\nTower price: %d", valorTorre);
    printf("\n\nWhat will you do next? \n1 - Place tower. \n2 - Start the wave. \n3 - Upgrade a tower. \n4 - Quit.\n\n");
    opcao = getch();


    //ve se o usuario apertou o botao de opcao certo
    if(opcao == '1' || opcao == '2' || opcao == '3' || opcao == '4'){ 
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
        //scaling de vida
        if(nivelPlayer == 1) vidaRound = 5;
        else vidaRound = vidaRound * 1.25;

        inimigo->vida = vidaRound;
        inimigo->x = 1;
        inimigo->y = 1;
        //dano do inimigo
        danoInimigo = inimigo->vida;
        
        //faz o inimigo mecher e vai ter
        while(inimigo->vida  > 0){
            while(inimigo->x < 9 && inimigo->y < 9){
                //fazer enemego mexer
                for (int i = 1; i < TAM_MAPA; i++) {
                    for(int j = 1; j < TAM_MAPA; j++){
                        //transformar o ultimo caractere andado em espaco vazio dnv
                        if (j>=1 && i>=1 && mapaI[inimigo->x][inimigo->y] == 'N') {
                            mapaI[inimigo->x][inimigo->y] = ' ';
                        }
                        if (mapaI[i][j] == ' ' || mapaI[i][j] == 'B') { //marcando o caminho q o inimigo vai passar
                            mapaI[i][j] = 'N';
                            inimigo->x = i;
                            inimigo->y = j;
                            
                            limparConsole();
                            printMapa();
                            //bater no enemego
                            gotoxy(0, 12);
                            printf("Vida atual do inimigo %d", inimigo->vida);

                            for(int k = 0; k <= ultimaTorreColocada; k++ ) {
                                if ((torre[k].x - inimigo->x) <= torre[k].alcance && (torre[k].y - inimigo->y) <= torre[k].alcance) {
                                    inimigo->vida = inimigo->vida - torre[k].danoTorre;
                                    
                                    if (inimigo->vida <= 0) {
                                        i = j = TAM_MAPA;
                                        mapaI[inimigo->x][inimigo->y] = ' ';
                                        inimigo->x = inimigo->y = 11;
                                        limparConsoleRestosMenos();
                                        gotoxy(0, 21);
                                        printf("\nYou won wave number: %d", nivelPlayer);
                                    }
                                }
                            }
                            delay(400);
                        }
                    }
            if(inimigo->x == 9 && inimigo->y == 9) {
                mapaI[inimigo->x][inimigo->y] = 'B';
                gotoxy(0, 21);
                vidaPlayer = vidaPlayer - danoInimigo;
                if(vidaPlayer <= 0) perdeu = perdeu + 1;
                printf("\nThe enemy hit your base, you received %d points of damage!                 ", danoInimigo);
                inimigo->vida = 0;
            }
        }
        }
        }
        //faz a modificacao do valor da torre referente ao round q a pessoa ta
        valorTorre = 40*nivelPlayer;
        ganhoRound = 50*(nivelPlayer*0.5);
        gotoxy(0, 20);
        printf("\nMoney earned in this wave %d", ganhoRound);
        moneyPlayer = moneyPlayer + ganhoRound;
        nivelPlayer++;
    break;
    case '3':
    //upgrade da torre peco perdao pq aqui eu ja parei de comentar tava maluco
        if(moneyPlayer > 0){
        char columnSel;
        int rowSelNum,columnSelNum, torreMexendo;
        limparConsoleRestosMais();
        gotoxy(0, 12);
        printf("Which position do you want to place the tower? (EX:A 1)         \n");
        scanf(" %c %d", &columnSel, &rowSelNum);

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
            if (mapaI[rowSelNum][columnSelNum] != 't' && mapaI[rowSelNum][columnSelNum] != 'T'){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("There is no tower in this position.");
                break;
            }
            if (mapaI[rowSelNum][columnSelNum] == 'T'){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("You already have upgraded tower in this position.");
                break;
            } 
            if(moneyPlayer < valorUpgrade){
                limparConsole();
                limparConsoleRestosMenos();
                gotoxy(0, 20);
                printf("You don't have enough money.");
                break;
            }
            else{
                // Upgrade da torre
                
                valorUpgrade = torre[torreMexendo].valorPagoTorre*2;
                mapaTorres[rowSelNum][columnSelNum] = torreMexendo;
                torre[torreMexendo].alcance = 2;
                torre[torreMexendo].danoTorre = torre[torreMexendo].danoTorre*2;
                mapaI[rowSelNum][columnSelNum] = 'T';
                moneyPlayer = moneyPlayer - valorTorre;
                limparConsoleRestosMais();
                gotoxy(0, 13);
                printf("Tower upgraded successfully. You now have %d money.", moneyPlayer);
                delay(2000);
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

        continuar = 'n';
        limparConsole();
        //Letreiro de saida
        gotoxy(0,0);
        letreiroPrint();
        gotoxy(23, 19);
        printf("|                          Obrigado por jogar                          |");
        printf("|                      Sua pontuacao foi de %d                       ", nivelPlayer*moneyPlayer*1500); 
        gotoxy(94, 20);
        printf("|");
        gotoxy(23, 21); 
        gotoxy(23, 21);
        printf("------------------------------------------------------------------------\n\n");
        getch();
        system("exit"); 
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
        printf("|                      Sua pontuacao foi de %d                       ", nivelPlayer*moneyPlayer*1500); 
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