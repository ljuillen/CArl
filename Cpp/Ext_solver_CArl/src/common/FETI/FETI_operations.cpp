#include "FETI_operations.h"

namespace carl
{

void FETI_Operations::set_coupling_matrix_R_micro(const std::string& filename)
{
	MatCreate(m_comm.get(),&m_C_R_micro);
	read_PETSC_matrix(m_C_R_micro,filename,m_comm.get());
	MatGetLocalSize(m_C_R_micro,&m_C_R_micro_M_local,&m_C_R_micro_N_local);
	MatGetSize(m_C_R_micro,&m_C_R_micro_M,&m_C_R_micro_N);
	m_C_RR_M = m_C_R_micro_M; m_C_RR_M_local = m_C_R_micro_M_local;
	m_bC_R_micro_MatrixSet = true;
	m_bCouplingMatricesSet = m_bC_R_BIG_MatrixSet && m_bC_R_micro_MatrixSet && m_bC_RR_MatrixSet;
}

void FETI_Operations::set_coupling_matrix_R_BIG(const std::string& filename)
{
	MatCreate(m_comm.get(),&m_C_R_BIG);
	read_PETSC_matrix(m_C_R_BIG,filename,m_comm.get());
	MatGetLocalSize(m_C_R_BIG,&m_C_R_BIG_M_local,&m_C_R_BIG_N_local);
	MatGetSize(m_C_R_BIG,&m_C_R_BIG_M,&m_C_R_BIG_N);
	m_C_RR_M = m_C_R_BIG_M; m_C_RR_M_local = m_C_R_BIG_M_local;
	m_bC_R_BIG_MatrixSet = true;
	m_bCouplingMatricesSet = m_bC_R_BIG_MatrixSet && m_bC_R_micro_MatrixSet && m_bC_RR_MatrixSet;
}

void FETI_Operations::set_coupling_matrix_RR(const std::string& filename)
{
	MatCreate(m_comm.get(),&m_C_RR);
	read_PETSC_matrix(m_C_RR,filename,m_comm.get());
	m_bC_RR_MatrixSet = true;
	m_bCouplingMatricesSet = m_bC_R_BIG_MatrixSet && m_bC_R_micro_MatrixSet && m_bC_RR_MatrixSet;
}

void FETI_Operations::read_coupling_matrices(const std::string& filename_base)
{
	this->set_coupling_matrix_R_micro(filename_base + "_micro.petscmat");
	this->set_coupling_matrix_R_BIG(filename_base + "_macro.petscmat");
	this->set_coupling_matrix_RR(filename_base + "_mediator.petscmat");
}

void FETI_Operations::set_null_space_vecs_micro(const std::string& input_filename_base, int nb_of_vecs)
{
	homemade_assert_msg(m_bC_R_micro_MatrixSet,"Micro coupling matrix not set yet!");

	// Set the null vec arrays
	m_null_nb_vecs = nb_of_vecs;

	// Matrix dimensions
	//                       M       x N
	// m_C_R_micro         : n_coupl x n_sys
	// m_null_vecs         : n_sys   x nb_of_vecs	( R )  -> nb_of_vecs vectors of dim n_sys
	// m_null_coupled_vecs : n_coupl x nb_of_vecs	( RC ) -> nb_of_vecs vectors of dim n_coupl

	// Set the first nullspace vectors
	std::string input_filename = input_filename_base + "_0_n_" + std::to_string(m_null_nb_vecs) + ".petscvec";
	VecCreate(m_comm.get(),&m_null_vecs[0]);
	VecSetSizes(m_null_vecs[0],m_C_R_micro_N_local,m_C_R_micro_N);
	read_PETSC_vector(m_null_vecs[0],input_filename, m_comm.get());
	
	std::string output_filename = m_scratch_folder_path + "/rb_coupl_vector_0_n_" + std::to_string(m_null_nb_vecs) + ".petscvec";
	VecCreate(m_comm.get(),&m_null_coupled_vecs[0]);
	VecSetSizes(m_null_coupled_vecs[0],m_C_R_micro_M_local,m_C_R_micro_M);
	VecSetFromOptions(m_null_coupled_vecs[0]);
	MatMult(m_C_R_micro,m_null_vecs[0],m_null_coupled_vecs[0]);
	write_PETSC_vector(m_null_coupled_vecs[0],output_filename,m_comm.rank(),m_comm.get());

	// DEBUG print
	// write_PETSC_vector_MATLAB(m_null_coupled_vecs[0],m_scratch_folder_path + "/rb_coupl_vector_0_n_" + std::to_string(m_null_nb_vecs) + ".m",m_comm.get());
	// write_PETSC_vector_MATLAB(m_null_vecs[0],m_scratch_folder_path + "/rb_vector_0_n_" + std::to_string(m_null_nb_vecs) + ".m",m_comm.get());

	// Read and calculate the rest of the nullspace vectors
	for(int iii = 1; iii < m_null_nb_vecs; ++iii)
	{
		input_filename = input_filename_base + "_" + std::to_string(iii) + "_n_" + std::to_string(m_null_nb_vecs) + ".petscvec";
		VecDuplicate(m_null_vecs[0],&m_null_vecs[iii]);
		read_PETSC_vector(m_null_vecs[iii],input_filename, m_comm.get());

		std::string output_filename = m_scratch_folder_path + "/rb_coupl_vector_" + std::to_string(iii) + "_n_" + std::to_string(m_null_nb_vecs) + ".petscvec";
		VecDuplicate(m_null_coupled_vecs[0],&m_null_coupled_vecs[iii]);
		MatMult(m_C_R_micro,m_null_vecs[iii],m_null_coupled_vecs[iii]);

		write_PETSC_vector(m_null_coupled_vecs[iii],output_filename,m_comm.rank(),m_comm.get());

		// DEBUG print
		// write_PETSC_vector_MATLAB(m_null_coupled_vecs[iii],m_scratch_folder_path + "/rb_coupl_vector_" + std::to_string(iii) + "_n_" + std::to_string(m_null_nb_vecs) + ".m",m_comm.get());
		// write_PETSC_vector_MATLAB(m_null_vecs[iii],m_scratch_folder_path + "/rb_vector_" + std::to_string(iii) + "_n_" + std::to_string(m_null_nb_vecs) + ".m",m_comm.get());
	}

	// Build the LOCAL dense matrix
	std::vector<PetscScalar> dummy_vec_val(m_null_nb_vecs,0);
	std::vector<PetscInt>    dummy_vec_row(m_null_nb_vecs,0);

	for(PetscInt iii = 0; iii < m_null_nb_vecs; ++iii)
	{
		dummy_vec_row[iii] = iii;
	}

	MatCreateSeqDense(PETSC_COMM_SELF,m_null_nb_vecs,m_null_nb_vecs,NULL,&m_RITRI_mat);

	for(PetscInt iii = 0; iii < m_null_nb_vecs; ++iii)
	{
		VecMDot(m_null_coupled_vecs[iii],m_null_nb_vecs,m_null_coupled_vecs,dummy_vec_val.data());
		MatSetValues(m_RITRI_mat,m_null_nb_vecs,dummy_vec_row.data(),1,&iii,dummy_vec_val.data(),INSERT_VALUES);
	}
	MatAssemblyBegin(m_RITRI_mat,MAT_FINAL_ASSEMBLY);
	MatAssemblyEnd(m_RITRI_mat,MAT_FINAL_ASSEMBLY);

	PETSC_invert_dense_matrix(m_RITRI_mat,m_inv_RITRI_mat);

	if(m_comm.rank() == 0)
	{
		write_PETSC_matrix(m_inv_RITRI_mat,m_scratch_folder_path + "/rb_inv_RITRI.petscmat",0,PETSC_COMM_SELF);

		// DEBUG print
		// write_PETSC_matrix_MATLAB(m_inv_RITRI_mat,m_scratch_folder_path + "/rb_inv_RITRI.m",PETSC_COMM_SELF);
	}

	// Set up flag
	m_bNullVecsSet = true;
}

void FETI_Operations::calculate_phi_0(const std::string& force_path)
{
	// 	phi0 = - RC * (inv_RITRI_mat) * R^t* Force
	homemade_assert_msg(m_bNullVecsSet,"Null space vectors not set yet!");
	homemade_assert_msg(m_bC_R_micro_MatrixSet,"Micro coupling matrix not set yet!");
	homemade_assert_msg(m_bC_R_BIG_MatrixSet,"Macro coupling matrix not set yet!");

	// --- Declare the vectors
	// phi0 vector
	Vec vec_phi_0_PETSc;
	Vec vec_force_PETSc;
	VecCreate(m_comm.get(),&vec_phi_0_PETSc);
	VecSetSizes(vec_phi_0_PETSc,m_C_RR_M_local,m_C_RR_M);
	VecSetFromOptions(vec_phi_0_PETSc);

	// Force vector
	VecCreate(m_comm.get(),&vec_force_PETSc);
	read_PETSC_vector(vec_force_PETSc,force_path,m_comm.get());

	// Create the local auxiliary vectors
	Vec aux_null_vec_input;
	Vec aux_null_vec_output;

	VecCreateSeq(PETSC_COMM_SELF,m_null_nb_vecs,&aux_null_vec_input);
	VecCreateSeq(PETSC_COMM_SELF,m_null_nb_vecs,&aux_null_vec_output);

	VecZeroEntries(aux_null_vec_input);
	VecZeroEntries(aux_null_vec_output);

	// aux_vec_input = R^t * vec_force
	// -> All the communications are done here!
	// Cannot use VecMDot because "m_null_vecs" is a constant pointer ...
	PetscScalar *dummy_array_input;
	VecGetArray(aux_null_vec_input,&dummy_array_input);
	for(int iii = 0; iii < m_null_nb_vecs; ++iii)
	{
		VecDot(vec_force_PETSc,m_null_vecs[iii],&dummy_array_input[iii]);
	}
	VecRestoreArray(aux_null_vec_input,&dummy_array_input);

	// aux_vec_output = inv_RITRI_mat * aux_vec_input
	// -> Completely local operation!
	MatMult(m_inv_RITRI_mat,aux_null_vec_input,aux_null_vec_output);

	// vec_out = sum ( aux_null_vec_output[i] * vec_RC[i])
	// -> This should have no communications at all!
	VecZeroEntries(vec_phi_0_PETSc);

	PetscScalar *dummy_array_output;
	VecGetArray(aux_null_vec_output,&dummy_array_output);
	VecMAXPY(vec_phi_0_PETSc,m_null_nb_vecs,dummy_array_output,m_null_coupled_vecs);
	VecRestoreArray(aux_null_vec_output,&dummy_array_output);

	VecScale(vec_phi_0_PETSc,-1);

	// Set outputs
	Vec vec_C_micro_t_phi_0_PETSc;
	VecCreate(m_comm.get(),&vec_C_micro_t_phi_0_PETSc);
	VecSetSizes(vec_C_micro_t_phi_0_PETSc,m_C_R_micro_N_local,m_C_R_micro_N);
	VecSetFromOptions(vec_C_micro_t_phi_0_PETSc);

	Vec vec_C_BIG_t_phi_0_PETSc;
	VecCreate(m_comm.get(),&vec_C_BIG_t_phi_0_PETSc);
	VecSetSizes(vec_C_BIG_t_phi_0_PETSc,m_C_R_BIG_N_local,m_C_R_BIG_N);
	VecSetFromOptions(vec_C_BIG_t_phi_0_PETSc);

	MatMultTranspose(m_C_R_micro,vec_phi_0_PETSc,vec_C_micro_t_phi_0_PETSc);
	MatMultTranspose(m_C_R_BIG,vec_phi_0_PETSc,vec_C_BIG_t_phi_0_PETSc);

	write_PETSC_vector(vec_C_BIG_t_phi_0_PETSc,m_scratch_folder_path + "/ext_solver_A_rhs.petscvec",m_comm.rank(),m_comm.get());
	write_PETSC_vector_MATLAB(vec_C_BIG_t_phi_0_PETSc,m_scratch_folder_path + "/ext_solver_A_rhs.m",m_comm.get());

	write_PETSC_vector(vec_C_micro_t_phi_0_PETSc,m_scratch_folder_path + "/ext_solver_B_rhs.petscvec",m_comm.rank(),m_comm.get());
	write_PETSC_vector_MATLAB(vec_C_micro_t_phi_0_PETSc,m_scratch_folder_path + "/ext_solver_B_rhs.m",m_comm.get());

	VecDestroy(&vec_phi_0_PETSc);
	VecDestroy(&vec_force_PETSc);
	VecDestroy(&vec_C_micro_t_phi_0_PETSc);
	VecDestroy(&vec_C_BIG_t_phi_0_PETSc);
};

}