#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(){

char mapaI[10][10] = {
        {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '/', '/', '/', '/', '/', '/', '/', '/', '/'},
        {'2', '/', '/', '/', '/', '/', '/', '/', '/', '/'},
        {'3', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'4', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'5', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'6', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'7', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'8', '/', '/', '/', '/', '/', '/', '/', '/', '/'}, 
        {'9', '/', '/', '/', '/', '/', '/', '/', '/', '/'}  
    };


//Inicio do jogo
//Letreiro
printf("     |xxxxxxxxxxx| |wwwwwwx| |xxx| |xxx| |xxxxx| |xxxxxx|\n");       
printf("     |           | |       | |   |x|   | |     | |  xxxx|\n");       
printf("     |xxx|   |xxx| |  xxx  | |   | |   | | xxxx| |  |    \n");       
printf("         |   |     |  x x  | |   | |   | |    |  |  |    \n");       
printf("         |   |     |  xxx  | |         | | xxxx| |  |    \n");       
printf("         |   |     |       | |         | |     | |  |    \n");       
printf("         |xxx|     |xxxxxxx| |xxxxxxxxx| |xxxxx| |xx|    \n\n");     
                                                                             
printf("|xxxxx|  |xxxxxx| |xxxxxx| |xxxxxx| |xxxx|x| |xxxxxx| |xxxxxx|\n");  
printf("|     || |      | |      | |      | |    | | |      | |      |\n");  
printf("| xxx  | | xxxxx| | xxxxx| | xxxxx| |    | | |  xxxx| | xxxxx|\n");  
printf("| x x  | |    |   |     |  |    |   | |  | | |      | |    |  \n");  
printf("| xxx  | | xxxxx| | xxxx|  | xxxxx| | |    | |xxxxx | | xxxxx|\n");  
printf("|      | |      | | |      |      | | |    | |      | |      |\n");  
printf("|     || |      | | |      |      | | |    | |      | |      |\n");
printf("|XXXXX|  |XXXXXX| |X|      |XXXXXX| |X|XXXX| |XXXXXX| |XXXXXX|\n\n");
printf("                      Press any key to start!                     ");      
getch();



    for(int i=0;i<10;i++){
        printf("\n");
        for(int j=0;j<10;j++){
            printf("%c ", mapaI[i][j]);
        }
    }

}