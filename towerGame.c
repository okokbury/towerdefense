#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void limparConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

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

char mapaI[10][10] = {
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
int vidaPlayer, moneyPlayer, nivelPlayer, valorTorre;
char opcao;
char continuar = 's';

//definicoes padrao:
vidaPlayer = 100;
moneyPlayer = 50;
nivelPlayer = 1;
valorTorre = 25;

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

while(continuar == 's'){
    gotoxy(0, 0);
    //imprimindo o mapa base
    for(int i=0;i<10;i++){
        printf("\n");
        for(int j=0;j<10;j++){
                printf("%c ", mapaI[i][j]);
        }
    }

    printf("\n\nBase HP: %d | Money: %d | Round: %d", vidaPlayer, moneyPlayer, nivelPlayer);
    printf("\n\nWhat will you do next? \n1 - Place tower. \n2 - Start the wave. \n3 - Quit.\n");
    opcao = getch();

    //ve se o usuario apertou o botao de opcao certo
    if(opcao == '1' || opcao == '2' || opcao == '3'){ 
    switch(opcao){
    case '1':
    //Coloca a torre
    
        //faz a modificacao do valor da torre referente ao round q a pessoa ta
        if(nivelPlayer == 1){
            valorTorre = 25;
        }
        else {
            valorTorre = valorTorre*(nivelPlayer*0,60);
        }
     
        if (moneyPlayer >= valorTorre){
            char columnSel;
            int rowSelNum,columnSelNum;
            gotoxy(0, 19);
            printf("Which position do you want to place the tower? (EX:A 1)\n");
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
            else if (mapaI[rowSelNum][columnSelNum] == 'B'){
                limparConsole();
                gotoxy(0, 19);
                printf("You cannot place a tower here because your base is in this position.\n");
                break;
            }
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
            printf("Tower price is %d\n", valorTorre);
            printf("You are out of founds.\n");
        }
        break;

    case '2':
    //Comecar a wave, aqui vai demorar
        nivelPlayer++;
    break;

    case '3':
    //Sair  
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
    //informa q ele selecionou o botao errado
    else {
        limparConsole();
        gotoxy(0, 19);
        printf("Invalid option.");
    }
}
}