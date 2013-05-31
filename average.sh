vertex_num=$1
folder="experiment_${vertex_num}"
pool_size=100
mutation_rate=0.01
convergence_threshold=0.001
crossover=0
mkdir -p "${folder}"

for replace_policy in 0 1 2
do
	for optimize in 0 1 2 3
	do
		file="${folder}/result_${replace_policy}_${optimize}.out"
		for i in $(seq 1 30)
		do
			./maxcut ./g${vertex_num}.txt ./data.out $pool_size $crossover $mutation_rate $replace_policy $convergence_threshold $optimize >> "${file}"
		done
		awk '{ total += $1; count++ } END { print total / count }' "${file}" >> "${file}"
		awk 'BEGIN{sum=0;}{if(NR<=30){sum += $1; sumsq += $1*$1}} END {printf("%f\n"),sqrt(sumsq/30-(sum/30)^2)}' "${file}" >> "${file}"
	done
done
