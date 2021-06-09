#include "quadrado.h"
#include "peca_entry.h"
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <stdlib.h>
#include <unistd.h>

//as funções abaixo são puramente manipulação de coordenadas
//foram feitas com auxilio de desenhos para entender melhor a movimentação
void caiQuadrado(){
       if((y==0||y==2)&&matriz_consulta[y][x]==1&&matriz_consulta[y][x+1]==1){
           limpaTela();
           gx_system_canvas_refresh();
           t=1;
           i=0;
       }
       else if(y==0){
            pintaBloco(matriz[y][x]);
            pintaBloco(matriz[y][x+1]);
            matriz_consulta[y][x]=1;
            matriz_consulta[y][x+1]=1;
            gx_system_canvas_refresh();
            y++;
        }
        else if(y==1){
            pintaBloco(matriz[y][x]);
            pintaBloco(matriz[y][x+1]);
            matriz_consulta[y][x]=1;
            matriz_consulta[y][x+1]=1;
            gx_system_canvas_refresh();
            y++;
        }
        else if(y==20||matriz_consulta[y][x]==1||matriz_consulta[y][x+1]==1)
        {
            y=0;
            x=4;
            peca1 = peca2;
            peca2 = rand()%7;
            for(int c=19;c>=0;c--){
                for (int d=0; d<10;d++){
                    linha=linha+matriz_consulta[c][d];
                }
                if(linha==10){
                    limpaLinha(c);
                    gx_system_canvas_refresh();
                    c++;
                    mult++;
                    pontuacao+=10*mult;
                    update_score(ID_PONTUACAO, pontuacao);
                }
            linha=0;
            }
        }
        else{
            limpaBloco(matriz[y-2][x]);
            limpaBloco(matriz[y-2][x+1]);
            matriz_consulta[y-2][x]=0;
            matriz_consulta[y-2][x+1]=0;
            pintaBloco(matriz[y][x]);
            pintaBloco(matriz[y][x+1]);
            matriz_consulta[y][x]=1;
            matriz_consulta[y][x+1]=1;
            gx_system_canvas_refresh();
            y++;
        }
}

void moveQuadradoEsquerda(){
    if(x>0&&
        matriz_consulta[y-2][x-1]==0&&
        matriz_consulta[y-1][x-1]==0){
        pintaBloco(matriz[y-2][x-1]);
        pintaBloco(matriz[y-1][x-1]);
        limpaBloco(matriz[y-1][x+1]);
        limpaBloco(matriz[y-2][x+1]);
        matriz_consulta[y-2][x-1]=1;
        matriz_consulta[y-1][x-1]=1;
        matriz_consulta[y-1][x+1]=0;
        matriz_consulta[y-2][x+1]=0;
        x--;
    }
}

void moveQuadradoDireita(){
    if(x<8&&
        matriz_consulta[y-2][x+2]==0&&
        matriz_consulta[y-1][x+2]==0){
        pintaBloco(matriz[y-2][x+2]);
        pintaBloco(matriz[y-1][x+2]);
        limpaBloco(matriz[y-1][x]);
        limpaBloco(matriz[y-2][x]);
        matriz_consulta[y-2][x+2]=1;
        matriz_consulta[y-1][x+2]=1;
        matriz_consulta[y-1][x]=0;
        matriz_consulta[y-2][x]=0;
        x++;
    }
}
