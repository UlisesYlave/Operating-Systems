if [ $# -ne 2 ]; then
  echo 'Deben ser 2 argumentos: n1 (ini) - n2 (fin)'
  exit 1
fi

if [ $1 -gt $2 ]; then
  echo 'n1 (ini) debe ser menor o igual que n2 (fin)'
  exit 1
fi

esprimo(){
  num=$1
  if [ $num -le 1 ]; then
    return 1
  fi
  if [ $num -eq 2 ]; then
    return 0
  fi
  if [ $(($num%2)) -eq 0 ]; then
    return 1
  fi
  ini=3
  raiz=$(echo "scale=0; sqrt($num)" | bc -l )
  while [ $ini -le $raiz ]
  do
    if [ $(($num%$ini)) -eq 0 ]; then
      return 1
    fi
    ini=$(($ini+1))
  done
  return 0
}

n=$1
while [ $n -le $2 ]
do
  if esprimo $n; then
    echo "$n (primo)"
  else
    echo $n
  fi
  n=$(($n+1))
done