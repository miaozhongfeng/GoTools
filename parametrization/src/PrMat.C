/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/* (c) Copyright 1998 by                                                     */
/*     SINTEF, Oslo, Norway                                                  */
/*     All rights reserved. See the copyright.h for more details.            */
/*                                                                           */
/*****************************************************************************/

/********************************************************************
 FILENAME    : PrMat.C
 AUTHOR      : Michael Floater, SINTEF
 DATE        : Nov 98
 DESCRIPTION : Implementation of methods in the class PrMat.
 CHANGE LOG  :
*********************************************************************/

#include "GoTools/parametrization/PrMat.h"
#include "GoTools/utils/errormacros.h"

//-----------------------------------------------------------------------------
PrMat::PrMat(int m, int n, double val)
//-----------------------------------------------------------------------------
    : a_(m*n, val), m_(m), n_(n)
{
}

//-----------------------------------------------------------------------------
void PrMat::redim(int m, int n)
//-----------------------------------------------------------------------------
{
  a_.resize(m*n);
  m_ = m;
  n_ = n;
}

//-----------------------------------------------------------------------------
PrMat::~PrMat()
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
void PrMat::read(std::istream& is)
//-----------------------------------------------------------------------------
{
    int ind = 0;
    for (int i = 0; i < m_; ++i) {
	for (int j = 0; j < n_; ++j) {
	    is >> a_[ind++];
	}
    }
}



//-----------------------------------------------------------------------------
void PrMat::prod(const PrVec& x, PrVec& y) const // Find y = Ax
//-----------------------------------------------------------------------------
{
  if(x.size() != n_ || y.size() != m_)
  {
    MESSAGE("Error in PrMat::prod");
    MESSAGE("Matrix and vectors have incompatible sizes");
    return;
  }

  int i,j;
  for(i=0; i<m_; i++)
  {
    y(i) = 0.0;
    for(j=0; j<n_; j++)
    {
      y(i) += (*this)(i,j) * x(j);
    }
  }
}


//-----------------------------------------------------------------------------
double PrMat::operator () (int i, int j) const
//-----------------------------------------------------------------------------
{
  return a_[i*n_+j];
}