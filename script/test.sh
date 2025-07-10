#!/usr/bin/env bash

getNormalDistributionSample () {
	min=$1
	max=$2
	echo $(( min + (RANDOM % (max-min+1)) ))
}

getParetoDistributionSample () {

    x=$(echo "" | awk -v seed=$RANDOM 'BEGIN {alpha=1.1d; lambda=20; u=(seed+1)/32768; printf("%.0f\n", lambda*u^(-1/alpha));}')

    echo "$x"

}

declare -A arete
density=50
for i in $(seq -w 1 10); do
  for j in $(seq -w 1 10); do
    randomNumber=$(getNormalDistributionSample 1 100)
    if [ $randomNumber -le $density ]; then
      arete[$i $j]=$(getParetoDistributionSample)
    fi
  done
done

for cle in "${!arete[@]}"; do
  echo "arete : $cle distance ${arete[$cle]}"
done

getNormalDistributionSample 0 10
declare -A tab
for i in $(seq 1 5); do
  for j in $(seq 1 5); do
    tab[$i $j]=$(getNormalDistributionSample 0 10)
  done

done

for valeur in "${tab[@]}"; do
  echo "Valeur : $valeur"
done

for cle in "${!tab[@]}"; do
  echo "arete $cle distance ${tab[$cle]}"
done