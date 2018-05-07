#ifndef TABLE_HPP
#define TABLE_HPP

#define COLUMNS vector<string>
#define DFCOL Rcpp::NumericVector
#define COLCOUNTER vector<COLUMNS>::iterator
#define ROWCOUNTER COLUMNS::iterator


#include <cassert>
#include <fstream>
#include <Rcpp.h>

#include <string>
using std::getline;
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

class Table {
	

	
	private:
	
	  //used to build dataframes from input stram
		vector<COLUMNS> m_table;
	  //used to extract columns from dataframes
	   Rcpp::List m_vectable;
	  
	  //stored frame either from input or from constructor
	  Rcpp::DataFrame m_frame;
	  //result after using cutTable
	  Rcpp::DataFrame m_cutframe;
	  
	  //used to store the column with predictions when needed
	  Rcpp::StringVector predictionCol;
	  
		int m_colNum;
		int m_rowNum;
		
		//used to format print function
		int m_maxStrSize;
		
		inline void setColNum(int const &);
		inline void setRowNum(int const &);
		inline bool insertColumn(int const &, vector<string> const &);
		inline void setStringSize (string &);
		
		inline bool checkQuot(string::iterator &);
		inline string::iterator checkNext(string::iterator);
		inline vector<string> fieldMaker(string &);
		
	public:
		Table();
	  Table(Rcpp::DataFrame);
		~Table();
		int getRowNum(void);
		int getColNum(void);
		//used to build table from input
		void makeTable(std::ifstream &);
		//used to build table from dataframe
		void makeTable();
		Rcpp::DataFrame cutFromTable(string &);
		void createDataFrame(void);
		vector<string> extractHead(void);
		Rcpp::DataFrame extractTable(void);
		void printTable(void);
		
};

#endif //TABLE_HPP
