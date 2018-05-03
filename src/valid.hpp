#ifndef VALIDATION_H
#define VALIDATION_H

#include <Rcpp.h>
#include <string>
#include <iostream>

#define IF_X_IN_RANGE ((predic_x[i] >= (valid_x[j] - 1) && predic_x[i] <= (valid_x[j] + 1)))
#define IF_Y_IN_RANGE ((predic_y[i] >= (valid_y[j] - 1) && predic_y[i] <= (valid_y[j] + 1)))

class Validation {

	private:
	  Rcpp::DataFrame m_valid;
	  Rcpp::DataFrame m_predic;
	  
		int predic_x_i;
		int predic_y_i;
		int valid_x_i;
		int valid_y_i;
		int pred_col_i;
		Rcpp::NumericVector predic_x;
		Rcpp::NumericVector predic_y;
		Rcpp::NumericVector valid_x;
		Rcpp::NumericVector valid_y;
		Rcpp::StringVector pred_col;

		Rcpp::NumericVector match_xcoord;
		Rcpp::NumericVector match_ycoord;
		Rcpp::StringVector match_col;

		inline void search_coord(Rcpp::DataFrame &, int &, int&);
		inline void search_predic();
		inline void testXY(int &, int &);
		inline void testPred();

	public:
	Validation(Rcpp::DataFrame, Rcpp::DataFrame);
	~Validation();
	void make();
	Rcpp::DataFrame makeValid(void);

};

#endif //VALIDATION_H
