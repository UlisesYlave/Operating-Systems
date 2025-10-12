#! /bin/bash
n1="$1"
n2="$2"
digit="$3"

is_prime(){
  local num=$1
  if [ $num -le 1 ]; then
    return 1
  fi
  if [[ $num -eq 2 ]]; then
    return 0
  fi
  if [[ $(($num % 2)) -eq 0 ]]; then
    return 1
  fi
  local i=3
  while [ $((i * i)) -le $num ]
  do
    if [ $((num % i)) -eq 0 ]; then
      return 1
    fi
    i=$((i + 2))
  done
  return 0
}

have_num(){
  local num=$1
  local dig=$2
  local dignum=0
  until [ $num -eq 0 ]
  do
    dignum=$(($num%10))
    if [ $dignum -eq $dig ]; then
      return 0
    fi
    num=$(($num/10))
  done
  return 1
}

while [ $n1 -le $n2 ]
do
  if have_num $n1 $digit; then
    if is_prime $n1; then
      echo "$n1 primo"
    else
      echo "$n1"
    fi
  fi
  n1=$(($n1+1))
done