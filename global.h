/*
 * File:   global.h
 * Author: Alex
 *
 * Created on 08 marzo 2016, 11.27
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <string>
#include <vector>

using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace std;

/*
 * Defines
 */

#define LOG_FILE_NAME "etl.log"
#define DATABASE_FILE_NAME "kpi_fe_unico_storico.db"
#define KPI_FE_FILE_NAME "kpi_fe_unico_storico_preagg.out"
#define AGGREGATION_TYPE "M"
#define TABLE_NAME "KPI_FE_CRUSCOTTO"
#define DEFAULT_DATE "1970-01-01"
#define MAX_LOG_SIZE 25000000
#define MAX_NUM_LOG 5

/*
 * User types
 */
// http://www.boost.org/doc/libs/1_60_0/doc/html/date_time/examples.html#date_time.examples.local_utc_conversion
// This local adjustor depends on the machine TZ settings-- highly dangerous!
typedef boost::date_time::c_local_adjustor < boost::posix_time::ptime > local_adj;

/*
 *  Global Vars
 */
extern const char *logFilename;
extern const char *databaseFilename;
extern const char *kpiFeFilename;
extern const char *aggregationType;
extern const char *tableName;
extern const char *dateRef;

/*
 * CSV Column for KPI
 */
const char csv_column[][32] = {
  "COMBO"
  ,"ATYPE"
  ,"DATA"
  ,"MD5SUM"
  ,"POLO"
  ,"SILOS"
  ,"ISOLA"
  ,"REGIONE"
  ,"DOMINIO"
  ,"NETWORK"
  ,"FAMIGLIA"
  ,"PIATTAFORMA"
  ,"VENDOR"
  ,"SLOGAN"
  ,"SEVERITY"
  ,"GRAYLIST"
  ,"PICCOLI_ALLARMI"
  ,"CORR_INTERD"
  ,"ACK"
  ,"ACKTT"
  ,"ACKP"
  ,"CORR"
  ,"PSISTEMA"
  ,"OUT"
  ,"NGN"
  ,"NGNMIN60"
  ,"NGNMAG60"
  ,"VAI"
  ,"VAP"
  ,"VAG"
  ,"VNTT"
  ,"VCTT"
  ,"DA"
  ,"IGA"
  ,"NTTTOT"
  ,"NTTRR"
  ,"NTTGEN"
  ,"NTTDISP"
  ,"NTTDISPWR"
  ,"NTTCORR"
  ,"NTTTRASF"
  ,"NTTT1SLA"
  ,"NTTT2SLA"
  ,"NTTRRR"
  ,"NTTRISCR"
  ,"DTI"
  ,"AZIONE"
  ,"CAUSALE"
  ,"CTTRR"
  ,"CTTTOT"
  ,"CTTCORR"
  ,"CTTDISP"
  ,"CTTDISPWR"
  ,"CTTT1SLA"
  ,"CTTT2SLA"
  ,"CTTSO"
  ,"CTTTRASF"
  ,"CTTRRR"
  ,"CTTRISCR"
  ,"LATENZA"
 };

/*
 * Combo Column
 */
 const char combo_column[][32] = {
     //"DATA","POLO", "SILOS", "ISOLA", "REGIONE", "DOMINIO", "NETWORK", "FAMIGLIA", "PIATTAFORMA", "VENDOR", "CAUSALE", "AZIONE", "SEVERITY"
     "DATA","POLO", "SILOS", "ISOLA", "REGIONE", "DOMINIO", "NETWORK", "FAMIGLIA", "PIATTAFORMA", "VENDOR"
 };

/*
 * Formula for KPI
 */
 const char kpi_column[][256] = {
   "SUM(GRAYLIST) as GRAYLIST"
   ,"SUM(PICCOLI_ALLARMI) as PICCOLI_ALLARMI"
   ,"SUM(CORR_INTERD) as CORR_INTERD"
   ,"SUM(ACK) as ACK"
   ,"SUM(ACKTT)	as ACKTT"
   ,"SUM(ACKP) as	ACKP"
   ,"SUM(CORR) as CORR"
   ,"SUM(PSISTEMA) as	PSISTEMA"
   ,"SUM(OUT)	as OUT"
   ,"SUM(NGN)	as NGN"
   ,"SUM(NGNMIN60)	as	NGNMIN60"
   ,"SUM(NGNMAG60)	as	NGNMAG60"
   ,"SUM(VAI)	as VAI"
   ,"SUM(ACK+ACKTT+NGN+NGNMIN60+NGNMAG60+ACKP) as VAP"
   ,"SUM(ACK+ACKTT+ACKP) as VAG"
 };


/*
 *  Prototypes
 */
void formatDateTime(std::string const& format,boost::posix_time::ptime const& date_time,std::string& result);

#endif  /* GLOBAL_H */
