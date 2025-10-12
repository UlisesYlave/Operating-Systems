#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Uso: $0 archivo.txt palabra"
  exit 1
fi


if [ ! -f "$1" ] || [[ "$1" != *.txt ]]; then
  echo "El primer parametro debe ser el archivo .txt existente"
  exit 1
fi

palabra="$2"
num=0
while IFS= read -r linea; do
  ((linea_num++))

  if echo "$linea" | grep -q -w "$palabra"; then
    ((num++))
    echo "Coincidencia $num en linea: $linea_num: $linea"
  fi
done < "$1"

if [ "$num" -eq 0 ]; then
  echo "No se encontró la palabra"
fi