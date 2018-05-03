#ifndef TABLE_HPP
#define TABLE_HPP

#define COLUMNS vector<string>
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

#include <iomanip>
using std::setw;
using std::left;

class Table {
	
	private:
	
		vector<COLUMNS> m_table;
	  Rcpp::DataFrame m_frame;
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
		~Table();
		int getRowNum(void);
		int getColNum(void);
		void makeTable(std::ifstream &);
		void createDataFrame(void);
		vector<string> extractHead(void);
		Rcpp::DataFrame extractTable(void);
		void printTable();
		
};

#endif //TABLE_HPP
