#ifndef R_SFHEADERS_SF_LINESTRING_H
#define R_SFHEADERS_SF_LINESTRING_H

#include <Rcpp.h>
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/sf/sf_utils.hpp"
#include "sfheaders/sfc/linestring/sfc_linestring.hpp"
#include "sfheaders/utils/unique/unique_ids.hpp"
#include "sfheaders/shapes/shapes.hpp"

namespace sfheaders {
namespace sf {

// the design should be;
// given the objet, get the 'ids' out here;
// then create an sfc
// and attach the ids
//
// BUT, this is a two-step id extract
// and is there a guarantee they'll be combined in the correct order??

  inline SEXP sf_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& linestring_id
  ) {

    Rcpp::List sfc = sfheaders::sfc::sfc_linestring( x, geometry_cols, linestring_id );

    // TODO: we're getting the linestring_ids inside sfc_linestring,
    // and re-doing it here... say what...
    // and for issue 41 we also want to know the row-index of the first
    // row of each sfg, so we can keep the data for that row
    SEXP ids = sfheaders::utils::get_ids( x, linestring_id );

    // SEXP unique_ids = sfheaders::utils::get_sexp_unique( ids );
    // Rcpp::IntegerMatrix line_positions = sfheaders::utils::id_positions( ids );
    // Rcpp::Rcout << line_positions << std::endl;

    Rcpp::DataFrame sf = sfheaders::sf::make_sf( sfc, ids );
    return sf;
  }

  inline SEXP sf_linestring(
    SEXP& x,
    SEXP& geometry_cols,
    SEXP& linestring_id,
    bool& keep
  ) {
    if( !keep ) {
      return sf_linestring( x, geometry_cols, linestring_id );
    }

    // TODO:
    // - get line_positions.
    // - get call sfc_linestring with line_positions as an argument

  }


} // sfc
} // sfheaders

#endif
