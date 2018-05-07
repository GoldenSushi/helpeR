#include "table.hpp"

Table::Table() : m_rowNum(0), m_colNum(0), m_maxStrSize(0) {}

Table::Table(Rcpp::DataFrame df) : m_frame(df), m_rowNum(0), m_colNum(0), m_maxStrSize(0) {}

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

void Table::makeTable() {
  
  int predcol_i = m_frame.findName("Prediction");
  predictionCol = Rcpp::as<Rcpp::StringVector>(m_frame[predcol_i]);
  m_frame.erase(m_frame.begin() + predcol_i);
  
  for (int i = 0; i < m_frame.size(); ++i) {
    m_vectable.push_back(m_frame[i]);
  }

  // //TODO put switch only at cut table. do list of vectors here instead
  // //use switch to put value into two different vectors
  // for (DFCOL it = m_frame.begin(); it != m_frame.end(); ++it) {
  //   m_veclist.push_back(*it);
  //   switch (TYPEOF(*it)) {
  //   case REALSXP : {
  //     Rcpp::NumericVector nvec;
  //     m_newframe.push_back(nvec);
  //     break;
  //   }
  //   case STRSXP : {
  //      Rcpp::StringVector strvec;
  //     m_newframe.push_back(strvec);
  //     break;
  //    }
  //   case INTSXP : {
  //     Rcpp::IntegerVector intvec;
  //     m_newframe.push_back(intvec);
  //     break;
  //   }
  //   default : Rcpp::stop("Unsupported type in dataframe");
  //   }
  // }
}

Rcpp::DataFrame Table::cutFromTable(string &str) {
  
  vector<int> match_i;
  for (int i = 0; i < predictionCol.size(); ++i) {
    if (Rcpp::as<string>(predictionCol[i]) == str) {
      match_i.push_back(i);
      }
    }
  
  
  Rcpp::DataFrame df;
  for (Rcpp::List::iterator it = m_vectable.begin(); it != m_vectable.end(); ++it) {
    Rcpp::NumericVector tmp_vec = *it;
    Rcpp::NumericVector new_col;
    for (int i = 0; i < match_i.size(); ++i) {
      int index = (match_i[i]);
      new_col.push_back(tmp_vec[index]);
    }
    df.push_back(new_col);
  }
  
  df.attr("names") = m_frame.attr("names");
  
  return df;

  // int pred_index = m_frame.findName("Prediction");
  // Rcpp::StringVector predictionCol = m_frame[pred_index];
  // for (int i = 0; i < predictionCol.size(); ++i) {
  //   if (Rcpp::as<string>(predictionCol[i]) == str){
  //     for (int j = 0; j < m_frame.size(); ++j) {
  //       switch (TYPEOF(m_frame[j])) {
  //       case REALSXP:{
  //         Rcpp::NumericVector from_nvec = m_frame[j];
  //         Rcpp::NumericVector to_nvec = m_newframe
  //       }
  //     }
  //   }
  // }
  // }
  // Rcpp::DataFrame df;
  // for (int i = 0; i < new_table.size(); ++i) {
  //   df[i] = new_table[i];
  // }
  // return df;
  // 
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

