/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms
 * - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"


// return event code, char* as argument
int extractEvent(ninjaEvent_t&, char*&);

// problem set
void problem0(L1List<char*>&);
void problem1(L1List<NinjaInfo_t>&);
void problem2(L1List<NinjaInfo_t>&);
void problem3(L1List<char*>&);
void problem4(L1List<char*>&);
void problem5(L1List<NinjaInfo_t>&, char*&);
void problem6(L1List<NinjaInfo_t>&, char*&);
void problem7(L1List<NinjaInfo_t>&, char*&);
void problem8(L1List<NinjaInfo_t>&, L1List<char*>&, char*&);
void problem9(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem10(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem11(L1List<char*>&, char*&, L1List<char**>&);
void problem12(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem13(L1List<NinjaInfo_t>&, char*&);
void problem14(L1List<NinjaInfo_t>&, L1List<char*>&, L1List<char**>&, bool&);

// time from lhs, to rhs
double timeInterval(NinjaInfo_t& from, NinjaInfo_t& to) {
      return difftime(to.timestamp, from.timestamp);
}
// distance between lhs and rhs
double distance(NinjaInfo_t& lhs, NinjaInfo_t& rhs) {
      return distanceEarth(
         lhs.latitude, lhs.longitude, rhs.latitude, rhs.longitude);
}
// whether ninja stop between lhs and rhs
bool isStop(NinjaInfo_t& lhs, NinjaInfo_t& rhs) {
      return distance(lhs, rhs) * 1000 <= 5;
}

// total distance of a ninja
double  TotalDistance(L1List<NinjaInfo_t>&, const char*);
double  TotalTime(L1List<NinjaInfo_t>&, const char*);
double  ThinkingTime(L1List<NinjaInfo_t>&, const char*);
double* parseTrapPlace(const char*);
bool    isTrap(NinjaInfo_t&, double[4]);
bool    isLost(char*& ninja, L1List<NinjaInfo_t>& recordList);
int     isInList(L1List<char*>&, const char*);
int     isInList(L1List<char**>&, char**&);
void    removeNinja(L1List<char*>&, const char*);
void    removeNinja(L1List<char**>&, char**&);

// print the result
void print(char*&);
void print(const char*);
void print(const int&);
void print(const double&);
void print(L1List<char*>&);
void print(L1List<char**>&);
void print(time_t&);


//
// ─── MAIN PROCESS
// ───────────────────────────────────────────────────────────────
//


bool processEvent(
   ninjaEvent_t&        event,
   L1List<NinjaInfo_t>& nList,
   void*                pGData) {
      // TODO: Your code comes here
      void**          Data      = (void**) pGData;
      L1List<char*>*  allEvents = (L1List<char*>*) Data[0];
      L1List<char*>*  allNinjas = (L1List<char*>*) Data[1];
      L1List<char**>* event14   = (L1List<char**>*) Data[2];
      bool            allLost   = false;
      // allEvents by its order


      /// NOTE: The output of the event will be printed on one line
      /// end by the endline character.

      char* args = nullptr;
      int   code = extractEvent(event, args);

      if (code >= 0 && code <= 14 && code != 13)
            cout << code << args << ":";

      switch (code) {
            case 0:
                  problem0(*allEvents);
                  break;
            case 1:
                  problem1(nList);
                  break;
            case 2:
                  problem2(nList);
                  break;
            case 3:
                  problem3(*allNinjas);
                  break;
            case 4:
                  problem4(*allNinjas);
                  break;
            case 5:
                  problem5(nList, args);
                  break;
            case 6:
                  problem6(nList, args);
                  break;
            case 7:
                  problem7(nList, args);
                  break;
            case 8:
                  problem8(nList, *allNinjas, args);
                  break;
            case 9:
                  problem9(nList, *allNinjas);
                  break;
            case 10:
                  problem10(nList, *allNinjas);
                  break;
            case 11:
                  problem11(*allNinjas, args, *event14);
                  break;
            case 12:
                  problem12(nList, *allNinjas);
                  break;
            case 13:
                  return false;
                  break;
            case -13:
                  break;
            case 14:
                  problem14(nList, *allNinjas, *event14, allLost);
                  break;
            default:
                  delete[] args;
                  args = nullptr;
                  return false;
      }

      delete[] args;
      args = nullptr;
      /// NOTE: The output of the event will be printed on one line
      /// end by the endline character.
      return true;
}

//
// ─── EXTRACT EVENTS TO CODE AND ARGS
// ────────────────────────────────────────────
//


int extractEvent(ninjaEvent_t& Event, char*& args) {
      int codeLength = strlen(Event.code);

      // 13...
      if (Event.code[0] == '1' && Event.code[1] == '3' && Event.code[2] != '\0')
            return -13;

      switch (codeLength) {
            case 1:
                  args = new char[2];
                  strcpy(args, "");
                  return Event.code[0] - '0';

            case 2:
                  args = new char[2];
                  strcpy(args, "");
                  return 10 * (Event.code[0] - '0') + (Event.code[1] - '0');

            case 5:
                  args = new char[5];
                  for (int i = 0; i < 4; ++i)
                        args[i] = Event.code[i + 1];
                  args[4] = '\0';
                  return Event.code[0] - '0';

            case 6:
                  args = new char[5];
                  for (int i = 0; i < 4; ++i)
                        args[i] = Event.code[i + 2];
                  args[4] = '\0';
                  return 10 * (Event.code[0] - '0') + (Event.code[1] - '0');

            default:
                  return -1;
      }
}

//
// ────────────────────────────────────────────────────────────────────── I
//   :::::: S O L V I N G   P R O B L E M : :  :   :    :     :        : :
// ────────────────────────────────────────────────────────────────────────────────
//

void problem0(L1List<char*>& allEvents) {
      print(allEvents);
      cout << "\n";
}
void problem1(L1List<NinjaInfo_t>& recordList) {
      if (recordList.isEmpty())
            print("empty");
      else
            print(recordList[0].id);
      cout << "\n";
}
void problem2(L1List<NinjaInfo_t>& recordList) {
      if (recordList.isEmpty())
            print("empty");
      else
            print(recordList[recordList.getSize() - 1].id);
      cout << "\n";
}
void problem3(L1List<char*>& ninjaList) {
      print((int) ninjaList.getSize());
      cout << "\n";
}
void problem4(L1List<char*>& ninjaList) {
      auto findMaxId = [](char*& ninja, void* v) {
            char** maxId = (char**) v;
            if (*maxId == nullptr) {
                  *maxId = ninja;
                  return;
            }
            if (strcmp(ninja, *maxId) > 0)
                  *maxId = ninja;
      };

      if (ninjaList.isEmpty()) {
            print("empty");
            cout << "\n";
            return;
      }

      char** maxId = new char*();
      ninjaList.traverse(findMaxId, maxId);

      if (*maxId)
            print(*maxId);
      else
            print("empty");
      cout << "\n";
      delete maxId;
      maxId = nullptr;
}
void problem5(L1List<NinjaInfo_t>& recordList, char*& ninja) {
      struct Ans
      {
            char**       ninja;
            time_t       ret;
            NinjaInfo_t* lastpoint;
            NinjaInfo_t* laststop;
            bool         first;
            bool         stop;

            Ans(char* n) {
                  ninja     = &n;
                  lastpoint = nullptr;
                  laststop  = nullptr;
                  first     = true;
                  stop      = false;
                  ret       = 0;
            }

            ~Ans() {
                  ninja     = nullptr;
                  lastpoint = nullptr;
                  laststop  = nullptr;
            }
      };


      auto findFirstMove = [](NinjaInfo_t& ninjaRecord, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(*ans->ninja, ninjaRecord.id) != 0)
                  return;

            if (ans->first) {
                  ans->first = false;
            }
            else if (!ans->stop) {
                  if (!isStop(*ans->lastpoint, ninjaRecord)) {
                        ans->ret = ans->lastpoint->timestamp;
                        throw true;
                  }
                  else {
                        ans->laststop = ans->lastpoint;
                        ans->stop     = true;
                  }
            }
            else {
                  if (!isStop(*ans->laststop, ninjaRecord)) {
                        ans->ret = ninjaRecord.timestamp;
                        throw true;
                  }
            }

            ans->lastpoint = &ninjaRecord;
      };


      Ans ans(ninja);
      try {
            recordList.traverse(findFirstMove, &ans);
      } catch (bool b) {
            print(ans.ret);
            cout << "\n";
            return;
      }

      print(-1);
      cout << "\n";
}
void problem6(L1List<NinjaInfo_t>& recordList, char*& ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* lastStopPlace;
            char**       ninja;
            bool         first;
            bool         stop;

            Ans(char* n) {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
                  ninja         = &n;
                  first         = true;
                  stop          = false;
            }
            ~Ans() {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
                  ninja         = nullptr;
            }
      };

      auto findLastStopTime = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;
            if (strcmp(*ans->ninja, info.id) != 0)
                  return;

            if (ans->first) {
                  ans->first = false;
            }

            else if (!ans->stop) {
                  if (isStop(*ans->lastPlace, info)) {
                        ans->lastStopPlace = ans->lastPlace;
                        ans->stop          = true;
                  }
            }

            else {
                  if (!isStop(*ans->lastStopPlace, info)) {
                        ans->stop = false;
                  }
            }

            ans->lastPlace = &info;
      };

      Ans ans(ninja);
      recordList.traverse(findLastStopTime, &ans);

      if (ans.first)
            print(-1);
      else
            print(ans.lastStopPlace->timestamp);

      cout << "\n";
}
void problem7(L1List<NinjaInfo_t>& recordList, char*& ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* stopPlace;
            char**       ninja;
            int          timeStop;
            bool         first;
            bool         stop;

            Ans(char* n) {
                  lastPlace = nullptr;
                  stopPlace = nullptr;
                  ninja     = &n;
                  timeStop  = 0;
                  first     = true;
                  stop      = false;
            }
            ~Ans() {
                  lastPlace = nullptr;
                  stopPlace = nullptr;
                  ninja     = nullptr;
            }
      };

      auto findTimeStop = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;
            if (strcmp(*ans->ninja, info.id) != 0)
                  return;

            if (ans->first) {
                  ans->first = false;
            }

            else if (!ans->stop) {
                  if (isStop(*ans->lastPlace, info)) {
                        ans->stopPlace = ans->lastPlace;
                        ans->stop      = true;
                        ans->timeStop++;
                  }
            }

            else {
                  if (!isStop(*ans->stopPlace, info)) {
                        ans->stop = false;
                  }
            }

            ans->lastPlace = &info;
      };

      Ans ans(ninja);
      recordList.traverse(findTimeStop, &ans);

      if (ans.first)
            print(-1);
      else
            print(ans.timeStop);

      cout << "\n";
}
void problem8(
   L1List<NinjaInfo_t>& recordList,
   L1List<char*>&       allNinjas,
   char*&               ninja) {
      if (!isInList(allNinjas, ninja)) {
            print(-1);
            return;
      }
      double distance = TotalDistance(recordList, ninja);
      print(distance);
      cout << "\n";
}
void problem9(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {
      struct Ans
      {
            L1List<NinjaInfo_t>& recordList;
            double               maxDistance;
            char**               ninja;

            Ans(L1List<NinjaInfo_t>& l) : recordList(l) {
                  maxDistance = 0;
                  ninja       = nullptr;
            }

            ~Ans() {
                  ninja = nullptr;
            }
      };

      auto findDistanceMax = [](char*& ninja, void* v) {
            Ans*   ans          = (Ans*) v;
            double maxThisNinja = TotalDistance(ans->recordList, ninja);

            if (ans->maxDistance >= maxThisNinja)
                  return;

            ans->maxDistance = maxThisNinja;
            ans->ninja       = &ninja;
      };

      if (ninjaList.isEmpty()) {
            print(-1);
            cout << "\n";
            return;
      }

      Ans ans(recordList);
      ninjaList.traverse(findDistanceMax, &ans);

      print(*ans.ninja);
      cout << "\n";
}
void problem10(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {
      struct Ans
      {
            L1List<NinjaInfo_t>& recordList;
            double               maxTime;
            char**               ninja;

            Ans(L1List<NinjaInfo_t>& l) : recordList(l) {
                  maxTime = 0;
                  ninja   = new char*();
            }

            ~Ans() {
                  delete ninja;
                  ninja = nullptr;
            }
      };

      auto findDistanceMax = [](char*& ninja, void* v) {
            Ans*   ans          = (Ans*) v;
            double maxThisNinja = TotalTime(ans->recordList, ninja);

            //  cout << ninja << ": " << maxThisNinja << "\n";

            if (ans->maxTime >= maxThisNinja)
                  return;

            ans->maxTime = maxThisNinja;
            *ans->ninja  = ninja;
      };

      if (ninjaList.isEmpty()) {
            print(-1);
            cout << "\n";
            return;
      }

      Ans ans(recordList);
      ninjaList.traverse(findDistanceMax, &ans);

      print(*ans.ninja);
      cout << "\n";
}
void problem11(
   L1List<char*>&  ninjaList,
   char*&          ninja,
   L1List<char**>& event14) {
      struct Ans
      {
            char**       attackedNinja;
            const char** fakeNinja;

            Ans(const char* f) {
                  fakeNinja     = &f;
                  attackedNinja = nullptr;
            }
            ~Ans() {
                  attackedNinja = nullptr;
                  fakeNinja     = nullptr;
            }
      };

      auto findAttackedNinja = [](char*& thisNinja, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(*ans->fakeNinja, thisNinja) > 0) {
                  if (ans->attackedNinja == nullptr)
                        ans->attackedNinja = &thisNinja;
                  else if (strcmp(*ans->attackedNinja, thisNinja) < 0)
                        ans->attackedNinja = &thisNinja;
            }
      };

      if (ninjaList.isEmpty()) {
            print(-1);
            cout << "\n";
            return;
      }

      Ans ans(ninja);
      ninjaList.traverse(findAttackedNinja, &ans);

      if (ans.attackedNinja == nullptr)
            print(-1);
      else {
            print(*ans.attackedNinja);
            removeNinja(ninjaList, *ans.attackedNinja);
            if (!event14.isEmpty())
                  removeNinja(event14, ans.attackedNinja);
      }
      cout << "\n";
}
void problem12(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {
      struct Ans
      {
            L1List<NinjaInfo_t>& recordList;
            double               maxTime;
            char**               ninja;

            Ans(L1List<NinjaInfo_t>& l) : recordList(l) {
                  maxTime = 0;
                  ninja   = new char*();
            }

            ~Ans() {
                  delete ninja;
                  ninja = nullptr;
            }
      };

      auto findDistanceMax = [](char*& ninja, void* v) {
            Ans*   ans          = (Ans*) v;
            double maxThisNinja = ThinkingTime(ans->recordList, ninja);

            if (ans->maxTime >= maxThisNinja)
                  return;

            ans->maxTime = maxThisNinja;
            *ans->ninja  = ninja;
      };

      if (ninjaList.isEmpty()) {
            print(-1);
            cout << "\n";
            return;
      }

      Ans ans(recordList);
      ninjaList.traverse(findDistanceMax, &ans);

      print(*ans.ninja);
      cout << "\n";
}
void problem13(L1List<NinjaInfo_t>& recordList, char*& trap) {
      struct Ans
      {
            double*        trapPlace;
            L1List<char*>* trapList;

            Ans(double* trap) {
                  trapPlace = trap;
                  trapList  = new L1List<char*>();
            }

            ~Ans() {
                  trapPlace = nullptr;
                  delete trapList;
            }
      };


      auto TrapNinjaList = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (!isTrap(info, ans->trapPlace))
                  return;

            if (isInList(*ans->trapList, info.id) != -1)
                  return;

            char* id = new char[ID_MAX_LENGTH];
            strcpy(id, info.id);
            ans->trapList->insertHead(id);
      };

      double* trapPlace = parseTrapPlace(trap);

      Ans* ans = new Ans(trapPlace);
      recordList.traverse(TrapNinjaList, ans);

      if (ans->trapList->isEmpty())
            print(-1);
      else
            print(*ans->trapList);

      cout << "\n";
}
void problem14(
   L1List<NinjaInfo_t>& recordList,
   L1List<char*>&       ninjaList,
   L1List<char**>&      event14,
   bool&                allLost) {

      struct Ans
      {
            L1List<char**>*      list;
            L1List<NinjaInfo_t>* recordList;

            ~Ans() {
                  list       = nullptr;
                  recordList = nullptr;
            }
      };

      auto getlostlist = [](char*& ninja, void* v) {
            Ans* ans = (Ans*) v;
            if (!isLost(ninja, *ans->recordList))
                  return;

            char** ninja_address = &ninja;
            ans->list->insertHead(ninja_address);
      };

      if (ninjaList.isEmpty()) {
            print(-1);
            cout << "\n";
            return;
      }

      if (event14.isEmpty() && !allLost) {
            Ans ans;
            ans.list       = &event14;
            ans.recordList = &recordList;

            ninjaList.traverse(getlostlist, &ans);
            ans.list->reverse();

            if (ans.list->isEmpty())
                  allLost = true;
      }

      if (event14.isEmpty())
            print(-1);
      else
            print(event14);
      cout << "\n";
}


//
// ──────────────────────────────────────────────────────────────────────── II
//   :::::: N I N J A   A T T R I B U T E S : :  :   :    :     :        : :
// ──────────────────────────────────────────────────────────────────────────────────
//


double TotalDistance(L1List<NinjaInfo_t>& recordList, const char* ninja) {

      struct Ans
      {
            NinjaInfo_t* lastStop;
            const char** ninja;
            double       distance;
            bool         first;

            Ans(const char* c) {
                  lastStop = nullptr;
                  ninja    = &c;
                  distance = 0;
                  first    = true;
            }
      };

      auto findDistance = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(*ans->ninja, info.id) != 0)
                  return;

            if (ans->first) {
                  ans->first = false;
            }

            else {
                  // ans->distance += distance(ans->lastStop, info);
                  // cout << ans->distance << "\n";
                  //*
                  ans->distance += distanceEarth(
                     ans->lastStop->latitude,
                     ans->lastStop->longitude,
                     info.latitude,
                     info.longitude);
                  // */
            }
            ans->lastStop = &info;
      };

      Ans ans(ninja);
      recordList.traverse(findDistance, &ans);

      return ans.distance;
}
double TotalTime(L1List<NinjaInfo_t>& recordList, const char* ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* lastStopPlace;
            const char** ninja;
            double       ThinkingTime;
            time_t       firstTime;
            bool         first;
            bool         stop;

            Ans(const char* c) {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
                  ninja         = &c;
                  ThinkingTime  = 0;
                  firstTime     = 0;
                  first         = true;
                  stop          = false;
            }

            ~Ans() {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
                  ninja         = nullptr;
            }
      };

      auto findTotalTime = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(*ans->ninja, info.id) != 0)
                  return;

            if (ans->first) {
                  ans->first     = false;
                  ans->firstTime = info.timestamp;
            }

            else if (!ans->stop) {
                  if (isStop(*ans->lastPlace, info)) {
                        ans->lastStopPlace = ans->lastPlace;
                        ans->stop          = true;
                  }
            }

            else {
                  if (!isStop(*ans->lastStopPlace, info)) {
                        ans->stop = false;
                        ans->ThinkingTime +=
                           timeInterval(*ans->lastStopPlace, *ans->lastPlace);
                  }
            }

            ans->lastPlace = &info;
      };

      Ans ans(ninja);
      recordList.traverse(findTotalTime, &ans);

      // if he is still stop till end of time
      if (ans.stop) {
            ans.ThinkingTime +=
               timeInterval(*ans.lastStopPlace, *ans.lastPlace);
      }

      return difftime(ans.lastPlace->timestamp, ans.firstTime) -
             ans.ThinkingTime;
}
double ThinkingTime(L1List<NinjaInfo_t>& recordList, const char* ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* lastStopPlace;
            const char** ninja;
            double       time;
            bool         first;
            bool         stop;

            Ans(const char* c) {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
                  ninja         = &c;
                  time          = 0;
                  first         = true;
                  stop          = false;
            }

            ~Ans() {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
            }
      };

      auto findThinkingTime = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(*ans->ninja, info.id) != 0)
                  return;

            if (ans->first) {
                  ans->first = false;
            }

            else if (!ans->stop) {
                  if (isStop(*ans->lastPlace, info)) {
                        ans->lastStopPlace = ans->lastPlace;
                        ans->stop          = true;
                  }
            }

            else {
                  if (!isStop(*ans->lastStopPlace, info)) {
                        ans->stop = false;
                        ans->time +=
                           timeInterval(*ans->lastStopPlace, *ans->lastPlace);
                  }
            }

            ans->lastPlace = &info;
      };

      Ans ans(ninja);
      recordList.traverse(findThinkingTime, &ans);

      // if he is still stop till end of time
      if (ans.stop) {
            return ans.time + timeInterval(*ans.lastStopPlace, *ans.lastPlace);
      }
      return ans.time;
}

double* parseTrapPlace(const char* trap) {
      double latA = 0;
      double lonA = 0;
      double latB = 0;
      double lonB = 0;

      if (sscanf(trap, "%4lF%4lF%4lF%4lF", &latA, &lonA, &latB, &lonB) != 4) {
            exit(-3);
      }

      // cout << lonA << " " << latA << " " << lonB << " " << latB;

      latA /= 10000;
      lonA /= 10000;
      latB /= 10000;
      lonB /= 10000;
      double* ret = new double[4]{lonA, latA, lonB, latB};
      return ret;
}
bool isTrap(NinjaInfo_t& record, double* trapPlace) {

      auto sign = [](double d) -> int { return (d < 0) ? -1 : 1; };

      double lonN   = record.longitude;
      double latN   = record.latitude;
      double lonA   = trapPlace[0] * sign(lonN) + (int) record.longitude;
      double latA   = trapPlace[1] * sign(latN) + (int) record.latitude;
      double lonB   = trapPlace[2] * sign(lonN) + (int) record.longitude;
      double latB   = trapPlace[3] * sign(latN) + (int) record.latitude;
      bool   status = false;

      // A left lower --- B right upper
      bool scenario_1 =
         (lonA <= lonN && latA <= latN && lonB >= lonN && latB >= latN);

      // A left upper --- B right lower
      bool scenario_2 =
         (lonA <= lonN && latA >= latN && lonB >= lonN && latB <= latN);

      // A right upper --- B left lower
      bool scenario_3 =
         (lonA >= lonN && latA >= latN && lonB <= lonN && latB <= latN);

      // A right lower --- B left upper
      bool scenario_4 =
         (lonA >= lonN && latA <= latN && lonB <= lonN && latB >= latN);

      if (scenario_1 || scenario_2 || scenario_3 || scenario_4)
            status = true;


      return status;
}

// throw true on found loop
void findloop(L1List<NinjaInfo_t&>& list) {
      NinjaInfo_t* compare_point = &list.at(0);
      list.removeHead();

      auto getloopstatus = [](NinjaInfo_t& info, void* v) {
            NinjaInfo_t* compare_point = (NinjaInfo_t*) v;

            if (isStop(*compare_point, info)) {
                  compare_point = nullptr;
                  throw true;
            }
      };

      list.traverse(getloopstatus, compare_point);
}

bool isLost(char*& ninja, L1List<NinjaInfo_t>& recordList) {

      struct Ans
      {
            NinjaInfo_t*         laststop;
            NinjaInfo_t*         lastpoint;
            bool                 first = true;
            bool                 stop  = false;
            char**               ninja;
            L1List<NinjaInfo_t&> liststop;

            ~Ans() {
                  laststop  = nullptr;
                  lastpoint = nullptr;
                  ninja     = nullptr;
            }
      };

      auto getliststop = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;
            if (strcmp(info.id, *ans->ninja) != 0)
                  return;

            if (ans->first) {
                  ans->first = false;
            }
            else if (!ans->stop) {
                  if (isStop(*ans->lastpoint, info)) {
                        ans->laststop = ans->lastpoint;
                        ans->stop     = true;
                  }
                  ans->liststop.insertHead(*ans->lastpoint);
            }
            else {
                  if (!isStop(*ans->laststop, info)) {
                        ans->stop = false;
                  }
            }
            ans->lastpoint = &info;
      };

      Ans ans;
      ans.ninja = &ninja;

      recordList.traverse(getliststop, &ans);

      if (!ans.stop)
            ans.liststop.insertHead(*ans.lastpoint);

      while (!ans.liststop.isEmpty()) {
            try {
                  findloop(ans.liststop);
            } catch (bool b) {
                  return true;
            }
      }
      return false;
}


int isInList(L1List<char*>& ninjaList, const char* ninja) {

      struct Ans
      {
            const char** ninja;
            int          index;

            Ans(const char* c) {
                  ninja = &c;
                  index = -1;
            }

            ~Ans() {
                  ninja = nullptr;
            }
      };

      auto findNinja = [](char*& ninjaInList, void* v) {
            Ans* ans = (Ans*) v;

            ans->index++;

            if (strcmp(ninjaInList, *ans->ninja) == 0) {
                  throw true;
            }
      };

      Ans ans(ninja);

      try {
            ninjaList.traverse(findNinja, &ans);
      } catch (bool b) {
            return ans.index;
      }
      return -1;
}
int isInList(L1List<char**>& ninjaList, char**& ninja) {

      struct Ans
      {
            char** ninja;
            int    index;

            Ans(char** c) {
                  ninja = c;
                  index = -1;
            }

            ~Ans() {
                  ninja = nullptr;
            }
      };

      auto findNinja = [](char**& ninjaInList, void* v) {
            Ans* ans = (Ans*) v;

            ans->index++;

            if (ninjaInList == ans->ninja) {
                  throw true;
            }
      };

      Ans ans(ninja);

      try {
            ninjaList.traverse(findNinja, &ans);
      } catch (bool b) {
            return ans.index;
      }
      return -1;
}
void removeNinja(L1List<char*>& ninjaList, const char* ninja) {
      ninjaList.remove(isInList(ninjaList, ninja));
}
void removeNinja(L1List<char**>& ninjaList, char**& ninja) {
      ninjaList.remove(isInList(ninjaList, ninja));
}

//
// ──────────────────────────────────────────────────────────────── III
//   :::::: P R I N T   A N S W E R : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────
//


void print(char*& c) {
      cout << " " << c;
}
void print(const char* c) {
      cout << " " << c;
}
void print(const int& i) {
      cout << " " << i;
}
void print(const double& d) {
      cout << " " << setprecision(12) << d;
}
void print(L1List<char*>& l) {
      void (*op)(char*&) = &print;
      l.traverse(op);
}
void print(L1List<char**>& l) {
      auto print_charpp = [](char**& c) { cout << " " << *c; };
      l.traverse(print_charpp);
}
void print(time_t& t) {
      char* time = new char[26];
      strPrintTime(time, t);
      print(time);
      delete[] time;
      time = nullptr;
}
