/*******************************************************************************
*
*  $MCD Módulo de definição: CLI  Cedulas LIvres
*
*  Arquivo gerado:              CEDULASLIVRES.h
*  Letras identificadoras:      CLI
*  Nome da base de software:    Jogo Freecell
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301    Implementação do Jogo Freecell para fins educacionais
*  Gestor:  LES/DI/PUC-Rio
*  Autores: Gabriel Barros, Noemie Nakamura e Leonardo Giroto
*
*  $HA Histórico de evolução:
*     Versão  Autor           Data     Observações
*     2       GB          28/set/2012 prosseguimento do  desenvolvimento
*     1       GB/Noemie   25/set/2013 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa as Regras e Funções básicas às colunas de cartas do tipo que 
*    contém uma única carta.
*
*	  Permite a criação de até 4 colunas, conforme a restrição do jogo. 
*
*     Implementa uma abstração da estrutura de dados, tornando o uso uma 
*   simples questão de conjuntos de cartas organizadas.
*
*******************************************************************************/
public CLI_Coluna CLI_CriaColuna (void);
public int CLI_ExcluirColuna( CLI_Coluna coluna );
public int CLI_InserirCarta ( CLI_Coluna destino, Carta carta);
public int CLI_ExcluirCarta (CLI_Coluna alvo, Carta carta);
