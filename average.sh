rm -f result.out

for vertex_num in 500 750 1000
do
	folder="experiment_${vertex_num}"
	mkdir -p "${folder}"
	for pool_size in 10 30 50
	do
		for crossover in 0 1
		do
			for mutation_rate in 0.1 0.2 0.3
			do
				for replace_policy in 0 1 2
				do
					for convergence_threshold in 0.005 0.001
					do
						file="${folder}/result_${pool_size}_${crossover}_${mutation_rate}_${replace_policy}_${convergence_threshold}.out"
						for i in $(seq 1 30)
						do
							./maxcut ./maxcut${vertex_num}.txt ./data.out $pool_size $crossover $mutation_rate $replace_policy $convergence_threshold >> "${file}"
						done
						awk '{ total += $1; count++ } END { print total / count }' "${file}" >> "${file}"
						awk 'BEGIN{sum=0;}{if(NR<=30){sum += $1; sumsq += $1*$1}} END {printf("%f\n"),sqrt(sumsq/30-(sum/30)^2)}' "${file}" >> "${file}"
					done
				done
			done
		done
	done
done
