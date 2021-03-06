#ifndef R_SFHEADERS_SFC_LINESTRINGS_H
#define R_SFHEADERS_SFC_LINESTRINGS_H

#include <Rcpp.h>
#include "sfheaders/sfc/linestring/sfc_linestring.hpp"

namespace sfheaders {
namespace sfc {

  inline Rcpp::List sfc_linestrings( Rcpp::List& lst ) {
    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::List sfcs(n);

    for( i = 0; i < n; ++i ) {
      SEXP x = lst[i];
      sfcs[i] = sfheaders::sfc::sfc_linestring( x );
    }
    return sfcs;
  }



} // sfc
} // sfheaders

#endif
