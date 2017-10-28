#include <iostream>

#include "listLib.h"
#include "eventLib.h"
#include "dbLib.h"

using namespace std;


/// This function displays the content of database
void display(L1List<NinjaInfo_t>& nList) {
      cout.flush();
      nList.traverse(printNinjaInfo);
}

int main(int narg, char** argv) {
      time_t               first = time(NULL);
      L1List<ninjaEvent_t> eventList;
      L1List<NinjaInfo_t>  db;    // database of NinjaInfo
      loadEvents(argv[1], eventList);
      loadNinjaDB(argv[2], db);

      cout << fixed << setprecision(12);    // preset for floating point numbers
      /// Process events
      process(eventList, db);

      cout << resetiosflags(ios::showbase) << setprecision(-1);

      time_t last     = time(NULL);
      double timespan = difftime(last, first);
      int    minutes  = timespan / 60;
      int    seconds  = timespan - 60 * minutes;
      cout << "Time elapsed: " << minutes << " minutes and " << seconds
           << " seconds" << endl;
      return 0;
}