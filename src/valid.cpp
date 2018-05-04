#include "valid.hpp"

Validation::Validation(Rcpp::DataFrame valid, Rcpp::DataFrame predic)
: predic_x_i(-1), predic_y_i(-1), valid_x_i(-1), valid_y_i(-1), pred_col_i(-1),
  valid_col_i(-1), m_valid(valid), m_predic(predic) {}

Validation::~Validation(){}

void Validation::search_coord(Rcpp::DataFrame &df, int &x, int &y) {
  
	try {
		x = df.findName("X");
	} catch (std::exception &e) {}
	try {
		x = df.findName("x");
	} catch (std::exception &e) {}
	try {
		y = df.findName("Y");
	} catch (std::exception &e) {}
	try {
		y = df.findName("y");
	} catch (std::exception &e) {}

}

void Validation::search_predic(Rcpp::DataFrame &df, int &pr_col) {
  
  try {
    pr_col = df.findName("Prediction");
  } catch (std::exception &e) {}
  
}

void Validation::search_valid(Rcpp::DataFrame &df, int &vld_col) {
  
  try {
    vld_col = df.findName("Validation");
  } catch (std::exception &e) {}
  
}

void Validation::testXY(int &x, int &y) {

	if (x == -1){
		Rcpp::stop("No column named X was found\n");
	}
	if (y == -1){
		Rcpp::stop("No column named Y was found\n");
	}

}

void Validation::testPred(int &pred_col) {
	if (pred_col == -1){
		Rcpp::stop("No column named Prediction was found\n");
	}
}

void Validation::testValid(int &valid_col) {
  if (valid_col == -1){
    Rcpp::stop("No column named Validation was found\n");
  }
}

void Validation::make() {
  
  
  //TODO correct search_ and test functions!
  //search
  search_coord(m_predic, predic_x_i, predic_y_i);
  search_coord(m_valid, valid_x_i, valid_y_i);
  search_predic(m_predic, pred_col_i);
  search_valid(m_valid, valid_col_i);
  
  //test
  testXY(predic_x_i, predic_y_i);
  testXY(valid_x_i, valid_y_i);
  testPred(pred_col_i);
  testValid(valid_col_i);
  
  //assign
  predic_x = m_predic[predic_x_i];
  predic_y = m_predic[predic_y_i];
  valid_x = m_valid[valid_x_i];
  valid_y = m_valid[valid_y_i];
  pred_col = m_predic[pred_col_i];
  valid_col = m_valid[valid_col_i];
  
}

Rcpp::DataFrame Validation::makeValid() {

	for (int i = 0; i < predic_x.size(); ++i) {
	for (int j = 0; j < valid_x.size(); ++j){
			if (IF_X_IN_RANGE && IF_Y_IN_RANGE) {
				match_xcoord.push_back(predic_x[i]);
				match_ycoord.push_back(predic_y[i]);
				expected_result.push_back(valid_col[j]);
				predicted_result.push_back(pred_col[i]);
				
				valid_x.erase(valid_x.begin() + j);
				valid_y.erase(valid_y.begin() + j);
				valid_col.erase(valid_col.begin() + j);
			}
		}
	}
	 
	Rcpp::DataFrame result = Rcpp::DataFrame::create(Rcpp::Named("X") = match_xcoord,
                                              Rcpp::Named("Y") = match_ycoord,
                                              Rcpp::Named("Expected") = expected_result,
                                              Rcpp::Named("Predicted") = predicted_result);
	return result;

}




