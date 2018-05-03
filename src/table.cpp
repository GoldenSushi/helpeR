#include "table.hpp"

Table::Table() : m_rowNum(0), m_colNum(0), m_maxStrSize(0) {}

Table::~Table() {}

void Table::setRowNum(int const &num) {
	m_rowNum = num;
}

void Table::setColNum(int const &num) {
	m_colNum = num;
	m_table.resize(m_colNum);
}

int Table::getRowNum() {
	return m_rowNum;
}

int Table::getColNum() {
	return m_table.size();
}

void Table::createDataFrame() {
  for (COLCOUNTER it = m_table.begin(); it != m_table.end(); ++it) {
    m_frame.push_back(*it);
  }
}

void Table::setStringSize (string &str) {
	if (str.size() > m_maxStrSize)
	  m_maxStrSize = str.size();
}

bool Table::checkQuot(string::iterator &it) {
	if (*it == '\"') {
		return true;
	}
	return false;
}

string::iterator Table::checkNext(string::iterator it) {
	return ++it;
}

vector<string> Table::fieldMaker(string &str) {
	
	string field = "";
  vector<string> v_fields;
  string::iterator it = str.begin();
  
  for (it; it != str.end(); ++it) {
    
    if (*it == ',') {
      v_fields.push_back(field);
      field = "";
      ++it;
    }
    
    if (!checkQuot(it))
      field += *it;
    //if quotes occur twice replace it by whitespace
    else 
      if(*(checkNext(it)) == '\"')
        field += " ";
  }
  
  if (field.size() != 0)
    v_fields.push_back(field);	
	
	return v_fields;
}

void Table::makeTable(std::ifstream &input) {

    string line;
    getline(input, line);
    vector<string> vec = fieldMaker(line);
    input.seekg(0, std::ios::beg);
    int col_num = vec.size();
    int i = 0;
    setColNum(col_num);
    
    while (getline(input, line, ',')) {
		  m_table[i%col_num].push_back(line);
      
      //eliminates line break:
      if ((i+2)%col_num == 0){
        getline(input, line, '\n');
        m_table[(i+1)%col_num].push_back(line);
        ++i;
      }
		  ++i;
	}
}

Rcpp::DataFrame Table::extractTable() {
	return m_frame;
}

vector<string> Table::extractHead() {
	vector<string> head;
	
	for (int i = 0; i < m_table.size(); ++i) {
	  head.push_back(m_table[i][0]);
	  m_table[i].erase(m_table[i].begin());
	}
	
	return head;	
}

void Table::printTable() {
	
	for (int i = 0; i < m_table[0].size(); ++i) {
	  for (int j = 0; j < m_table.size(); ++j) {
	    Rcpp::Rcout << m_table[j][i] << " ";
	  }
	  Rcpp::Rcout << std::endl;
	}
}

