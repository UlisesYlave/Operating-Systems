nombrearchivo="Lista1.txt"

while IFS= read -r linea
do
  IFS=, read -r parte1 nombres <<<$linea
  read id apepat apemat <<<$parte1
  nom_minus=$(echo "$nombres" | awk '{print $1}' | tr '[:upper:]' '[:lower:]')
  ape_minus=$(echo "$apepat" | tr '[:upper:]' '[:lower:]')
  nombres_formato=""
  for nombre in $nombres;do
    nombre_min="${nombre,,}"
    primera_letra="${nombre_min:0:1}"
    primera_letra_mayus="${primera_letra^^}"
    resto_nombre="${nombre_min:1}"
    nombre_formato="${primera_letra_mayus}${resto_nombre}"

    if [ -z "$nombres_formato" ]; then
      nombres_formato="$nombre_formato"
    else
      nombres_formato="$nombres_formato $nombre_formato"
    fi
  done
  echo "$id:$apepat $apemat,$nombres_formato:$nom_minus.$ape_minus@pucp.edu.pe"
done < $nombrearchivo > "Lista2.txt"