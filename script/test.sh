#!/usr/bin/env bash

getNormalDistributionSample () {
	min=$1
	max=$2
	echo $(( min + (RANDOM % (max-min+1)) ))
}

getNormalDistributionSample 0 10