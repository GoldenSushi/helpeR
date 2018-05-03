#include <Rcpp.h>
#include <string>
#include <iostream>
#include "valid.hpp"

//'Validation
//'
//'Crosses georreferenced classification predictions with their respective validation tables. Both tables must have columns named X, Y, and Prediction
//'@param valid Validation data frame
//'@param predic Prediction data frame
//'@export
// [[Rcpp::export]]
Rcpp::DataFrame validation(Rcpp::DataFrame valid, Rcpp::DataFrame predic) {
  
  Validation val(valid, predic);
  val.make();
  return val.makeValid();
  
  }
