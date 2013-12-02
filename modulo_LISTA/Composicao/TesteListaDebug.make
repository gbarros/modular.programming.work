##################################################
###
### Diretivas de MAKE para o construto: TesteListaDebug
### Gerado a partir de: testelistadebug.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteListaDebug


### Nomes de paths

Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Plib                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diretórios para geração

Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Flib                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\lista.obj   $(Fobj)\test_lis.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}cespdin.h            {$(Ph)}conta.h              {$(Ph)}generico.h           \
    {$(Ph)}lista.h              {$(Ph)}lista_instr.h        {$(Ph)}tst_espc.h          
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\test_lis.obj :  {$(Pc)}\test_lis.c \
    {$(Ph)}cespdin.h            {$(Ph)}generico.h           {$(Ph)}lerparm.h            \
    {$(Ph)}lista.h              {$(Ph)}lista_instr.h        {$(Ph)}tst_espc.h          
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\lista.obj   $(Fobj)\test_lis.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteListaDebug
###
##################################################

