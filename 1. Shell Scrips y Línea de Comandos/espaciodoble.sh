for arg in $*
do
  contenido=$(cat $arg)
  while IFS= read -r line; do
    printf "%s\n\n" "$line"
  done < $arg
done