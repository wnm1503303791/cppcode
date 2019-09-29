#declare -a arr=('chr01' 'chr02' 'chr03' 'chr04' 'chr05' 'chr06' 'chr07' 'chr08' 'chr09' 'chr10' 'chr11' 'chr12')

for i in {1..100}
  do
    echo "$i"
    # if [ -d "/public/home/hzhao/data/RiceVarMap/ZS_MH_basenji/ZS97_mutiple_train_20/ZS97_${i}" ]
    # then
       # echo 'calculated!'
     # else
       # mkdir /public/home/hzhao/data/RiceVarMap/ZS_MH_basenji/ZS97_mutiple_train_20/ZS97_${i}
       # basenji_sad.py 
			# -f /public/home/hzhao/rice_genome_sequence/MSU/version_7.0/rice_all_genomes_v7.fasta 
			# -g /public/home/hzhao/rice_genome_sequence/MSU/version_7.0/ricev7.genome 
			# -o /public/home/hzhao/data/RiceVarMap/ZS_MH_basenji/ZS97_mutiple_train_20/ZS97_$i 
		  # --rc 
		    # -t /public/home/hzhao/data/RiceVarMap/ZS_MH_basenji/ZS97_samples_no_scale_sad.txt /public/home/hzhao/data/RiceVarMap/ZS_MH_basenji/ZS97_params.txt /public/home/hzhao/data/RiceVarMap/ZS_MH_basenji/ZS97_mutiple_train_20/model_best.tf /public/home/hzhao/data/RiceVarMap/chrom_vcf_all20190711/${i}.vcf 
			# -c
     # fi
	useradd -d /home/u-${i} -m u-${i}
	echo "u-${i}" | passwd --stdin u-${i}
	#userdel -r u-${i}
  done  
