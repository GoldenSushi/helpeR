#include <Rcpp.h>
#include <iostream>
#include <string>
using namespace Rcpp;

//'@title Negative Cleaner
//'@description Substitutes all the negative values in the given Data Frame for 0.
//'@param x The Data Frame user wishes to process.
//'@export
// [[Rcpp::export]]
void negclean (DataFrame x) {
  for (int i = 0; i < x.length(); ++i) {
    NumericVector col = x[i];
    for (int j = 0; j < col.length(); ++j) {
      if (col[j] < 0) 
        col[j] = 0;
    }
  }
  Rcout << "Done." << std::endl;
}

// [[Rcpp::export]]
DataFrame neural_arrange (NumericMatrix df) {
  
  StringVector vec (df.rows());
  StringVector colNames = colnames(df);
  
  for (int i = 0; i < df.rows(); ++i) {
    char* maxName = colNames(0);
    for (int j = 0; j < df.cols(); ++j) {
      double max = df(i, 0);
      if (df(i,j) > max){
        max = df(i,j);
        maxName = colNames(j);
      }
      vec(i) = maxName;
    }
  }
  
  DataFrame newDF = DataFrame::create(Named("Prediction") = vec);
  return newDF;
}