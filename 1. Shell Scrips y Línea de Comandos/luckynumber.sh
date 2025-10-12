# !/bin/bash
ini=1000
fin=10000

isluckynumber(){
  num=$1
  sum=0
  while [ $num -gt 0 ] || [ $sum -gt 9 ]
  do
    if [ $num -eq 0 ] && [ $sum -gt 9 ]; then
      num=$sum
      sum=0
    fi
    digito=$(($num%10))
    sum=$(($sum+$digito))
    num=$(($num/10))
  done
  if [ $sum -eq 7 ]; then
    return 0
  else
    return 1
  fi
}

echo '               L U C K Y  N U M B E R S : ( 1000 - 10000 )'
echo '=========================================================================='
echo
lucky_numbers=()
while [ $ini -lt $fin ]
do
  if isluckynumber $ini; then
    lucky_numbers+=($ini)
  fi
  ini=$(($ini+1))
done

count=0
for num in "${lucky_numbers[@]}"; do
  printf "%-10s" $num
  count=$((count + 1))
  if [ $((count % 8)) -eq 0 ]; then
    echo
  fi
done

# Asegurarse de que la última línea termina con un salto de línea
if [ $((count % 4)) -ne 0 ]; then
  echo
fi