#PBS -l walltime=0:10:00
#PBS -l select=1:ncpus=4:mpiprocs=4

# "fusion" PBS options
#PBS -q haswellq
#PBS -P omaha

# Charge the modules here
# "fusion" cluster modules
module purge
module load intel-compilers/17.0.4
module load intel-mpi/2017.0.3


cd $PBS_O_WORKDIR
