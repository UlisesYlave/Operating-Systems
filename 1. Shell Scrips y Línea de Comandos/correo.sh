echo "Ingreso tu mensaje"
read correo
MENSAJE=${correo:?"El correo no contiene contenido."}
echo $MENSAJE