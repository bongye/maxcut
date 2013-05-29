for vertex_num in 500 750 1000
do
	folder="experiment_${vertex_num}"
	mkdir -p "${folder}"
	pool_size= 100
	mutation_rate= 0.01
	convergence_threshold= 0.001
	for crossover in 0 1 2
	do
		for replace_policy in 0 1 2
		do
			for optmize in 0 1 2 3
				file="${folder}/result_${crossover}_${replace_policy}_${convergence_threshold}_${optimize}.out"
				for i in $(seq 1 30)
				do
					./maxcut ./maxcut${vertex_num}.txt ./data.out $pool_size $crossover $mutation_rate $replace_policy $convergence_threshold $optimize >> "${file}"
				done
				awk '{ total += $1; count++ } END { print total / count }' "${file}" >> "${file}"
				awk 'BEGIN{sum=0;}{if(NR<=30){sum += $1; sumsq += $1*$1}} END {printf("%f\n"),sqrt(sumsq/30-(sum/30)^2)}' "${file}" >> "${file}"
		done
	done
done
