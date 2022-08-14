//
// Created by Havelund, Klaus (348B) on 3/29/21.
//

#ifndef LOGSCOPE_TEST8_H
#define LOGSCOPE_TEST8_H

#include "contract.h"
#include "../../src/engine/Binding.h"
#include <unordered_map>
#include "../../src/csv/csvparser.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace suite8 {

    void test1() {
        int i =  0;
        //                                   file, delimiter, first_line_is_header?
        CsvParser *csvparser = CsvParser_new("/Users/khavelun/Desktop/development/logscope/backend/test/suite8/test1.csv", ",", 0);
        CsvRow *row;

        auto start = high_resolution_clock::now();
        while ((row = CsvParser_getRow(csvparser)) ) {
            cout << "==NEW LINE==\n";
            const char **rowFields = CsvParser_getFields(row);
            for (i = 0 ; i < CsvParser_getNumFields(row) ; i++) {
                cout << "[" << rowFields[i] << "]";
            }
            cout << "\n";
            CsvParser_destroy_row(row);
        }
        CsvParser_destroy(csvparser);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time: " << duration.count() << " microseconds" << endl;
    }

    /*
log-1-12500.csv
log-50-250.csv

log-1-50000.csv
log-5-10000.csv
log-10-5000.csv
log-20-2500.csv

log-1-125000.csv
log-5-25000.csv
     */

    void test2() {
        SpecObject contract = makeContract();

        auto file = "/Users/khavelun/Desktop/development/logscope/backend/test/suite8/log-5-25000.csv";

        int i =  0;
        //                                   file, delimiter, first_line_is_header?
        CsvParser *csvparser = CsvParser_new(file, ",", 0);
        CsvRow *row;

        auto start = high_resolution_clock::now();
        while ((row = CsvParser_getRow(csvparser)) ) {
            const char **rowFields = CsvParser_getFields(row);
            // for (i = 0 ; i < CsvParser_getNumFields(row) ; i++) {
            //     cout << "[" << rowFields[i] << "]";
            // }
            // cout << "\n";
            if (contract.getEventCount() % 1000 == 0) cout << "--> " << contract.getEventCount() << "\n";
            Event e;
            if (strncmp(rowFields[0],"command",7) == 0) {
                e = Event(10, "command",
                          {
                                  {"cmd",  rowFields[1]},
                                  {"nr",   rowFields[2]},
                                  {"kind", rowFields[3]}
                               });
            } else {
                e = Event(10, rowFields[0],
                          {
                                  {"cmd",  rowFields[1]},
                                  {"nr",   rowFields[2]}});
            }
            contract.eval(e);
            CsvParser_destroy_row(row);
        }
        CsvParser_destroy(csvparser);
        contract.end();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Time: " << duration.count() << " milliseconds" << endl;
    }

    void test() {
        test2();
    }

}

#endif
