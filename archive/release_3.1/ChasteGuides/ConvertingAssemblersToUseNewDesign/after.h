
#include "AbstractLinearEllipticPde.hpp"
// the 2 new parents new to be included 
#include "AbstractAssemblerSolverHybrid.hpp"
#include "AbstractStaticLinearPdeSolver.hpp"  // or AbstractDynamicinearPdeSolver


template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
class SimpleLinearEllipticSolver 
     // new parents: See assembler/solver description page for what NORMAL means.
     // Second should be either AbstractStaticLinearPdeSolver or AbstractDynamicLinearPdeSolver
   : public AbstractAssemblerSolverHybrid<ELEMENT_DIM, SPACE_DIM, 1, NORMAL>,  
     public AbstractStaticLinearPdeSolver<ELEMENT_DIM, SPACE_DIM, 1>     
{
protected:
    AbstractLinearEllipticPde<ELEMENT_DIM,SPACE_DIM>* mpEllipticPde;

    
    virtual c_matrix<double, 1*(ELEMENT_DIM+1), 1*(ELEMENT_DIM+1)> ComputeMatrixTerm(
        c_vector<double, ELEMENT_DIM+1>& rPhi,
        c_matrix<double, SPACE_DIM, ELEMENT_DIM+1>& rGradPhi,
        ChastePoint<SPACE_DIM>& rX,
        c_vector<double,1>& rU,
        c_matrix<double,1,SPACE_DIM>& rGradU,
        Element<ELEMENT_DIM,SPACE_DIM>* pElement)
    {
       .. 
    }

    
    virtual c_vector<double,1*(ELEMENT_DIM+1)> ComputeVectorTerm(
        c_vector<double, ELEMENT_DIM+1>& rPhi,
        c_matrix<double, SPACE_DIM, ELEMENT_DIM+1>& rGradPhi,
        ChastePoint<SPACE_DIM>& rX,
        c_vector<double,1>& rU,
        c_matrix<double,1,SPACE_DIM>& rGradU,
        Element<ELEMENT_DIM,SPACE_DIM>* pElement)
    {
       ..
    }
        

    virtual c_vector<double, ELEMENT_DIM> ComputeVectorSurfaceTerm(const BoundaryElement<ELEMENT_DIM-1,SPACE_DIM>& rSurfaceElement,
            c_vector<double, ELEMENT_DIM>& rPhi,
            ChastePoint<SPACE_DIM>& rX)
    {
       ..
    }

    //  **** ADD THE FOLLOWING METHOD ****. 
    // It implements a pure method on the solver parent class by
    // calling a method on the hyrid parent.
    
    /**
     * Delegate to AbstractAssemblerSolverHybrid::SetupGivenLinearSystem.
     *  @param currentSolution The current solution which can be used in setting up
     *   the linear system if needed (NULL if there isn't a current solution)
     *  @param computeMatrix Whether to compute the LHS matrix of the linear system
     *   (mainly for dynamic solves).
     */
    void SetupLinearSystem(Vec currentSolution, bool computeMatrix)
    {
        SetupGivenLinearSystem(currentSolution, computeMatrix, this->mpLinearSystem);
    }
    
public:

    // Constuctor calls base class constructors
    SimpleLinearEllipticSolver(AbstractTetrahedralMesh<ELEMENT_DIM,SPACE_DIM>* pMesh,
                               AbstractLinearEllipticPde<ELEMENT_DIM,SPACE_DIM>* pPde,
                               BoundaryConditionsContainer<ELEMENT_DIM,SPACE_DIM,1>* pBoundaryConditions,
                               unsigned numQuadPoints = 2)
        : AbstractAssemblerSolverHybrid<ELEMENT_DIM,SPACE_DIM,1,NORMAL>(pMesh,pBoundaryConditions,numQuadPoints),
          AbstractStaticLinearPdeSolver<ELEMENT_DIM,SPACE_DIM,1>(pMesh)
    {
       mpEllipticPde = pPde;
    }


    void InitialiseForSolve(Vec initialSolution = NULL)
    {
       // Only change is the 'AbstractLinearPdeSolver<ELEMENT_DIM,SPACE_DIM,1>::'
       AbstractLinearPdeSolver<ELEMENT_DIM,SPACE_DIM,1>::InitialiseForSolve(initialSolution);
       
       assert(this->mpLinearSystem);
       this->mpLinearSystem->SetMatrixIsSymmetric(true);
       this->mpLinearSystem->SetKspType("cg");
    }
};



