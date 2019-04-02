#!/bin/bash
#
# Programa desenvolvido por:
#     Andre Leon S. Gradvohl, Dr.
# para preparar o laboratorio de sistemas operacionais.
# Ultima atualizacao: 02/11/2011

echo -e "Esse programa vai preparar o ambiente para o\n laboratorio de sistemas operacionais"

#Primeiro Passo: Definicao de variaveis de ambiente

ARQCOMPACT=labSO.tar.gz
TAR=`which tar`
if [ $? -ne 0 ]; then
	echo "Programa para descompactacao nao foi encontrado!"
	echo "Abortando Script"
    exit 1;
fi

BROWSER=`which firefox`
if [ $? -ne 0 ]; then
    echo -e "Browser nao encontrado!\nTestando 2a. opcao"
	BROWSER=`which mozilla`
	if [ $? -ne 0 ]; then
		    echo  "Browser nao encontrado!"
		    echo "Abortando Script"
			exit 1;
	fi		
fi

ARQHTML=$PWD/laboratorio/index.html

#Segundo Passo: descompactar arquivo de instrucoes
if [ ! -f $ARQCOMPACT ]; then 
    echo -e "Arquivo ${ARQCOMPACT} nao existe! \n Abortando..."
	echo "Contacte o professor!"  
    exit 1
else
    ${TAR} xzf ${ARQCOMPACT}
    if [ $? -eq 0 ]; then 
        echo "Arquivo ${ARQCOMPACT} descompactado com sucesso!"
    else
        echo "Arquivo ${ARQCOMPACT} com problemas na descompactacao"
        echo "Abortando... Contacte o professor!"
        exit 1
    fi
fi

echo "Disparando browser: $BROWSER file://${ARQHTML}"
$BROWSER file://${ARQHTML} &

if [ $? -ne 0 ]; then
    echo "Nao foi possivel instanciar o browser ${BROWSER}!"
    echo "Contacte o professor! Abortando!"
    exit 1
else
    echo "Ambiente preparado! Bom proveito!"
    exit 0
fi
