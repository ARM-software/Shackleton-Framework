for tsp_file in *.tsp; do
	echo "running ${tsp_file}"
	lli acotsp_full.bc --tsplibfile ${tsp_file} > /dev/null
done	
