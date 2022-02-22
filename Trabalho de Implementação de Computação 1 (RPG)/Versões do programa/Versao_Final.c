#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int hp, dano, acerto, evasao, defesa, pontuacao = 0;
int idano, iacerto, ihp;
char item1[100], item2[100], player[51];
FILE *pa; //o jogo cria um arquivo de texto denominado 'pontuacao.txt'. esse arquivo eh usado para guardar o nome e a pontuacao do jogador.
double hpmax;

void atkinimigo(int idano, int iacerto, int evasao, int defesa) //a funcao atkinimigo eh usada para determinar se, quando o inimigo ataca, ele eh capaz de acertar o jogador e, caso seja,
                                //causa dano diretamente aos pontos de vida do jogador. a funcao faz uso de numeros aleatorios para determinar se o inimigo
{                                                   //erra ou acerta. alem disso, a funcao eh do tipo void, pois nao precisa retornar nenhum valor.
  int hit;
  hit = rand() % 101;
  if (hit <= iacerto)
  {
    hit = rand() % 101;
    if (hit>=evasao)
    {
      hp =hp - (idano - defesa);
      printf ("Voce foi acertado!\n");
    }
    else
      printf("Voce se esquivou do ataque!\n");
  }
  else
    printf("O inimigo errou o ataque!\n");
}

void atkjogador(int dano, int acerto) //a funcao atkjogador serve quase o mesmo proposito que atkinimigo, mas neste caso ela serve para determinar se o jogador eh capaz de acertar o
{                   //inimigo. novamente a funcao e void por nao precisar retornar valor, e faz uso de numeros gerados aleatoriamente para determinar o erro ou acerto.
  int hit;
  hit = rand() % 101;
  if (hit <= acerto)
  {
    ihp = ihp - dano*0.4;
    if (ihp<0)
      ihp = 0;
    printf("\nVoce acertou o ataque!\nA vida inimiga eh: %d\n", ihp);
  }
  else
    printf("\nVoce errou o Ataque!\n");
}

int item()  //a funcao item eh usada para o jogador usar itens que o ajudem durante o combate. a pocao restaura os pontos de vida do jogador, enquanto que a bomba causa dano direto ao
{           //inimigo. essa funcao eh do tipo int, para determinar se o jogador digitou corretamente os comandos para usar o item. caso nao tenha, nao acontece nada. caso tenha, o item
  char yn;  //eh utilizado e desaparece. cada jogador tem direito a uma bomba e uma pocao por vez.
  if (item1[0] == '\0' && item2[0] == '\0')
  {
    printf("\nNao ha itens disponiveis.\n\n");
    return -1;
  }
  if (item1[0] != '\0' && item2[0] != '\0')
  {
    printf("Itens disponiveis:\nPocao - Restaura pontos de vida\nBomba - Causa dano ao inimigo\nUsar algum item(S/N) ? \n");
    scanf("%c", &yn);
    getchar();
    if (yn == 's' || yn == 'S')
    {
      printf("Qual item? (P/B)\n");
      scanf("%c", &yn);
      getchar();
      if (yn == 'P' || yn == 'p')
      {
        item1[0] = '\0';
        hp = hp + 15;
        if (hp>hpmax)
          hp = hpmax;
        printf("Vida restaurada! Vida atual: %d\n\n", hp);
        return 0;
      }
      if (yn == 'B' || yn == 'b')
      {
        item2[0] = '\0';
        ihp = ihp - 7;
        if (ihp<0)
          ihp = 0;
        printf("O inimigo sofreu dano!\n");
        printf("A vida inimiga eh: %d\n\n", ihp);
        return 0;
      }
    }
    else
    {
      getchar();
      return -1;
    }
  }
  if (item1[0] != '\0' && item2[0] == '\0')
  {
    printf("Item disponivel:\nPocao - Restaura pontos de vida\nUsar pocao(S/N) ? ");
    scanf("%c", &yn);
    getchar();
    if (yn == 's' || yn == 'S')
    {
      item1[0] = '\0';
      hp = hp + 15;
      if (hp>hpmax)
        hp = hpmax;
      printf("Vida restaurada! Vida atual: %d\n\n", hp);
      return 0;
    }
    return -1;
  }
  if (item1[0] == '\0' && item2[0] != '\0')
  {
    printf("Item disponivel:\nBomba - Causa dano ao inimigo\nUsar bomba(S/N) ? ");
    scanf("%c", &yn);
    getchar();
    if (yn == 's' || yn == 'S')
    {
      item2[0] = '\0';
      ihp= ihp - 7;
      if(ihp<0)
        ihp =0;
      printf("O inimigo sofreu dano!\n");
      printf("A vida inimiga eh: %d\n\n", ihp);
      return 0;
    }
    return -1;
  }
  return -1;
}
void inimigo(char* nome,int ihp,int idano,int iacerto)//a funcao inimigo eh usada apenas para apresentar as estatisticas de cada inimigo, de modo que o jogador saiba o que esta enfrentando.
{
  printf("O %s possui:\nVida = %d\nDano = %d\nChance de acerto = %d%%\n", nome, ihp, idano, iacerto);
}
void luta() //a funcao luta serve para simular a batalha entre o jogador e o inimigo, fazendo uso de um while que rodara infinitamente a menos que chegue a uma condicao de saida. as unicas
{     //duas condicoes de saida sao: ou o jogador derrotou o inimigo(reduziu os pontos de vida do inimigo a 0), ou o jogador foi derrotado(teve seus pontos de vida reduzidos a 0).
  while (1)
  {
    int confere = 0;
    char acao;
    printf("Eh a sua vez de atacar!\n");
    printf("Seus pontos de vida atuais: %d\n", hp);
    printf("Opcoes:\nAtacar (A)\nItem (I)\n");
    scanf("%c", &acao);
    getchar();
    if (acao == 'A' || acao == 'a')
      atkjogador(dano, acerto);
    if (acao == 'I' || acao == 'i')
      confere = item();
    if (ihp<= 0)
      break;
    if (confere == -1)
      continue;
    atkinimigo(idano, iacerto, evasao, defesa);
    if (hp <= 0)
    {
      if(hpmax==25)
        printf("Voce e sua filha sao enterrados pelos poucos aldeoes que sobreviveram ao ataque.\n");
        printf("Muitos morreram por sua culpa.\n");
      if(hpmax==15)
        printf("Conseguiu levar sua alma para o plano astral, salvando sua consciencia,\n");
        printf("porem seu corpo teve de ser abandonado apos ter sido ferido fatalmente.\n");
        printf("Todos os aldeoes foram assassinados e devorados. Falhaste em salva-los.\n");
      if(hpmax==20)
        printf("Deveria ter esquecido os tesouros e focado na luta. Acabou levando um golpe fatal.\nTodos morreram por conta da tua incompetencia.\n");
      printf("Fim de jogo!\nVoce foi derrotado!\n");
      pa = fopen("jogadores.txt", "a");
      fprintf(pa, "%s,  %d pontos \n", player, pontuacao);
      fclose(pa);
    break;
    }
  }

}
void personagem() //a funcao personagem apresenta as estatisticas dos personagens disponiveis no jogo para o jogador, para que este possa escolher com qual deles deseja jogar.
{
  while(1){
    char classe[100];
    printf("(Digite apenas o nome da classe escolhida)\n");
    gets(classe);
    for(int i = 0;i<strlen(classe);i++)
      {classe[i] = tolower(classe[i]);}
    if (strcmp(classe, "guerreiro") == 0) 
    {
        hpmax = 25.0; //hpmax eh utilizado para que o jogador nao possa ter mais pontos de vida do que tinha inicialmente, seja usando uma pocao ou chegando no ultmo inimigo.
      hp = 25; //a variavel hp eh o que determina se o jogador podera continuar jogando. se esse valor for reduzido a 0, eh um game over e o jogador perdeu.
      acerto = 70; //a chance de acerto do jogador, utilizada na funcao atkjogador.
      evasao = 10; //quando o inimigo ataca o jogador, ha uma chance do jogador se esquivar do ataque. a variavel evasao eh a estatistica que determina se o jogador se esquiva ou nao.
      dano = 10; //a variavel dano determina quantos pontos de dano o jogador causa ao inimigo quando o acerta. isso eh utilizado na funcao atkjogador.
      defesa = 8; //a defesa de um personagem reduz o dano que um inimigo causa ao jogador. isso eh usado em atkinimigo.
      printf("\n\nVoce eh um guerreiro(a) muito habilidoso(a), porem ainda sofre com uma grande derrota do passado.\n");//historia do personagem. ela varia de acordo com a classe escolhida
      printf("Seu antigo vilarejo foi tomado por criaturas, e nao foi capaz de protege-lo.\n");
      printf("Entre os mortos, havia a sua(seu) esposa(o).\n");
      printf("Conseguiram escapar com vida apenas voce e sua unica filha.\n");
      printf("Por muitos anos, moram isolados em uma pequena aldeia no topo da montanha Misty Montes.\n");
      printf("Ao ver a aldeia ser atacada por criaturas, ansiedade e desespero correm pelas suas veias.\n");
      printf("Tera de levantar sua espada mais uma vez, mesmo que a ultima vez que teve de\n");
      printf("empunha-la foi em seu maior fracasso.\n");
      break;
    }
    if (strcmp(classe, "mago") == 0) 
    {
        hpmax = 15.0;
      hp = 15;
      acerto = 80;
      evasao = 17;
      dano = 20;
      defesa = 5;
      printf("\n\nVoce eh um(a) mago(a) muito poderoso(a),\nprocurando sempre aumentar o seu poder nas artes arcanas.\n");
      printf("Por praticar magia, muitos do vilarejo proximo o(a)\nencaram como vilanesco(a), e sempre se escondem de voce.\n");
      printf("Outros o(a) desprezam, e ja formaram turbas para o (a) perseguir e tentar mata-lo(a).\n");
      printf("Por muitos anos, vive isolado(a) no topo da montanha Erebor Mons.\n");
      printf("Ao ver o vilarejo ser atacado por criaturas, corre em sua direção para defende-lo.\n");
      printf("Pensa: Talvez os aldeoes parem de ter medo de mim.\n");
      printf("Independente disso, tenho de protege-los.\n Nao posso deixa-los morrer sabendo que poderia ter feito algo.\n");
      break;
    }
    if (strcmp(classe, "ladino") == 0) 
    {
        hpmax = 20.0;
      hp = 20;
      acerto = 100;
      evasao = 30;
      dano = 6;
      defesa = 6;
      printf("\n\nVoce eh um ladino(a) que acaba de fugir da prisao.\n");
      printf("Escala a montanha Mindolluin Montes procurando despistar os guardas.\n");
      printf("Ao chegar no topo, ve uma vila sendo atacada por criaturas.\n");
      printf("Por nao ser uma pessoa ma, corre para tentar protege-la.\n");
      printf("Porem, por ser um ladino(a), ja esta pensando em roubar uns pertences para si,\n");
      printf("aproveitando a situacao caotica.\n");
      break;
    }
    else
    {
      classe[0] = '\0';
      continue;
    }
}
}
void escolhe()
  {
    int x;
    x = rand() % 3;
  if (x==0)
  {
    printf("\nVoce lutara contra um Goblin!\n");
    ihp= 9;
    idano = 10;
    iacerto = 50;
    inimigo("Goblin", ihp, idano, iacerto);
  }
  if(x==1)
  {
    printf("\nVoce lutara contra um lobo!\n");
    ihp= 20;
    idano = 10;
    iacerto = 60;
    inimigo("Lobo", ihp, idano, iacerto);
  }
  if (x==2)
  {
    printf("\nVoce Lutara contra um minotauro!\n");
    ihp=25;
    idano=11;
    iacerto=70;
    inimigo("Minotauro", ihp, idano, iacerto);
  }
}

int main() //na funcao main, o jogador eh lancado em combate contra tres inimigos diferentes. caso seja capaz de derrotar os dois primeiros, ele tera sua vida restaurada antes de enfrentar
{      //o ultimo.
  char vontade, acao, nome[100];
  while(1){
    pontuacao =0;
    strcpy(item1, "Pocao");
    strcpy(item2, "Bomba");
    printf("Digite seu nome.\n");
    gets(nome);
    printf("\nBem vindo ao jogo, %s!\n", nome);
    printf("Esperamos que se divirta com esse RPG!\n");
    printf("Digite o seu nickname: ");
    gets(player);
    pa = fopen("pontuacao.txt", "w");
    fprintf(pa, "%s %d", player, pontuacao);
    fclose(pa);
    printf("\nEscolha seu personagem.\n");
    printf("Guerreiro:\nVida: 25\nChance de acerto: 70%%\nEvasao: 10%%\nForca: 10\nDefesa: 8\n\n");
    printf("Mago:\nVida: 15\nChance de acerto: 80%%\nEvasao: 17%%\nForca: 20\nDefesa: 5\n\n");
    printf("Ladino:\nVida: 20\nChance de acerto: 100%%\nEvasao: 30%%\nForca: 6\nDefesa: 6\n\n");
    personagem();
    if(hpmax==25)
      printf("\nAvista de longe mulheres que estao prestes a ser devoradas. Corre para protege-las da criatura.\n");
    if(hpmax==15)
      printf("\nAo chegar no vilarejo, ve criaturas famintas que estao prestes a devorar mulheres e criancas. Corre para protege-las.\n");
    if(hpmax==20)
      printf("\nAo chegar na vila, ve criaturas sequestrando alguns aldeoes. Corre para liberta-los.\n");
    escolhe();
    luta();
  if (hp>0){
    pontuacao = pontuacao + (1000*(hp/hpmax));
    printf("Inimigo derrotado!\n");
    printf("Pontuacao atual: %d\n", pontuacao);
    printf("Gostaria de salvar o jogo(S/N) ? ");
    scanf("%c", &acao);
    if (acao == 'S' || acao == 's')
    {
      pa = fopen("pontuacao.txt", "w");
      fprintf(pa, "%s %d", player, pontuacao);
      fclose(pa);
    }
    if(hpmax==25)
      printf("\n\nUma outra criatura esta prestes a ferir um menor. Corre para socorre-lo!\n");
    if(hpmax==15)
      printf("\n\nMataste uma criatura. Restam-lhe mais duas.\n");
    if(hpmax==20)
      printf("\n\nMataste uma criatura e roubaste seus pertences. Restam-lhe mais duas.\n");
    escolhe();
    getchar();
    luta();}
  if (hp>0){
    pontuacao = pontuacao + (1000*(hp/hpmax));
    printf("Inimigo derrotado!\n");
    printf("Pontuacao atual: %d\n", pontuacao);
    printf("Gostaria de salvar o jogo(S/N) ? ");
    scanf("%c", &acao);
    if (acao == 'S' || acao == 's')
    {
      pa = fopen("pontuacao.txt", "w");
      fprintf(pa, "%s %d", player, pontuacao);
      fclose(pa);}
    hp = hp + 12;
    if (hp>hpmax)
      hp = hpmax;
    if(hpmax==25)
      printf("Um velho sabio lhe oferece uma pocao para recuperar suas energias.\nDe repente, uma criatura lhe atinge e morre em suas maos, e percebe que a mesma sequestrou a sua filha!\n Corre para salva-la.\n");
    if(hpmax==15)
      printf("Um velho sabio lhe recompensa com uma pocao por te-lo salvado da criatura.\n Lhe resta matar a ultima criatura.\n");
    if(hpmax==20)
      printf("Roubaste uma pocao de uma casa destruida, e recupera as suas energias.\n Avista uma criatura saqueando os moradores. Corre para salva-los.\n");
    printf("\n\nParabens por ter chegado ate a ultima fase do nosso jogo.\nSua vida atual eh: %d\n\n", hp);
    escolhe();
    getchar();
    luta();
    if(hp>0){
      pontuacao = pontuacao + (1000*(hp/hpmax));
      printf("Inimigo derrotado!\n");
      printf("Pontuacao atual: %d\n", pontuacao);
      printf("Fim de jogo!\nVoce venceu!\n");
      if(hpmax==25)
        printf("Salvaste a todos. Chora de emocao ao poder abracar sua filha novamente.\nGritam o seu nome pelas pracas publicas, o nome do heroi que os salvaste.\n");
      if(hpmax==15)
        printf("Apos ter salvado a todos, deixam o preconceito que tinham por voce de lado.\nPermitem que voce habite novamente o vilarejo.\n");
      if(hpmax==20)
        printf("Os moradores ficam muito agradecidos por te-los salvado,\nporem nao percebem que levou para si alguns dos pertences que haviam sido sequestrados.\nVendeste os tesouros obtidos e ficaste rico!\n");
      printf("Gostaria de salvar o jogo(S/N) ? ");
      scanf("%c", &acao);
      if (acao == 'S' || acao == 's')
      {
        pa = fopen("jogadores.txt", "a");
        fprintf(pa, "%s,  %d pontos \n", player, pontuacao);
        fclose(pa);
      }
      getchar();
      }}
  printf("\n\nDeseja jogar novamente? (S/N): ");
  scanf("%c", &vontade);
  if((vontade=='S') || (vontade== 's'))
    {getchar();
    continue;}
  else
    break;
}

return 0;
}