#!/bin/bash
#
# Programa desenvolvido por Prof. Andre Leon S. Gradvohl, Dr.
# para preparar o laboratorio de sistemas operacionais.
#
# Ultima versao: seg 02 abr 2019 13:51:22 -03

RED='\033[0;31m'
GREEN='\033[0;32m'
LIGHTBLUE='\033[1;34m'
NC='\033[0m' # No Color

echo -e "Esse script vai preparar o ambiente para o ${LIGHTBLUE}laboratorio de sistemas operacionais${NC}"

#Primeiro Passo: Definicao de variaveis de ambiente
# Arquivo compactado
ARQCOMPACT=labSO.tar.gz
#
# Programa tar
TAR=`which tar`
if [ $? -ne 0 ]; then
   echo "Programa para descompactacao ${RED}nao foi encontrado!${NC}"
   echo -e "\nAbortando script... ${RED}Contacte o professor!${NC}"
   exit 1;
fi
#
# Diretorio de destino
DESTDIR=${HOME}/laboratorioSO

#Segundo Passo: descompactar arquivo de instrucoes
if [ ! -f $ARQCOMPACT ]; then 
   echo -e "Arquivo ${ARQCOMPACT} ${RED} nao existe!${NC}"
   echo -e "\nAbortando script... ${RED}Contacte o professor!${NC}"  
   exit 1
else
    mkdir -p ${DESTDIR}
    if [ $? -ne 0 ]; then 
        echo -e "Problemas na criação do diretorio ${DESTDIR} !"
        echo -e "\nAbortando script... ${RED}Contacte o professor!${NC}"
        exit 1
    fi

    ${TAR} xzf ${ARQCOMPACT} -C ${DESTDIR}
    if [ $? -eq 0 ]; then 
        echo -e "Arquivo ${ARQCOMPACT} descompactado ${GREEN} com sucesso!${NC}"
        echo -e "Mude para o diretorio ${RED}${DESTDIR}${NC} e aguarde novas instrucoes. Use o comando a seguir:"
        echo -e "  ${LIGHTBLUE}cd ${RED}${DESTDIR}${NC}"
        exit 0
    else
        echo -e "Arquivo ${ARQCOMPACT} com ${RED}problemas na descompactacao${NC}"
        echo -e "\nAbortando script... ${RED}Contacte o professor!${NC}"
        exit 1
    fi
fi
