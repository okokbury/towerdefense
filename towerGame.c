#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


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
int vida, money, nivel;
char continuar = 's';
char opcao;

system("cls");

//Inicio do jogo
//Letreiro                                                                                      
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
printf("                       |                      Press any key to start!                         |\n");  
printf("                       |                                                                      |\n");  
printf("                       ------------------------------------------------------------------------\n\n");     
getch();

//while(continuar == 's'){}

system("cls");

//imprimindo o mapa base
for(int i=0;i<10;i++){
    printf("\n");
    for(int j=0;j<10;j++){
            printf("%c ", mapaI[i][j]);
    }
}

printf("\n\nVida da base: %d | Dinheiro: %d | Nivel: %d", vida, money, nivel);
printf("\n\nO que deseja fazer? \n1 - Colocar torre. \n2 - Comecar wave. \n3 - Sair.\n");
opcao = getch();

switch(opcao){
    //Coloca a torre
    case '1': 
    char columnSel;
    int rowSelNum,columnSelNum;
    printf("Qual posicao voce quer colocar a torre? (EX:A 1)\n");
    scanf(" %c %d", &columnSel, &rowSelNum);

    //verifica se a coluna ta certa.
    if (columnSel !=  mapaI[0][1] && columnSel !=  mapaI[0][2] && columnSel !=  mapaI[0][3] && columnSel !=  mapaI[0][4] && columnSel !=  mapaI[0][5] && columnSel !=  mapaI[0][6] && columnSel !=  mapaI[0][7] && columnSel !=  mapaI[0][8] && columnSel !=  mapaI[0][9]){
        printf("Posicao invalida");
        break;
    }

    //troca a letra pelo numero da coluna
    switch(columnSel){
        case 'A':
        columnSelNum = 1; 
        break;
        case 'B':
        columnSelNum = 2; 
        break;
        case 'C':
        columnSelNum = 3; 
        break;
        case 'D':
        columnSelNum = 4; 
        break;
        case 'E':
        columnSelNum = 5; 
        break;
        case 'F':
        columnSelNum = 6; 
        break;
        case 'G':
        columnSelNum = 7; 
        break;
        case 'H':
        columnSelNum = 8; 
        break;
        case 'I':
        columnSelNum = 9; 
        break;
    }

    //verifica se ta na rota do inimigo
    if (mapaI[rowSelNum][columnSelNum] == ' '){
        printf("Posicao esta na rota do inimigo. Por favor escolha outra posicao.");
    }
    
    //confirmando onde o usuario escolheu
    printf("Colocando a torre na coluna %c, linha %d", columnSel, rowSelNum);
    
    break;
    case '2':
    break;
    case '3':
    break;
}



}