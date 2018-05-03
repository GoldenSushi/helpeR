#include <Rcpp.h>
#include "table.hpp"

//'@title C Read
//'
//'@description Custom csv parser built using c++. For now it's just a test, and it is a little slower than R's read.csv, but in the future will have other custom utils
//'@param fileName name of the file or path leading to it.
//'@param header Indicates if the header is included in the file.
//'@export
// [[Rcpp::export]]
Rcpp::DataFrame cread_csv (std::string &fileName, bool header) {
  
  
  std::ifstream file(fileName.c_str(), std::ios::in);
  if (!file) {
    Rcpp::Rcout << "File not found." << endl;
    return NULL;
  }
  
  Table tab;
  tab.makeTable(file);
  std::vector<std::string> head;
  
  if (header)
    head = tab.extractHead();
  
  tab.createDataFrame();
  Rcpp::DataFrame table = tab.extractTable();
  table.attr("names") = Rcpp::wrap(head);
  
  return table;
}

