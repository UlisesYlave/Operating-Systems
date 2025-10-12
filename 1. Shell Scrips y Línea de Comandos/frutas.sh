frutas[1]=manzana
frutas[2]=piña
frutas[3]=durazno
echo ${frutas[*]}
frutas=uva
echo ${frutas[*]}
unset frutas