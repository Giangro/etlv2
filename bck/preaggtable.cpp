/*
 * File:   preaggtable.cpp
 * Author: Alex
 *
 * Created on 08 marzo 2016, 18.35
 */

#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp> // for 'list_of()'
#include "preaggtable.h"
#include "database.h"
#include "md5sum.h"
#include "global.h"
#include "simplelog.h"

using namespace boost::assign; // bring 'list_of()' into scope

PreaggTable::PreaggTable() {}

int PreaggTable::executeSql(const string& sql) {
  return DataBase::instance()->executeSql(sql.c_str(), PreaggTable::callback, (void *) this);
}
int PreaggTable::generateCSV() {
  const size_t combo_column_size = sizeof (combo_column) / sizeof (combo_column[0]);
  const size_t kpi_column_size = sizeof (kpi_column) / sizeof (kpi_column[0]);
  const int combinazioni = 1 << combo_column_size;
  //const int combinazioni = pow(2, arraysize);

  LOGWRITE(NULL, (_LOG_INFO, "loading data..."));

  for (int i = 1; i < combinazioni; i++) {

      int combo = i;
      vector<string> groupby_vector;

      for (int j = 0; combo > 0; j++) {

          if ((combo % 2) == 1) {
              groupby_vector.push_back(combo_column[j]);
          } // if

          combo >>= 1;

      } // for

      string sqlselect;

      sqlselect.append("SELECT ");

      //        BOOST_FOREACH(string col, groupby_vector) {
      //            sqlselect
      //                .append (col)
      //                .append(",");
      //        }

      string colset;

      colset.append(groupby_vector[0]);

      for (int j = 1; j < groupby_vector.size(); j++)
          colset.append(",").append(groupby_vector[j]);

      sqlselect.append(colset).append(",");
      sqlselect.append(kpi_column[0]);

      for (int j = 1; j < kpi_column_size; j++)
          sqlselect.append(",").append(kpi_column[j]);

      sqlselect.append(" FROM ").append(tableName);
      sqlselect.append(" GROUP BY ").append(colset);

      //LOGWRITE(NULL, (_LOG_DEBUG, "binary combo(%d) = %d - selecting cols = %s",i,decimal_to_binary(i),colset.c_str()));

      //cout << "colset = " << colset << endl;
      //snprintf (line,sizeof(line),"binary combo(%d) = %d",i,decimal_to_binary(i));
      //LOGWRITE(NULL, (_LOG_DEBUG, line));

      //cout << "binary combo (" << i << ")" << "=" << decimal_to_binary(i) << endl;
      this->colMap.clear();
      this->colMap["COMBO"]=string(lexical_cast<std::string>(i));
      
      //LOGWRITE(NULL, (_LOG_DEBUG, "sql = %s ",sqlselect.c_str()));

      DataBase::instance()->executeSql(sqlselect.c_str(), PreaggTable::callback, (void *) this);

  } // for

  return 0;

}
int PreaggTable::prepareData(int argc, char **argv, char **azColName) {
  const size_t csv_column_size = sizeof(csv_column) / sizeof(csv_column[0]);
  int i;
  char md5sum[33];

  // se il campo DATA non è valorizzata stiamo aggregando per mese
  this->colMap.erase("DATA");

  //this->colMap["COMBO"] = "-1";
  //this->colMap["ATYPE"] = "-1";
  //this->colMap["DATA"] = "-1";
  //this->colMap["MD5SUM"] = "-1";
  //this->colMap["POLO"] = "-1";
  //this->colMap["SILOS"] = "-1";
  //this->colMap["ISOLA"] = "-1";
  //this->colMap["REGIONE"] = "-1";
  //this->colMap["DOMINIO"] = "-1";
  //this->colMap["NETWORK"] = "-1";
  //this->colMap["FAMIGLIA"] = "-1";
  //this->colMap["PIATTAFORMA"] = "-1";
  //this->colMap["VENDOR"] = "-1";
  //this->colMap["SLOGAN"] = "-1";
  //this->colMap["SEVERITY"] = "-1";
  this->colMap["GRAYLIST"] = "-1";
  this->colMap["PICCOLI_ALLARMI"] = "-1";
  this->colMap["CORR_INTERD"] = "-1";
  this->colMap["ACK"] = "-1";
  this->colMap["ACKTT"] = "-1";
  this->colMap["ACKTTP"] = "-1";
  this->colMap["CORR"] = "-1";
  this->colMap["PSISTEMA"] = "-1";
  this->colMap["OUT"] = "-1";
  this->colMap["NGN"] = "-1";
  this->colMap["NGNMIN60"] = "-1";
  this->colMap["NGNMAG60"] = "-1";
  this->colMap["VAI"] = "-1";
  this->colMap["VAP"] = "-1";
  this->colMap["VAG"] = "-1";
  this->colMap["VNTT"] = "-1";
  this->colMap["VCTT"] = "-1";
  this->colMap["DA"] = "-1";
  this->colMap["IGA"] = "-1";
  this->colMap["NTTTOT"] = "-1";
  this->colMap["NTTRR"] = "-1";
  this->colMap["NTTGEN"] = "-1";
  this->colMap["NTTDISP"] = "-1";
  this->colMap["NTTDISPWR"] = "-1";
  this->colMap["NTTCORR"] = "-1";
  this->colMap["NTTTRASF"] = "-1";
  this->colMap["NTTT1SLA"] = "-1";
  this->colMap["NTTT2SLA"] = "-1";
  this->colMap["NTTRRR"] = "-1";
  this->colMap["NTTRISCR"] = "-1";
  this->colMap["DTI"] = "-1";
  this->colMap["AZIONE"] = " ";  // varchar type
  this->colMap["CAUSALE"] = " "; // varchar type
  this->colMap["CTTRR"] = "-1";
  this->colMap["CTTTOT"] = "-1";
  this->colMap["CTTCORR"] = "-1";
  this->colMap["CTTDISP"] = "-1";
  this->colMap["CTTDISPWR"] = "-1";
  this->colMap["CTTT1SLA"] = "-1";
  this->colMap["CTTT2SLA"] = "-1";
  this->colMap["CTTSO"] = "-1";
  this->colMap["CTTTRASF"] = "-1";
  this->colMap["CTTRRR"] = "-1";
  this->colMap["CTTRISCR"] = "-1";
  this->colMap["LATENZA"] = "-1";
  for(i = 0; i < argc; i++) {
    string colname = azColName[i];
    to_upper(colname);
    this->colMap[colname] = argv[i];
  } // for

  /* For logging purpose
   * ===================
   * for (map<string,string>::iterator it = this->colMap.begin();it!=this->colMap.end();it++) {
   *    LOGWRITE(NULL, (_LOG_DEBUG, "%s = %s",it->first.c_str(),it->second.c_str()));
   *} // for
   */
  // PATCH: da gestire settimana
  // INIZIO
  if(this->colMap.find("DATA") == this->colMap.end()) {
    this->colMap["DATA"] = dateRef;
    this->colMap["ATYPE"] = 'M';
  } else {
    this->colMap["ATYPE"] = 'D';
  }
  // FINE

  string sum;
  if(this->colMap.find("POLO") != this->colMap.end()) {
    sum.append(this->colMap["POLO"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("SILOS") != this->colMap.end()) {
    sum.append(this->colMap["SILOS"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("ISOLA") != this->colMap.end()) {
    sum.append(this->colMap["ISOLA"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("REGIONE") != this->colMap.end()) {
    sum.append(this->colMap["REGIONE"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("DOMINIO") != this->colMap.end()) {
    sum.append(this->colMap["DOMINIO"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("NETWORK") != this->colMap.end()) {
    sum.append(this->colMap["NETWORK"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("FAMIGLIA") != this->colMap.end()) {
    sum.append(this->colMap["FAMIGLIA"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("PIATTAFORMA") != this->colMap.end()) {
    sum.append(this->colMap["PIATTAFORMA"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("VENDOR") != this->colMap.end()) {
    sum.append(this->colMap["VENDOR"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("SLOGAN") != this->colMap.end()) {
    sum.append(this->colMap["SLOGAN"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("CAUSALE") != this->colMap.end()) {
    sum.append(this->colMap["CAUSALE"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("AZIONE") != this->colMap.end()) {
    sum.append(this->colMap["AZIONE"]).append("|");
  } else {
    sum.append("*|");
  }
  if(this->colMap.find("SEVERITY") != this->colMap.end()) {
    sum.append(this->colMap["SEVERITY"]);
  } else {
    sum.append("*");
  }

  md5hash(sum.c_str(), md5sum);

  //LOGWRITE(NULL, (_LOG_DEBUG, "md5 sum of %s is %s", sum.c_str(), md5sum));

  this->colMap["MD5SUM"] = md5sum;
  string csvrow;
  if(this->colMap.find(csv_column[0]) != this->colMap.end()) {
    csvrow.append(this->colMap[csv_column[0]]);
  } else {
    csvrow.append(" ");
  }
  for(i=1; i < csv_column_size; i++) {
    csvrow.append(";");
    if(this->colMap.find(csv_column[i]) != this->colMap.end()) {
      csvrow.append(this->colMap[csv_column[i]]);
    } else {
      csvrow.append(" ");
    }
  }     // for

  //LOGWRITE(NULL, (_LOG_DEBUG, "row #%d = %s", ++nrow, csvrow.c_str()));
  cout << csvrow << endl;
  return 0;
}
int PreaggTable::callback(void *data, int argc, char **argv, char **azColName) {
  PreaggTable *self = static_cast<PreaggTable *>(data);
  if(self) {
    return self->prepareData(argc, argv, azColName);
  } else {
    return -1;
  }
}
