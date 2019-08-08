#ifndef R_SFHEADERS_SF_POLYGON_H
#define R_SFHEADERS_SF_POLYGON_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf.hpp"
#include "sfheaders/sfc/polygon/sfc_polygon.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"

namespace sfheaders {
namespace sf {

inline SEXP sf_polygon(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& polygon_id,
    SEXP& linestring_id
) {
  Rcpp::List sfc = sfheaders::sfc::sfc_polygon( x, geometry_cols, polygon_id, linestring_id );
  SEXP ids = sfheaders::utils::get_ids( x, polygon_id );
  // Rcpp::Rcout << "id check1 : " << TYPEOF( ids ) << std::endl;
  // Rcpp::Rcout << "id check2 : " << TYPEOF( ids ) << std::endl;

  Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
  return sf;
}

} // sfc
} // sfheaders

#endif