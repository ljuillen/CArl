#include "CArl_FETI_iterate.h"

/**	\brief Program responsible to finish the FETI setup and launch the iterations
 *
 *	This program's input file description can be found at the documentation of the function 
 *  CArl::get_input_params(GetPot& field_parser, feti_iterate_params& input_params).
 *  
 *  It will use the following files ... 
 *  * ... from the `input_params.coupling_path_base` folder:
 *    + coupling matrices C_1 and C_2. *Files*:
 *      - `coupling_matrix_macro.petscmat`
 *      - `coupling_matrix_micro.petscmat`
 *
 *  * ... from the `input_params.scratch_folder_path` folder:
 *    + scalar values (iteration, residual, RB mode corrections). *Files*:
 *      - `FETI_iter_scalar_data.dat`
 *    + solutions x_kkk,1 and x_kkk,2, from the system K_i * x_kkk,i = C_i^T*p_kkk. *Files*:
 *      - `ext_solver_A_sys_sol_vec.petscvec`
 *      - `ext_solver_B_sys_sol_vec.petscvec`
 *    + previous iteration vectors r(kkk) anf phi(kkk)
 *      - `FETI_iter__phi__[kkk].petscvec`
 *	    - `FETI_iter__r__[kkk].petscvec`
 *    + (several) previous iterations vectors p(jjj), q(jjj) (used for re-orthogonalization). *Files*:
 *      - `FETI_iter__q__[jjj].petscvec`, jjj = 0 ... kkk - 1
 *      - `FETI_iter__p__[jjj].petscvec`, jjj = 0 ... kkk
 *    + previous p(jjj).q(jjj) values (with jjj = 0 ... kkk - 1). *Files*:
 *      - `FETI_iter_p_dot_q.dat`
 *    + matrix inv (R_I^t * R_I) = inv(R_2^t*C_2^t*C_2*R_2), used for the rigid body modes projections. *Files*:
 *      - [RB] `rb_inv_RITRI.petscmat`.
 *    + rigid body mode vectors multiplied by C_2. *Files*:
 *      - [RB] `rb_coupl_vector_[iii]_n_[nb. of vectors].petscvec`
 *  * ... from the micro system folder (common vector path given by `input_params.RB_vectors_base`):
 *    + rigid body mode vectors. *Files*:
 *      - [RB] `[input_params.RB_vectors_base]_rb_vector_[iii]_n_[nb. of vectors].petscvec`
 *
 * The items marked with a [RB] are only needed if the rigid body modes projectors are used.
 * In the last two cases, [nb. of vectors] is the number of rigid body mode vectors (given by `input_params.nb_of_rb_vectors`)
 * and [iii] is an integer going from 0 to `input_params.nb_of_rb_vectors - 1` (following C++ notation).
 *
 * This program outputs a series of files, all inside the `input_params.scratch_folder_path` folder:
 *   + (append) scalar values (iteration, residual, RB mode corrections). *Files*:
 *     - `FETI_iter_scalar_data.dat`
 *   + (overwrite) vectors used as the RHS for the external solvers. *Files*:
 *     - `ext_solver_A_rhs.petscvec`
 *     - `ext_solver_B_rhs.petscvec`
 *   + next iteration vectors, phi(kkk+1), r(kkk+1), q(kkk+1), p(kkk+1). *Files*:
 *     - `FETI_iter__phi__[kkk+1].petscvec`
 *     - `FETI_iter__r__[kkk+1].petscvec`
 *     - `FETI_iter__q__[kkk+1].petscvec`
 *     - `FETI_iter__p__[kkk+1].petscvec`
 *   + (append) p(kkk).q(kkk) value. *Files*:
 *     - `FETI_iter_p_dot_q.dat`
 */

int main(int argc, char** argv) {

	// --- Initialize libMesh
	libMesh::LibMeshInit init(argc, argv);

	// Do performance log?
	libMesh::PerfLog perf_log("Main program");

	// libMesh's C++ / MPI communicator wrapper
	libMesh::Parallel::Communicator& WorldComm = init.comm();

	// Number of processors and processor rank.
	int rank = WorldComm.rank();
	int nodes = WorldComm.size();

	// --- Set up inputs

	// Command line parser
	GetPot command_line(argc, argv);

	// File parser
	GetPot field_parser;

	// If there is an input file, parse it to get the parameters. Else, parse the command line
	std::string input_filename;
	if (command_line.search(2, "--inputfile", "-i")) {
		input_filename = command_line.next(input_filename);
		field_parser.parse_input_file(input_filename, "#", "\n", " \t\n");
	} else {
		field_parser = command_line;
	}

	carl::feti_iterate_params input_params;
	get_input_params(field_parser, input_params);

		// Object containing the FETI operations
	carl::FETI_Operations feti_op(WorldComm,input_params.scratch_folder_path,input_params.coupling_path_base);

	// --- Set current iteration
	feti_op.set_iteration_from_file();

	// --- Define if the rb modes will be used or not
	feti_op.using_rb_modes(input_params.bUseRigidBodyModes);

	// --- Read the files!

	// Read up the coupling matricesconst std::string& filename)
	feti_op.set_coupling_matrix_R_micro();
	feti_op.set_coupling_matrix_R_BIG();

	// Read operations needed if we are using the rigid body modes
	if(input_params.bUseRigidBodyModes)
	{
		// Read the RB-related vectors and matrices
		feti_op.read_null_space_vecs(input_params.RB_vectors_base,input_params.nb_of_rb_vectors);
		feti_op.read_null_space_inv_RITRI_mat();
	}

	// // --- Set up any matrices or vectors needed before calculating the outputs
	// // Set up the preconditioner
	// feti_op.set_preconditioner(input_params.CG_precond_type /*, initial_set = */ false);

	// // --- "Finish" the current iteration, kkk + 1
	// // Calculate q(kkk) and gamma(kkk)
	// feti_op.calculate_q_and_gamma();

	// // Calculate phi(kkk+1) and r(kkk+1)
	// feti_op.calculate_phi_and_r();

	// // Calculations needed if we are using the rigid body modes
	// if(input_params.bUseRigidBodyModes)
	// {
	// 	// Calculate the rigid body modes correction RB_corr
	// 	feti_op.calculate_rb_correction();
	// }

	// // Check the convergence
	// IterationStatus current_iteration_status = CArl::IterationStatus::ITERATING;
	// feti_op.check_convergence(input_params);

	// // Calculate r(kkk+1), q(kkk+1) and p(kkk+1)
	// feti_op.calculate_iter_vecs();

	// // Export them
	// feti_op.export_iter_vecs();

	// // In all cases, export the scalar data, rho(kkk+1), gamma(kkk+1) and, if pertinent, |RB_corr| 
	// // feti_op.export_scalar_data();

	// switch (current_iteration_status)
	// {
	// 	case CArl::IterationStatus::ITERATING :
	// 			// --- Continue the iteration
	// 			std::cout << " > Still iterating ... " << std::endl;

	// 			// Export the Ct_i * p(kkk+1) vectors
	// 			feti_op.export_ext_solver_rhs_iteration();

	// 			// // --- Launch the "iter_script.sh" script --- ONLY ON THE FIRST PROC!
	// 			// if(WorldComm.rank() == 0)
	// 			// {
	// 			// 	std::string iter_script_command = ". " + input_params.scratch_folder_path + "/FETI_iter_script.sh";
	// 			// 	carl::exec_command(iter_script_command);
	// 			// }
	// 			break;
	// 	case CArl::IterationStatus::CONVERGED :
	// 			// --- Well ... converged!
	// 			std::cout << " > Converged !" << std::endl;

	// 			// // --- Launch the "iter_script.sh" script --- ONLY ON THE FIRST PROC!
	// 			// if(WorldComm.rank() == 0)
	// 			// {
	// 			// 	std::string sol_script_command = ". " + input_params.scratch_folder_path + "/FETI_sol_script.sh";
	// 			// 	carl::exec_command(sol_script_command);
	// 			// }
	// 			break;
	// 	case CArl::IterationStatus::DIVERGED :
	// 			// --- Well, we have to stop here ...
	// 			std::cout << " > DIVERGED !" << std::endl;
				
	// 			break;
	// }

	// // Print the current values of the convergence parameters
	// feti_op.print_previous_iters_conv( /* nb. of iterations = 5 */);

	return 0;
}
