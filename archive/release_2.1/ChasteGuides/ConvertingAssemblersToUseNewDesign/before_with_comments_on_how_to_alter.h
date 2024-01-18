#include "AbstractLinearEllipticPde.hpp"
// the following 3 headers are no longer needed
#include "AbstractLinearAssembler.hpp"
#include <boost/mpl/void.hpp>
#include <boost/mpl/if.hpp>

//  The CONCRETE template parameter can be deleted 
template<unsigned ELEMENT_DIM, unsigned SPACE_DIM, class CONCRETE = boost::mpl::void_> 
class SimpleLinearEllipticAssembler  
  : public AbstractLinearAssembler<ELEMENT_DIM, SPACE_DIM, 1, true, SimpleLinearEllipticAssembler<ELEMENT_DIM, SPACE_DIM, CONCRETE> >
      //  The concrete class will now inherit from two classes: AbstractAssemblerSolverHybrid<ELEMENT_DIM,SPACE_DIM,your_problem_dim,NORMAL>
      //    AND ONE OF:
      //      AbstractStaticLinearPdeSolver<ELEMENT_DIM,SPACE_DIM,your_problem_dim> 
      //    OR
      //      AbstractDynamicLinearPdeSolver<ELEMENT_DIM,SPACE_DIM,your_problem_dim> 
{
public:
    // All these (the following 6 lines) will typically no longer be needed 
    // and can be deleted
    static const unsigned E_DIM = ELEMENT_DIM; 
    static const unsigned S_DIM = SPACE_DIM; 
    static const unsigned P_DIM = 1u; 
    typedef SimpleLinearEllipticAssembler<ELEMENT_DIM, SPACE_DIM, CONCRETE> SelfType;
    typedef AbstractLinearAssembler<ELEMENT_DIM, SPACE_DIM, 1, true, SelfType> BaseClassType; 
    friend class AbstractStaticAssembler<ELEMENT_DIM, SPACE_DIM, 1, true, SelfType>;

protected:

    AbstractLinearEllipticPde<ELEMENT_DIM,SPACE_DIM>* mpEllipticPde;


    // ComputeMatrixTerm, ComputeVectorTerm and ComputeVectorSurfaceTerm don't need to be changed
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


    // ComputeMatrixTerm, ComputeVectorTerm and ComputeVectorSurfaceTerm don't need to be changed
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


    // ComputeMatrixTerm, ComputeVectorTerm and ComputeVectorSurfaceTerm don't need to be changed
    virtual c_vector<double, ELEMENT_DIM> ComputeVectorSurfaceTerm(const BoundaryElement<ELEMENT_DIM-1,SPACE_DIM>& rSurfaceElement,
            c_vector<double, ELEMENT_DIM>& rPhi,
            ChastePoint<SPACE_DIM>& rX)
    {
        ..
    }


public:
    // Constructor needs to call base class constructors of new parents (see new version below)
    SimpleLinearEllipticAssembler(AbstractTetrahedralMesh<ELEMENT_DIM,SPACE_DIM>* pMesh,
                                  AbstractLinearEllipticPde<ELEMENT_DIM,SPACE_DIM>* pPde,
                                  BoundaryConditionsContainer<ELEMENT_DIM,SPACE_DIM,1>* pBoundaryConditions,
                                  unsigned numQuadPoints = 2)
        : AbstractAssembler<ELEMENT_DIM,SPACE_DIM,1>(),
          BaseClassType(numQuadPoints)
    {
        mpEllipticPde = pPde;

        // The following two lines aren't valid anymore and should be deleted
        this->SetMesh(pMesh); 
        this->SetBoundaryConditionsContainer(pBoundaryConditions);
    }

    // PrepareForSolve() doesn't exist anymore. Use InitialiseForSolve if there's anything that needs to be done before the solve
    void PrepareForSolve()
    {
        BaseClassType::PrepareForSolve();
        assert(mpEllipticPde != NULL);
    }
    
    // NOTE: if you have PrepareForAssembleSystem or FinaliseAssembleSystem
    // implemented, these need to be change to PrepareForSetupLinearSystem(Vec currentSolution)
    // and  FinaliseLinearSystem(Vec currentSolution). 
    // 
    // The current time is not passed into either of these. If you need to use it do:
    // double time = PdeSimulationTime::GetTime()


    void InitialiseForSolve(Vec initialSolution)
    {
        // BaseClassType should be given as AbstractLinearPdeSolver
        BaseClassType::InitialiseForSolve(initialSolution);
        assert(this->mpLinearSystem);
        this->mpLinearSystem->SetMatrixIsSymmetric(true);
        this->mpLinearSystem->SetKspType("cg");
    }
};


// All this stuff can be deleted
template<unsigned ELEMENT_DIM, unsigned SPACE_DIM, class CONCRETE>
struct AssemblerTraits<SimpleLinearEllipticAssembler<ELEMENT_DIM, SPACE_DIM, CONCRETE> >
{
    typedef typename boost::mpl::if_<boost::mpl::is_void_<CONCRETE>,
                                     SimpleLinearEllipticAssembler<ELEMENT_DIM, SPACE_DIM, CONCRETE>,
                                     typename AssemblerTraits<CONCRETE>::CVT_CLASS>::type
            CVT_CLASS;
    typedef typename boost::mpl::if_<boost::mpl::is_void_<CONCRETE>,
                                     SimpleLinearEllipticAssembler<ELEMENT_DIM, SPACE_DIM, CONCRETE>,
                                     typename AssemblerTraits<CONCRETE>::CMT_CLASS>::type
            CMT_CLASS;
    typedef typename boost::mpl::if_<boost::mpl::is_void_<CONCRETE>,
                     AbstractAssembler<ELEMENT_DIM, SPACE_DIM, 1u>,
                     typename AssemblerTraits<CONCRETE>::CMT_CLASS>::type
            INTERPOLATE_CLASS;
};
