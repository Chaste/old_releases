# Configuration

"""Copyright (C) University of Oxford, 2005-2011

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Chaste.

Chaste is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

Chaste is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details. The offer of Chaste under the terms of the
License is subject to the License being interpreted in accordance with
English Law and subject to any action against the University of Oxford
being under the jurisdiction of the English Courts.

You should have received a copy of the GNU Lesser General Public License
along with Chaste. If not, see <http://www.gnu.org/licenses/>.
"""

"""Hostconfig settings for Matlab integration with Chaste.

This settings file assumes that you followed the installation instructions at
https://chaste.cs.ox.ac.uk/cgi-bin/trac.cgi/wiki/InstallGuides/MatlabUbuntu.

If you do not wish to permanently set the environmental vaiables, you can modify
the code at 'Get environment variables', such that the variable are given the 
actual location of the Chaste source code, modified Chaste libraries, and Matlab
installation location.

"""

import glob
import os

#### Get environment variables 
chaste = os.environ["CHASTE"]
matlabroot = os.environ["MATLABROOT"]
####

# Check which version of Ubuntu this is
fp = open('/etc/issue')
ubuntu_ver = fp.read().split()[1]
fp.close()
petsc_2_2_path = ''
petsc_ver = 3.1
petsc_path = os.path.join(chaste, 'petsc')
petsc_build_name = 'openmpi-debug'
petsc_build_name_profile = petsc_build_name
petsc_build_name_optimized = petsc_build_name
dealii_path = None
intel_path = None
icpc = 'icpc'
other_includepaths = ['/usr/include/metis/',
                      os.path.join(chaste, 'boost/include'),
                      os.path.join(chaste, 'hdf5/include')]
other_libpaths = [os.path.join(chaste, 'boost/lib'),
                  os.path.join(chaste, 'hdf5/lib'),
                  os.path.join(matlabroot, 'bin/glnxa64'), 
                  os.path.join(matlabroot, 'sys/os/glnxa64')] 
libs_for_petsc = ['petsc', 'HYPRE']
other_libraries = libs_for_petsc + ['boost_serialization', 'boost_filesystem',
                                    'boost_system', 'xerces-c',
                                    'hdf5', 'z',
                                    'parmetis', 'metis']
blas_lapack = ['mwlapack', 'mwblas']
tools = {'xsd': '/usr/bin/xsdcxx',
         'mpirun': '/usr/bin/mpirun.openmpi',
         'mpicxx': '/usr/bin/mpic++.openmpi'}

def Configure(prefs, build):
    """Set up the build configuring.
    
    prefs can specify which version of various libraries we should use, and which optional libraries.
    VTK and CVODE support default on if they are installed.
    
    build is an instance of BuildTypes.BuildType.
    """
    global use_cvode
    global use_vtk   
    use_vtk = False
    use_cvode = False
