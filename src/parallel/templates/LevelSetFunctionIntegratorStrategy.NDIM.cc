/*
 * File:        LevelSetFunctionIntegratorStrategy.NDIM.cc
 * Copyright:   (c) 2005-2008 Kevin T. Chu and Masa Prodanovic
 * Revision:    $Revision: 1.4 $
 * Modified:    $Date: 2006/10/02 00:47:34 $
 * Description: Explicit template instantiation of LSMLIB classes 
 */

#include "SAMRAI_config.h"

#include "LevelSetFunctionIntegratorStrategy.h"
#include "LevelSetFunctionIntegratorStrategy.cc"

template class LSMLIB::LevelSetFunctionIntegratorStrategy<NDIM>;
