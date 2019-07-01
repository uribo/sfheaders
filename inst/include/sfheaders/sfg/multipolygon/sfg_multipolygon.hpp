#ifndef R_SFHEADERS_SFG_MULTIPOLYGON_H
#define R_SFHEADERS_SFG_MULTIPOLYGON_H

#include "sfheaders/utils/utils.hpp"
#include "sfheaders/shapes/shapes.hpp"
#include "sfheaders/sfg/sfg_dimension.hpp"
#include "sfheaders/sfg/sfg_attributes.hpp"

namespace sfheaders {
namespace sfg {

// multipolygon is a list of list of linestrings (matrices)
inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im
) {
  Rcpp::List p( 1 );
  Rcpp::List mp( 1 );
  p[0] = im;
  mp[0] = p;
  size_t n_col = im.ncol();
  std::string dim = sfheaders::sfg::sfg_dimension( n_col );

  std::string geom_type = "MULTIPOLYGON";
  mp.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

  return mp;
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm
) {
  Rcpp::List p( 1 );
  Rcpp::List mp( 1 );
  p[0] = nm;
  mp[0] = p;
  size_t n_col = nm.ncol();
  std::string dim = sfheaders::sfg::sfg_dimension( n_col );

  std::string geom_type = "MULTIPOLYGON";
  mp.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

  return mp;
}

inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df
) {

  Rcpp::NumericMatrix nm = sfheaders::utils::df_to_matrix( df );
  Rcpp::List p( 1 );
  Rcpp::List mp( 1 );
  p[0] = nm;
  mp[0] = p;
  size_t n_col = nm.ncol();
  std::string dim = sfheaders::sfg::sfg_dimension( n_col );

  std::string geom_type = "MULTIPOLYGON";
  mp.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

  return mp;
}

// need to check if it's a list of lists, OR a list with a matrix or df...

inline SEXP sfg_multipolygon(
    Rcpp::List& lst
) {
  Rcpp::List mp( 1 );
  mp[0] = lst;
  // each list element must be a matrix
  std::string dim = sfheaders::sfg::sfg_dimension( lst );

  std::string geom_type = "MULTIPOLYGON";
  lst.attr("class") = sfheaders::sfg::sfg_attributes( dim, geom_type );

  return lst;
}


inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols
) {
  Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
  return sfg_multipolygon( nm );
}

inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols
) {
  Rcpp::NumericMatrix nm = sfheaders::shapes::get_mat( df, cols );
  return sfg_multipolygon( nm );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& cols
) {
  Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
  return sfg_multipolygon( nm2 );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& cols
) {
  Rcpp::NumericMatrix nm2 = sfheaders::shapes::get_mat( nm, cols );
  return sfg_multipolygon( nm2 );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& cols
) {
  Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
  return sfg_multipolygon( im2 );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& cols
) {
  Rcpp::IntegerMatrix im2 = sfheaders::shapes::get_mat( im, cols );
  return sfg_multipolygon( im2 );
}

// We're still on single sfg objects.
// when we go up to sfc objects then we will need multiline_id & line_id
inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    int& id_col
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
  return sfg_multipolygon( lst );
}

inline SEXP sfg_multipolygon(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( df, cols, id_col );
  return sfg_multipolygon( lst );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::IntegerVector& cols,
    int& id_col
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
  return sfg_multipolygon( lst );
}

inline SEXP sfg_multipolygon(
    Rcpp::NumericMatrix& nm,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( nm, cols, id_col );
  return sfg_multipolygon( lst );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& cols,
    int& id_col
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
  return sfg_multipolygon( lst );
}

inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
) {
  Rcpp::List lst = sfheaders::shapes::get_listMat( im, cols, id_col );
  return sfg_multipolygon( lst );
}

  inline SEXP sfg_multipolygon(
    Rcpp::IntegerMatrix& im,
    Rcpp::IntegerVector& geometry_cols,
    int& polygon_id_column,
    int& line_id_column
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( im, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( im, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& geometry_cols,
      int& polygon_id_column,
      int& line_id_column
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( nm, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( nm, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp );
  }

  inline SEXP sfg_multipolygon(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& polygon_id_column,
      int& line_id_column
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( df, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp );
  }


  inline SEXP sfg_multipolygon(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      Rcpp::String& polygon_id_column,
      Rcpp::String& line_id_column
  ) {
    Rcpp::List mp = sfheaders::shapes::get_listListMat( df, geometry_cols, polygon_id_column, line_id_column );
    return sfg_multipolygon( mp );
  }


inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::IntegerVector& cols
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
  }
  }

  return Rcpp::List::create(); // never reaches
}



inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    int& line_id
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols, line_id );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols, line_id );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols, line_id );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
  }
  }

  return Rcpp::List::create(); // never reaches
}


// inline SEXP sfg_multipolygon(
//     SEXP& x,
//     Rcpp::IntegerVector& cols,
//     Rcpp::String& line_id
// ) {
//   switch( TYPEOF( x ) ) {
//   case INTSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
//     return sfg_multipolygon( im, cols, line_id );
//   }
//   case REALSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
//     return sfg_multipolygon( nm, cols, line_id );
//   }
//   case VECSXP: {
//     if( Rf_inherits( x, "data.frame") ) {
//     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
//     return sfg_multipolygon( df, cols, line_id );
//   } // else default
//   }
//   default: {
//     Rcpp::stop("sfheaders - unsupported sfg_LINESTRING type");
//   }
//   }
//
//   return Rcpp::List::create(); // never reaches
// }


inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::StringVector& cols
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");
  }
  }

  return Rcpp::List::create(); // never reaches
}

// inline SEXP sfg_multipolygon(
//     SEXP& x,
//     Rcpp::StringVector& cols,
//     int& line_id
// ) {
//   switch( TYPEOF( x ) ) {
//   case INTSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
//     return sfg_multipolygon( im, cols, line_id );
//   }
//   case REALSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("sfheaders - expecting a matrix");
//   }
//     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
//     return sfg_multipolygon( nm, cols, line_id );
//   }
//   case VECSXP: {
//     if( Rf_inherits( x, "data.frame") ) {
//     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
//     return sfg_multipolygon( df, cols, line_id );
//   } // else default
//   }
//   default: {
//     Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");
//   }
//   }
//
//   return Rcpp::List::create(); // never reaches
// }

inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::StringVector& cols,
    Rcpp::String& line_id
) {
  switch( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im, cols, line_id );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm, cols, line_id );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df, cols, line_id );
  } // else default
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");
  }
  }

  return Rcpp::List::create(); // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x
) {
  switch ( TYPEOF( x ) ) {
  case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
    return sfg_multipolygon( im );
  }
  case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
    Rcpp::stop("sfheaders - expecting a matrix");
  }
    Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
    return sfg_multipolygon( nm );
  }
  case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
    return sfg_multipolygon( df );
  } else {
    Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
    return sfg_multipolygon( lst );
  }
  }
  default: {
    Rcpp::stop("sfheaders - unsupported sfg_MULTIPOLYGON type");
  }
  }
  return x; // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols
) {
  if( Rf_isNull( cols ) ) {
    return sfg_multipolygon( x );
  }
  switch( TYPEOF( cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
    return sfg_multipolygon( x, iv );
  }
  case STRSXP: {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
    return sfg_multipolygon( x, sv );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
  return Rcpp::List::create(); // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    Rcpp::String& line_id
) {
  if( Rf_isNull( cols ) ) {
    //Rcpp::Rcout << "String line_id" << std::endl;
    Rcpp::StringVector id_cols( 1 );
    id_cols[0] = line_id;
    SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
    return sfg_multipolygon( x, other_cols, line_id );
  }
  switch( TYPEOF( cols ) ) {
  // case REALSXP: {}
  // case INTSXP: {
  //   Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
  //   return sfg_multipolygon( x, iv, line_id );
  // }
  case STRSXP: {
    Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
    return sfg_multipolygon( x, sv, line_id );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
  return Rcpp::List::create(); // never reaches
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    int& line_id
) {

  if( Rf_isNull( cols ) ) {
    Rcpp::IntegerVector id_cols( 1 );
    id_cols[0] = line_id;
    SEXP other_cols = sfheaders::utils::other_columns( x, id_cols );
    return sfg_multipolygon( x, other_cols, line_id );
  }
  switch( TYPEOF( cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
    return sfg_multipolygon( x, iv, line_id );
  }
    // case STRSXP: {
    //   Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( cols );
    //   return sfg_multipolygon( x, sv, line_id );
    // }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
  return Rcpp::List::create(); // never reaches
}

inline SEXP sfg_multipolygon(
  SEXP& x,
  Rcpp::IntegerVector geometry_cols,
  int& polygon_id,
  int& line_id
) {
  Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, polygon_id, line_id );
  return sfg_multipolygon( mp );
}

inline SEXP sfg_multipolygon(
    SEXP& x,
    Rcpp::StringVector geometry_cols,
    Rcpp::String& polygon_id,
    Rcpp::String& line_id
) {
  Rcpp::List mp = sfheaders::shapes::get_listListMat( x, geometry_cols, polygon_id, line_id );
  return sfg_multipolygon( mp );
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    int& polygon_id,
    int& line_id
) {
  switch( TYPEOF( cols ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector geometry_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
    return sfg_multipolygon( x, geometry_cols, polygon_id, line_id );
  }
  // case STRSXP: {
  //   Rcpp::StringVector geometry_cols = Rcpp::as< Rcpp::StringVector >( cols );
  //   return sfg_multipolygon( x, geometry_cols, polygon_id, line_id );
  // }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
}

inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    Rcpp::String& polygon_id,
    Rcpp::String& line_id
) {

  switch( TYPEOF( cols ) ) {
  // case REALSXP: {}
  // case INTSXP: {
  //   Rcpp::IntegerVector geometry_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
  //   return sfg_multipolygon( x, geometry_cols, polygon_id, line_id );
  // }
  case STRSXP: {
    Rcpp::StringVector geometry_cols = Rcpp::as< Rcpp::StringVector >( cols );
    return sfg_multipolygon( x, geometry_cols, polygon_id, line_id );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
}


inline SEXP sfg_multipolygon(
    SEXP& x,
    SEXP& cols,
    SEXP& polygon_id,
    SEXP& line_id
) {
  if( Rf_isNull( polygon_id ) && Rf_isNull( line_id ) ) {
    return sfg_multipolygon( x, cols );
  }

  if( Rf_isNull( polygon_id ) && !Rf_isNull( line_id ) ) {

  }

  if( !Rf_isNull( polygon_id ) && Rf_isNull( line_id ) ) {

  }

  // otherwise they are both provided
  if( TYPEOF( polygon_id ) != TYPEOF( line_id ) ) {
    Rcpp::stop("polygon_id and line_id must be the same type");
  }

  switch( TYPEOF( line_id ) ) {
  case REALSXP: {}
  case INTSXP: {
    Rcpp::IntegerVector iv_line = Rcpp::as< Rcpp::IntegerVector >( line_id );
    Rcpp::IntegerVector iv_polygon = Rcpp::as< Rcpp::IntegerVector >( polygon_id );
    int il = iv_line[0];
    int ip = iv_polygon[0];
    return sfg_multipolygon( x, cols, il, ip );
  }
  case STRSXP: {
    Rcpp::StringVector sv_line = Rcpp::as< Rcpp::StringVector >( line_id );
    Rcpp::StringVector sv_polygon = Rcpp::as< Rcpp::StringVector >( polygon_id );

    Rcpp::String sl = sv_line[0];
    Rcpp::String sp = sv_polygon[0];
    return sfg_multipolygon( x, cols, sl, sp );
  }
  default: {
    Rcpp::stop("sfheaders - unknown column types");
  }
  }
  return Rcpp::List::create(); // never reaches
}


} // sfg
} // sfheaders

#endif