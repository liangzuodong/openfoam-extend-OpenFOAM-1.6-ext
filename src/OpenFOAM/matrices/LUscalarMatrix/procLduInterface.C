/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "procLduInterface.H"
#include "lduInterfaceField.H"
#include "cyclicLduInterface.H"
#include "processorLduInterface.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::procLduInterface::procLduInterface
(
    const lduInterfaceField& interface,
    const scalarField& coeffs
)
:
    faceCells_(interface.interface().faceCells()),
    coeffs_(coeffs),
    myProcNo_(-1),
    neighbProcNo_(-1)
{
    if (isA<processorLduInterface>(interface.interface()))
    {
        const processorLduInterface& pldui =
            refCast<const processorLduInterface>(interface.interface());

        myProcNo_ = pldui.myProcNo();
        neighbProcNo_ = pldui.neighbProcNo();
    }
    else if (isA<cyclicLduInterface>(interface.interface()))
    {
    }
    else
    {
        FatalErrorIn
        (
            "procLduInterface::procLduInterface"
            "(const lduInterfaceField&, const scalarField&"
        )   << "unknown lduInterface type " << interface.interface().type()
            << exit(FatalError);
    }
}


Foam::procLduInterface::procLduInterface(Istream& is)
:
    faceCells_(is),
    coeffs_(is),
    myProcNo_(readLabel(is)),
    neighbProcNo_(readLabel(is))
{}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<(Ostream& os, const procLduInterface& cldui)
{
    os  << cldui.faceCells_
        << cldui.coeffs_
        << cldui.myProcNo_
        << cldui.neighbProcNo_;

    return os;
}


// ************************************************************************* //
