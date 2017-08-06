/*
 * File:   preaggtable.h
 * Author: Alex
 *
 * Created on 08 marzo 2016, 18.24
 */

#ifndef PREAGGTABLE_H
#define PREAGGTABLE_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace boost;
using namespace std;

class PreaggTable {

private:

  typedef vector<string> strvector;
  typedef int (PreaggTable::*fcb) (int argc, char **argv, char **azColName);

private:
  // vars
  strvector strVector;
  map<string, string> colMap;
  map<string, string> extraColMap;

private:
  static int callback (void *data, int argc, char **argv, char **azColName);
  int prepareData(int argc, char **argv, char **azColName);

public:
  int generateCSV();

private:
  int executeSql(const string &sql);

public:
  // constructor
  PreaggTable();

};

#endif	/* PREAGGTABLE_H */
