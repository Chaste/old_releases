
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

lib_root = "/Users/bordas/work/chaste-libs/"

petsc_3_0_path='/opt/local/lib/petsc/'
parmetis_path=lib_root + 'ParMetis-3.1/'

petsc_build_name = 'macx'
petsc_build_name_profile = 'macx'
petsc_build_name_optimized = 'macx'

noccache = "true"

other_includepaths = ['/opt/local/include',
                      lib_root + 'xsd-3.2.0-i686-macosx/libxsd',
                      parmetis_path]
other_libpaths = ['/opt/local/lib', 
                  '/opt/local/lib/petsc/lib',
                  lib_root + 'lib',
                  parmetis_path]
blas_lapack = []
other_libraries = ['X11', 'boost_serialization-mt', 'xerces-c', 'z', 'hdf5', 'parmetis', 'metis']
ldflags='-framework vecLib'

tools = {'mpirun': '/opt/local/lib/openmpi/bin/mpirun',
         'mpicxx': '/opt/local/lib/openmpi/bin/mpicxx',
         'xsd': '/Users/bordas/work/chaste-libs/bin/xsd'}
