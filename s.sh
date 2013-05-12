for file in "experiment_500"/*
do
	echo ${file}
	awk 'BEGIN{sum=0;}{sum += $1; sumsq += $1*$1} END {printf("%f\n"),sqrt(sumsq/NR-(sum/NR)^2)}' "${file}"
	awk 'BEGIN{sum=0;}{if(NR<=30){print $1; sum += $1; sumsq += $1*$1}} END {printf("%f\n"),sqrt(sumsq/30-(sum/30)^2)}' "${file}"
done
