# Configuration

"""Copyright (C) University of Oxford, 2005-2009

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

import os

base = '/home/jonc/src/'

petsc_2_2_path = None
petsc_2_3_path = base + 'petsc-2.3.3-p15/'
petsc_build_name = 'linux-gnu'
petsc_build_name_profile = 'linux-gnu'
petsc_build_name_optimized = 'linux-gnu-opt'

dealii_path = None
metis_path = base + 'metis-5.0pre2/'
xsd_path = base + 'xsd-2.3.1-x86_64-linux-gnu/'
mpi_path = base + 'mpi/'

intel_path = None
icpc = 'icpc'

other_includepaths = [metis_path + 'include',
                      xsd_path + 'libxsd']
#other_includepaths.append(mpi_path + 'include')

other_libpaths = [metis_path + 'build/Linux-x86_64']

blas_lapack = ['lapack', 'blas']
other_libraries = ['boost_serialization', 'xerces-c', 'hdf5', 'z', 'metis']

#tools = {'mpicxx': mpi_path + 'bin/mpicxx',
#         'mpirun': mpi_path + 'bin/mpirun'}
tools = {}
