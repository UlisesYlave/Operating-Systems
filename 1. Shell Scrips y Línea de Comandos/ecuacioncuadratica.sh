if [ $# -ne 3 ]; then
  echo "Los argumentos deben ser: A, B y C"
  exit 1
fi

ecuacion="$1x^2 + $2x + $3 = 0"
echo $ecuacion

tri=$(($2 * $2 - 4 * $1 * $3))

if [ $tri -lt 0 ]; then
  echo "No hay solucion real"
  exit 1
fi

rpta1=$(echo "scale=5; (-$2 - sqrt($tri)) / (2 * $1)" | bc -l)
rpta2=$(echo "scale=5; (-$2 + sqrt($tri)) / (2 * $1)" | bc -l)

printf "Primera respuesta: %.5f\n" "$rpta1"
printf "Segunda respuesta: %.5f\n" "$rpta2"