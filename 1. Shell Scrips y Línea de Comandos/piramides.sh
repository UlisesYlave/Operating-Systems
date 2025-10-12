x=0
cadena='0'
until [ $x -ge 10 ]
do
  echo "$cadena"
  x=`expr $x + 1`
  cadena="$x  $cadena"
done