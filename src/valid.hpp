#ifndef VALIDATION_H
#define VALIDATION_H

#include <Rcpp.h>
#include <string>
#include <iostream>

#define IF_X_IN_RANGE ((predic_x[i] >= (valid_x[j] - 2) && predic_x[i] <= (valid_x[j] + 2)))
#define IF_Y_IN_RANGE ((predic_y[i] >= (valid_y[j] - 2) && predic_y[i] <= (valid_y[j] + 2)))
#define IF_XY_NOTNULL (valid_x.size() != 0 && valid_y.size() != 0)

class Validation {

	private:
	  Rcpp::DataFrame m_valid;
	  Rcpp::DataFrame m_predic;
	  
	  //indexes
		int predic_x_i;
		int predic_y_i;
		int valid_x_i;
		int valid_y_i;
		int pred_col_i;
		int valid_col_i;
		
		//coordinate columns
		Rcpp::NumericVector predic_x;
		Rcpp::NumericVector predic_y;
		Rcpp::NumericVector valid_x;
		Rcpp::NumericVector valid_y;
		
		//Prediction and validation columns to test against
		Rcpp::StringVector pred_col;
		Rcpp::StringVector valid_col;

		//results
		Rcpp::NumericVector match_xcoord;
		Rcpp::NumericVector match_ycoord;
		Rcpp::StringVector predicted_result;
		Rcpp::StringVector expected_result;

		void search_coord(Rcpp::DataFrame &, int &, int&);
		void search_predic(Rcpp::DataFrame &, int &);
		void search_valid(Rcpp::DataFrame &, int &); 
		void testXY(int &, int &);
		void testPred(int &);
		void testValid(int &);

	public:
	Validation(Rcpp::DataFrame, Rcpp::DataFrame);
	~Validation();
	void make();
	Rcpp::DataFrame makeValid(void);

};

#endif //VALIDATION_H
