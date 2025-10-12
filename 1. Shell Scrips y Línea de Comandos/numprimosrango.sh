if [ $# -ne 2 ]; then
  echo "Deben ser 2 parametros: inicio-final"
  exit 1
fi

esPrimo(){
  if [ $1 -le 1 ]; then
    return 1
  fi

  if [ $1 -eq 2 ]; then
    return 0
  fi

  if [ $(($1%2)) -eq 0 ]; then
    return 1
  fi

  local raiz=$(echo "sqrt($1)" | bc)
  local y=3
  while [ $y -le $raiz ]
  do
    if [ $(($1%$y)) -eq 0 ]; then
      return 1
    fi
    y=`expr $y + 2`
  done

  return 0
}

x=$1

while [ $x -le $2 ]
do
  if esPrimo $x; then
    echo $x
  fi

  x=`expr $x + 1`
done