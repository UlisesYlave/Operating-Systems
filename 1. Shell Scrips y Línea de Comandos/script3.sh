if [ $# -ne 1 ]; then
  echo "Se debe ingresar un parametro: $0 <patron_eliminar>"
  exit 1
fi
patron=$1

archivos=$(ls | grep "$patron" 2>/dev/null)

if [ -z "$archivos" ]; then
    echo "No se encontraron archivos $patron"
    exit 0
fi

while IFS=\n read -r archivo; do
  nuevo_nombre="${archivo//$patron/}"
  mv $archivo $nuevo_nombre
done <<< "$archivos"