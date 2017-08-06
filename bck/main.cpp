/*
 * File:   main.cpp
 * Author: Alex
 *
 * Created on 28 novembre 2015, 15.44
 */

#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <time.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/assign/list_of.hpp> // for 'list_of()'

#include "database.h"
#include "preaggtable.h"
#include "simplelog.h"
#include "global.h"

using namespace boost::assign; // bring 'list_of()' into scope

/*
 * Prototypes
 */
int parseArgs(int argc, char **argv);
void usage(const char *message);

/*
 *  Main
 */
int main(int argc, char **argv) {

  if((parseArgs(argc, argv) != 0) || (aggregationType == NULL) || (databaseFilename == NULL) || (kpiFeFilename == NULL) || (logFilename == NULL)) {
    usage("etlv2 [-t table name] [-a aggregation type: m(onth)|w(eek)|d(ay)] [-l log file name] [-d database file name] [-o output file] [-m YYYY-MM-DD]\n");
    return EXIT_FAILURE;
  }
  LOGINIT(logFilename, MAX_LOG_SIZE, MAX_NUM_LOG, (_LOG_DEBUG | _LOG_INFO | _LOG_WARNING | _LOG_ERROR));
  //LOGINIT(logFilename, MAX_LOG_SIZE, MAX_NUM_LOG, (_LOG_INFO | _LOG_WARNING | _LOG_ERROR));
  LOGWRITE(NULL, (_LOG_INFO, "table name:         %s", tableName));
  LOGWRITE(NULL, (_LOG_INFO, "aggregation type:   %s", aggregationType));
  LOGWRITE(NULL, (_LOG_INFO, "database file name: %s", databaseFilename));
  LOGWRITE(NULL, (_LOG_INFO, "kpi fe file name:   %s", kpiFeFilename));
  LOGWRITE(NULL, (_LOG_INFO, "dday:               %s", dateRef));

  if (strcasecmp(aggregationType,"M") && strcasecmp(aggregationType,"W") && strcasecmp(aggregationType,"D")) {
    LOGWRITE(NULL, (_LOG_ERROR, "Wrong aggregation type <%s>. Exiting.", aggregationType));
    return EXIT_FAILURE;
  } // if

  if(DataBase::instance()->openDatabase(databaseFilename) == -1) {
    LOGWRITE(NULL, (_LOG_ERROR, "Error while opening database %s. Exiting.", databaseFilename));
    return EXIT_FAILURE;
  } // if

  PreaggTable().generateCSV();

  // all done.. exiting
  DataBase::instance()->closeDatabase();
  LOGWRITE(NULL, (_LOG_INFO, "All done. Exiting."));

  return EXIT_SUCCESS;
}

int parseArgs(int argc, char **argv) {
  int c;
  while((c = getopt(argc, argv, "t:a:l:d:o:m:")) != -1) {
    switch(c) {
    case 't':
        tableName = optarg;
        break;
    case 'a':
      aggregationType = optarg;
      break;
    case 'l':
      logFilename = optarg;
      break;
    case 'd':
      databaseFilename = optarg;
      break;
    case 'o':
      kpiFeFilename = optarg;
      break;
    case 'm':
      dateRef = optarg;
      break;
    case '?':
      if((optopt == 't') || (optopt == 'a') || (optopt == 'l') || (optopt == 'd') || (optopt == 'o')) {
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      } else if(isprint(optopt)) {
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      } else {
        fprintf(stderr,
                "Unknown option character `\\x%x'.\n",
                optopt);
      }
      return 1;
    default:
      abort();
    }
  }
  opterr = 0;
  return 0;
}

void usage(const char *message) {
  fprintf(stderr, "usage: %s", message);
}
