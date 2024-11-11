#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//globais 
#define TAM_MAPA 10
#define MAX_INIMIGOS 5
#define TAM_MAX_ROTA 20
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
typedef struct {
    int x;
    int y;
} PontoRota;

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

void desenharRota(char mapaI[TAM_MAPA][TAM_MAPA], PontoRota* rota, int tamanhoRota) {
    for (int i = 0; i < tamanhoRota; i++) {
        int x = rota[i].x;
        int y = rota[i].y;
        if (mapaI[x][y] == '/') { //marcando o caminho q o inimigo vai passar
            mapaI[x][y] = ' ';
        }
    }
}

//funcao pra mexer o bicho
void moverInimigo(Inimigo* inimigo) {
    }

//checar se ta livre o caminho
int posicaoLivre(int x, int y){
    return (x >= 0 && x < TAM_MAPA && y >= 0 && y < TAM_MAPA && mapaI[x][y] != 'T' && mapaI[x][y] != 'B');
}

//funcao pra limpar o console win e linux
void limparConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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

int main(){

//Variaveis
int vidaPlayer, moneyPlayer, nivelPlayer, valorTorre, tamanhoRota, round;
char opcao;
char continuar = 's';
PontoRota rota[TAM_MAX_ROTA];

//definicoes padrao:
vidaPlayer = 100;
moneyPlayer = 50;
nivelPlayer = 1;
valorTorre = 25;
round = 1;


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

//inicio das funcoes do jogo
while(continuar == 's'){
    gotoxy(0, 0);
    
    //imprimindo o mapa
    for(int i=0;i<10;i++){
        printf("\n");
        for(int j=0;j<10;j++){
                printf("%c ", mapaI[i][j]);
        }
    }
    

    printf("\n\nBase HP: %d | Money: %d | Round: %d", vidaPlayer, moneyPlayer, nivelPlayer);
    printf("\nTower price: %d", valorTorre);
    printf("\n\nWhat will you do next? \n1 - Place tower. \n2 - Start the wave. \n3 - Quit.\n");
    opcao = getch();


    //ve se o usuario apertou o botao de opcao certo
    if(opcao == '1' || opcao == '2' || opcao == '3'){ 
    switch(opcao){
    case '1':
    //Coloca a torre


        //ve se o usuario tem dinheiro p colocar a torre
        if (moneyPlayer >= valorTorre){
            char columnSel;
            int rowSelNum,columnSelNum;
            gotoxy(0, 19);
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
                gotoxy(0, 19);
                printf("Invalid position.");
                break;
            }
            //verifica se ta na rota do inimigo
            if (mapaI[rowSelNum][columnSelNum] == ' '){
                limparConsole();
                gotoxy(0, 19);
                printf("This position is in the enemy route. Please pick another one.");
                break;
            }
            //ve se o usuario ta colocando a torre em cima da base
            else if (mapaI[rowSelNum][columnSelNum] == 'B'){
                limparConsole();
                gotoxy(0, 19);
                printf("You cannot place a tower here because your base is in this position.\n");
                break;
            }
            //se todas verificacoes tiverem certas ele coloca a torre
            else {
                // Colocar a torre
                limparConsole();
                gotoxy(0, 19);
                mapaI[rowSelNum][columnSelNum] = 'T'; 
                moneyPlayer = moneyPlayer - valorTorre;
                printf("Tower positioned in column %c, row %d\n", columnSel, rowSelNum);
            }
        }
        else {
            limparConsole();
            gotoxy(0, 19);
            printf("You are out of founds.\n");
        }
        break;

    case '2':
    //Comeca a wave, aqui vai demorar

        //faz a modificacao do valor da torre referente ao round q a pessoa ta
        valorTorre = 40*(nivelPlayer*0.7);
        nivelPlayer++;
    break;

    case '3':
    //Sair do jogo

        continuar = 'n';
        limparConsole();
        //Letreiro de saida
        gotoxy(0,0);
        letreiroPrint();
        gotoxy(23, 19);
        printf("|                          Obrigado por jogar                          |");
        gotoxy(23, 20);
        printf("|                                                                      |\n"); 
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
        gotoxy(0, 19);
        printf("Invalid option.");
    }
}
}