#ifndef R_SFHEADERS_UTILS_COLUMNS_H
#define R_SFHEADERS_UTILS_COLUMNS_H

#include <Rcpp.h>
#include "sfheaders/utils/matrix/matrix.hpp"
#include "sfheaders/utils/sexp/sexp.hpp"
#include "sfheaders/utils/vectors/vectors.hpp"

namespace sfheaders {
namespace utils {

  // if the line_id cols are supplied, but the geometry_cols are not
  // we need to know the rest of the columns so we can supply them
  inline SEXP other_columns(
      Rcpp::IntegerVector& other_cols,
      Rcpp::IntegerVector& id_cols
  ) {

    // Can't use SETDIFF because I need the order maintained
    // Rcpp::IntegerVector iv = Rcpp::setdiff( other_cols, id_cols );
    // return iv;

    int n_id_cols = id_cols.length();
    int i;
    for( i = (n_id_cols - 1); i >= 0; i-- ) {
      int to_remove = id_cols[ i ];
      other_cols.erase( to_remove );
    }
    return other_cols;
  }

  inline SEXP other_columns(
      Rcpp::NumericVector& other_cols,
      Rcpp::NumericVector& id_cols
  ) {

    // Rcpp::Rcout << "other_cols: " << other_cols << std::endl;
    // Rcpp::Rcout << "id_cols: " << id_cols << std::endl;

    // Rcpp::NumericVector nv = Rcpp::setdiff( other_cols, id_cols );
    // return nv;

    int n_id_cols = id_cols.length();
    int i;
    for( i = (n_id_cols - 1); i >= 0; i-- ) {
      int to_remove = id_cols[ i ];
      other_cols.erase( to_remove );
    }
    // Rcpp::Rcout << "erased columns, left with : " << other_cols << std::endl;
    return other_cols;
  }


  inline SEXP other_columns(
      Rcpp::StringVector& all_cols,
      Rcpp::StringVector& id_cols
  ) {

    // Rcpp::StringVector sv = Rcpp::setdiff( all_cols, id_cols );
    // return sv;
    int n_id_cols = id_cols.size();
    int n_other_cols = all_cols.size();
    int i, j;
    bool is_in = false;
    Rcpp::IntegerVector id_col_index( n_id_cols );
    for( i = 0; i < n_id_cols; i++ ) {
      is_in = false;
      Rcpp::String id_col = id_cols[i];
      for( j = 0; j < n_other_cols; j++ ) {
        Rcpp::String a_col = all_cols[j];
        if( id_col == a_col ) {
          // this column is one of the id ones, so we shouldn't keep it.
          is_in = true;
          break;
        }
      }
      if( is_in ) {
        all_cols.erase( j );
      }
    }
    return all_cols;
    //return other_cols;
  }

  inline SEXP other_columns(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& id_cols
  ) {
    Rcpp::StringVector df_names = df.names();
    return other_columns( df_names, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& id_cols
  ) {
    int n_col = df.ncol();
    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    return other_columns( other_cols, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::DataFrame& df,
      Rcpp::NumericVector& id_cols
  ) {
    int n_col = df.ncol();

    // Rcpp::Rcout << "n_col: " << n_col << std::endl;

    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( other_cols );
    return other_columns( nv, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& id_cols
  ) {
    Rcpp::StringVector nm_names = sfheaders::utils::matrix_names( nm );
    return other_columns( nm_names, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::NumericMatrix& nm,
      Rcpp::IntegerVector& id_cols
  ) {
    int n_col = nm.ncol();
    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    return other_columns( other_cols, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::NumericMatrix& nm,
      Rcpp::NumericVector& id_cols
  ) {
    int n_col = nm.ncol();
    Rcpp::IntegerVector other_cols = Rcpp::seq( 0, n_col - 1 );
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( other_cols );
    return other_columns( nv, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& id_cols
  ) {
    Rcpp::StringVector im_names = sfheaders::utils::matrix_names( im );
    return other_columns( im_names, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::IntegerMatrix& im,
      Rcpp::IntegerVector& id_cols
  ) {
    int n_col = im.ncol();
    Rcpp::IntegerVector im_cols = Rcpp::seq( 0, n_col - 1 );
    return other_columns( im_cols, id_cols );
  }

  inline SEXP other_columns(
      Rcpp::IntegerMatrix& im,
      Rcpp::NumericVector& id_cols
  ) {
    int n_col = im.ncol();
    Rcpp::IntegerVector im_cols = Rcpp::seq( 0, n_col - 1 );
    Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( im_cols );
    return other_columns( nv, id_cols );
  }


  inline SEXP other_columns(
      SEXP& x,
      Rcpp::IntegerVector& id_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x ) ;
      return other_columns( im, id_cols );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return other_columns( nm, id_cols );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return other_columns( df, id_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported object");
    }
    }
  }

  inline SEXP other_columns(
      SEXP& x
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x ) ;
      Rcpp::IntegerVector cols = Rcpp::seq( 0, (im.ncol() - 1) );
      return cols;
      //return other_columns( im, id_cols );
    }
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      Rcpp::IntegerVector cols = Rcpp::seq( 0, (nm.ncol() - 1) );
      return cols;
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return df.names();
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported object");
    }
    }
  }


  inline SEXP other_columns(
      SEXP& x,
      Rcpp::NumericVector& id_cols
  ) {

    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x ) ;
      return other_columns( im, id_cols );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return other_columns( nm, id_cols );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return other_columns( df, id_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported object");
    }
    }
  }

  inline SEXP other_columns(
      SEXP& x,
      Rcpp::StringVector& id_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x ) ;
      return other_columns( im, id_cols );
    }
    }
    case REALSXP: {
    if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return other_columns( nm, id_cols );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame") ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return other_columns( df, id_cols );
    }
    }
    default: {
      Rcpp::stop("sfheaders - unsupported object");
    }
    }
  }


  inline SEXP other_columns(
      SEXP& x,
      SEXP& id_cols // will be a vector
  ) {

    if( Rf_isNull( id_cols ) ) {
      return other_columns( x );
    }

    switch( TYPEOF( id_cols ) ) {
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( id_cols );
      Rcpp::NumericVector nv2 = Rcpp::sort_unique( nv );
      return other_columns( x, nv2 );
    }
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( id_cols );
      Rcpp::IntegerVector iv2 = Rcpp::sort_unique( iv );
      return other_columns( x, iv2 );
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( id_cols );
      Rcpp::StringVector sv2 = Rcpp::sort_unique( sv );
      return other_columns( x, sv2 );
    }
    default: {
      Rcpp::stop("sfheaders - unsupported column types");
    }
    }
  }

  // when 2 columns are known
  inline SEXP other_columns(
    SEXP& x,
    SEXP& col_1,
    SEXP& col_2
  ) {

    if( Rf_isNull( col_1 ) && Rf_isNull( col_2 ) ) {
      return other_columns( x );
    }

    if( Rf_isNull( col_1 ) && !Rf_isNull( col_2 ) ) {
      return other_columns( x, col_2 );
    }

    if( !Rf_isNull( col_1 ) && Rf_isNull( col_2 ) ) {
      return other_columns( x, col_1 );
    }

    SEXP cols = sfheaders::utils::concatenate_vectors( col_1, col_2 );
    return other_columns( x, cols );

  }

    inline SEXP other_columns(
        SEXP& x,
        SEXP& col_1,
        SEXP& col_2,
        SEXP& col_3
    ) {

      if( !Rf_isNull( col_1 ) && Rf_isNull( col_2 ) && Rf_isNull( col_3 ) ) {
        return other_columns( x, col_1 );
      }

      if( Rf_isNull( col_1 ) && !Rf_isNull( col_2 ) && Rf_isNull( col_3 ) ) {
        return other_columns( x, col_2 );
      }

      if( Rf_isNull( col_1 ) && Rf_isNull( col_2 ) && !Rf_isNull( col_3 ) ) {
        return other_columns( x, col_3 );
      }

      if( Rf_isNull( col_1) && !Rf_isNull( col_2 ) && !Rf_isNull( col_3 ) ) {
        return other_columns( x, col_2, col_3 );
      }

      if ( !Rf_isNull( col_1 ) && Rf_isNull( col_2 ) && !Rf_isNull( col_3 ) ) {
        return other_columns( x, col_1, col_3 );
      }

      if ( !Rf_isNull( col_1 ) && !Rf_isNull( col_2 ) && Rf_isNull( col_3 ) ) {
        return other_columns( x, col_1, col_2 );
      }

      if ( Rf_isNull( col_1 ) && Rf_isNull( col_2 ) && Rf_isNull( col_3 ) ) {
        // then it's just all teh columns
        return other_columns( x );
      }

      // combine cols 1, 2 and 3
      SEXP other_cols_1 = sfheaders::utils::concatenate_vectors( col_1, col_2 );
      SEXP other_cols = sfheaders::utils::concatenate_vectors( other_cols_1, col_3 );
      return other_columns( x, other_cols );

    }

  // #nocov start

  inline SEXP column_positions(
      Rcpp::NumericMatrix& nm,
      Rcpp::StringVector& cols
  ) {

    Rcpp::StringVector m_names = sfheaders::utils::get_sexp_col_names( nm );
    R_xlen_t n_col = cols.size();

    Rcpp::IntegerVector iv( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; i++ ) {
      Rcpp::String this_col = cols[i];
      iv[ i ] = sfheaders::utils::where_is( this_col, m_names );
    }
    return iv;
  }

  inline SEXP column_positions(
      Rcpp::IntegerMatrix& im,
      Rcpp::StringVector& cols
  ) {

    Rcpp::StringVector m_names = sfheaders::utils::get_sexp_col_names( im );
    R_xlen_t n_col = cols.size();

    Rcpp::IntegerVector iv( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; i++ ) {
      Rcpp::String this_col = cols[i];
      iv[ i ] = sfheaders::utils::where_is( this_col, m_names );
    }
    return iv;
  }

  // #nocov end

  inline SEXP column_positions(
    SEXP& x,
    Rcpp::StringVector& cols
  ) {

    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("sfheaders - expecting matrix when finding column positions");  // #nocov
    }

    Rcpp::StringVector m_names = sfheaders::utils::get_sexp_col_names( x );
    R_xlen_t n_col = cols.size();

    Rcpp::IntegerVector iv( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; i++ ) {
      Rcpp::String this_col = cols[i];
      iv[ i ] = sfheaders::utils::where_is( this_col, m_names );
    }
    return iv;
  }


} // utils
} // sfheaders

#endif
