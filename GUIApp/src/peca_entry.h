#include "gui/guiapp_resources.h"

extern int y;
extern int x;
extern GX_RESOURCE_ID matriz[20][10];
extern bool matriz_consulta[20][10];
extern void pintaBloco(GX_RESOURCE_ID id);
extern void limpaBloco(GX_RESOURCE_ID id);
extern short linha;
extern void limpaLinha(int lim);
extern bool i;
extern short col;
extern void limpaTela();
extern void trocaTela(GX_RESOURCE_ID id);
extern bool t;
extern int peca2;
extern int peca1;
extern void update_score(GX_RESOURCE_ID id, int string_id);
extern int pontuacao;
extern int mult;
