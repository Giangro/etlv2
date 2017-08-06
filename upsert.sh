#!/bin/bash

#
# Configuration
#
PREFIX_DIR=/home/hadoop
PSQL_PATH=/usr/phoenix/phoenix-4.6.0-HBase-1.1-bin/bin
CSV_FILES_PATH=$PREFIX_DIR/dev/etlv2/kpi_cruscotto/
OUTPUT_FILE=kpi_fe_unico_preagg.csv

#
# Main procedure
#

$PSQL_PATH/psql.py -d';' -t'KPI_FE_UNICO_STORICO_PREAGG_2_0' localhost:2181:/hbase-unsecure $CSV_FILES_PATH/$OUTPUT_FILE
