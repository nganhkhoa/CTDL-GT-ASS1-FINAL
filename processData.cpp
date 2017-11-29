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
void problem4(L1List<NinjaInfo_t>&);
void problem5(L1List<NinjaInfo_t>&, char*);
void problem6(L1List<NinjaInfo_t>&, char*);
void problem7(L1List<NinjaInfo_t>&, char*);
void problem8(L1List<NinjaInfo_t>&, L1List<char*>&, char*);
void problem9(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem10(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem11(L1List<char*>&, char*);
void problem12(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem13(L1List<NinjaInfo_t>&, char*);
void problem14(L1List<NinjaInfo_t>&, L1List<char*>&);

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
bool    isInList(L1List<char*>&, const char*);
void    removeNinja(L1List<char*>&, const char*);

// print the result
void print() {
      cout << " Something's not right";
}
void print(char*&);
void print(const char*);
void print(const int&);
void print(const double&);
void print(L1List<char*>&);
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
      L1List<char*>** listOfList = (L1List<char*>**) pGData;
      L1List<char*>*  allEvents  = listOfList[0];
      L1List<char*>*  allNinjas  = listOfList[1];
      // allEvents by its order
      // allNinjas by the reversed order


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
                  problem4(nList);
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
                  problem11(*allNinjas, args);
                  break;
            case 12:
                  problem12(nList, *allNinjas);
                  break;
            case 13:
                  delete[] args;
                  args = nullptr;
                  return false;
                  // problem13(nList, args);
                  break;
            case 14:
                  problem14(nList, *allNinjas);
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

            case 18:
                  args = new char[17];
                  for (int i = 0; i < 16; ++i)
                        args[i] = Event.code[i + 2];
                  args[16] = '\0';
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
      cout << endl;
}
void problem1(L1List<NinjaInfo_t>& recordList) {
      print(recordList[0].id);
      cout << endl;
}
void problem2(L1List<NinjaInfo_t>& recordList) {
      print(recordList[recordList.getSize() - 1].id);
      cout << endl;
}
void problem3(L1List<char*>& ninjaList) {
      int ninjaSize = ninjaList.getSize();
      print(ninjaSize);
      cout << endl;
}
void problem4(L1List<NinjaInfo_t>& ninjaList) {
      char* maxId = new char[10];

      auto findMaxId = [](NinjaInfo_t& ninja, void* v) {
            char* maxId = (char*) v;
            if (strcmp(ninja.id, maxId) > 0)
                  strcpy(maxId, ninja.id);
      };

      ninjaList.traverse(findMaxId, maxId);

      print(maxId);
      cout << endl;

      delete[] maxId;
      maxId = nullptr;
}
void problem5(L1List<NinjaInfo_t>& recordList, char* ninja) {
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
            cout << endl;
            return;
      }

      print(-1);
      cout << endl;
}
void problem6(L1List<NinjaInfo_t>& recordList, char* ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* lastStopPlace;
            bool         first;
            bool         stop;

            Ans(char* n) {
                  lastPlace = new NinjaInfo_t(n);
                  first     = true;
                  stop      = false;
            }
      };

      auto findLastStopTime = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;
            if (strcmp(ans->lastPlace->id, info.id) != 0)
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

      Ans* ans = new Ans(ninja);
      recordList.traverse(findLastStopTime, ans);

      if (ans->first)
            print(-1);
      else
            print(ans->lastStopPlace->timestamp);

      cout << endl;

      delete ans;
      ans = nullptr;
}
void problem7(L1List<NinjaInfo_t>& recordList, char* ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* stopPlace;
            int          timeStop;
            bool         first;
            bool         stop;

            Ans(char* n) {
                  lastPlace = new NinjaInfo_t(n);
                  timeStop  = 0;
                  first     = true;
                  stop      = false;
            }
      };

      auto findTimeStop = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;
            if (strcmp(ans->lastPlace->id, info.id) != 0)
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

      Ans* ans = new Ans(ninja);
      recordList.traverse(findTimeStop, ans);

      if (ans->first)
            print(-1);
      else
            print(ans->timeStop);

      cout << endl;

      delete ans;
      ans = nullptr;
}
void problem8(
   L1List<NinjaInfo_t>& recordList,
   L1List<char*>&       allNinjas,
   char*                ninja) {
      double distance = TotalDistance(recordList, ninja);
      print(distance ? distance : -1);
      cout << endl;
}
void problem9(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {
      struct Ans
      {
            L1List<NinjaInfo_t>& recordList;
            double               maxDistance;
            char*                ninja;

            Ans(L1List<NinjaInfo_t>& l) : recordList(l) {
                  maxDistance = 0;
                  ninja       = new char[10];
            }

            ~Ans() {
                  delete[] ninja;
                  ninja = nullptr;
            }
      };

      auto findDistanceMax = [](char*& ninja, void* v) {
            Ans*   ans          = (Ans*) v;
            double maxThisNinja = TotalDistance(ans->recordList, ninja);

            if (ans->maxDistance >= maxThisNinja)
                  return;

            ans->maxDistance = maxThisNinja;
            strcpy(ans->ninja, ninja);
      };

      Ans* ans = new Ans(recordList);
      ninjaList.traverse(findDistanceMax, ans);

      print(ans->ninja);
      cout << endl;

      delete ans;
      ans = nullptr;
}
void problem10(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {
      struct Ans
      {
            L1List<NinjaInfo_t>& recordList;
            double               maxTime;
            char*                ninja;

            Ans(L1List<NinjaInfo_t>& l) : recordList(l) {
                  maxTime = 0;
                  ninja   = new char[10];
            }

            ~Ans() {
                  delete[] ninja;
                  ninja = nullptr;
            }
      };

      auto findDistanceMax = [](char*& ninja, void* v) {
            Ans*   ans          = (Ans*) v;
            double maxThisNinja = TotalTime(ans->recordList, ninja);

            //  cout << ninja << ": " << maxThisNinja << endl;

            if (ans->maxTime >= maxThisNinja)
                  return;

            ans->maxTime = maxThisNinja;
            strcpy(ans->ninja, ninja);
      };

      Ans* ans = new Ans(recordList);
      ninjaList.traverse(findDistanceMax, ans);

      print(ans->ninja);
      cout << endl;

      delete ans;
      ans = nullptr;
}
void problem11(L1List<char*>& ninjaList, char* ninja) {
      struct Ans
      {
            char* attackedNinja;
            char* fakeNinja;

            Ans(const char* f) {
                  fakeNinja     = new char[10];
                  attackedNinja = new char[10];
                  strcpy(fakeNinja, f);
                  strcpy(attackedNinja, "");
            }
            ~Ans() {
                  delete[] attackedNinja;
                  delete[] fakeNinja;
                  attackedNinja = nullptr;
                  fakeNinja     = nullptr;
            }
      };

      auto findAttackedNinja = [](char*& thisNinja, void* v) {
            Ans* ans = (Ans*) v;
            if (
               strcmp(ans->fakeNinja, thisNinja) > 0 &&
               strcmp(ans->attackedNinja, thisNinja) < 0) {
                  strcpy(ans->attackedNinja, thisNinja);
            }
      };

      Ans* ans = new Ans(ninja);
      ninjaList.traverse(findAttackedNinja, ans);

      if (strcmp(ans->attackedNinja, "") == 0)
            print(-1);
      else {
            print(ans->attackedNinja);
            removeNinja(ninjaList, ans->attackedNinja);
      }

      cout << endl;

      delete ans;
      ans = nullptr;
}
void problem12(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {
      struct Ans
      {
            L1List<NinjaInfo_t>& recordList;
            double               maxTime;
            char*                ninja;

            Ans(L1List<NinjaInfo_t>& l) : recordList(l) {
                  maxTime = 0;
                  ninja   = new char[10];
            }

            ~Ans() {
                  delete[] ninja;
                  ninja = nullptr;
            }
      };

      auto findDistanceMax = [](char*& ninja, void* v) {
            Ans*   ans          = (Ans*) v;
            double maxThisNinja = ThinkingTime(ans->recordList, ninja);

            if (ans->maxTime >= maxThisNinja)
                  return;

            ans->maxTime = maxThisNinja;
            strcpy(ans->ninja, ninja);
      };

      Ans* ans = new Ans(recordList);
      ninjaList.traverse(findDistanceMax, ans);

      print(ans->ninja);
      cout << endl;

      delete ans;
      ans = nullptr;
}
void problem13(L1List<NinjaInfo_t>& recordList, char* trap) {
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

            char* id = new char[strlen(info.id)];
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

      cout << endl;
}
void problem14(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {

      struct Ans
      {
            L1List<char*>        list;
            L1List<NinjaInfo_t>* recordList;
            char**               ninja;

            ~Ans() {
                  recordList = nullptr;
                  ninja      = nullptr;
            }
      };

      auto getlostlist = [](char*& ninja, void* v) {
            Ans* ans   = (Ans*) v;
            ans->ninja = &ninja;
            if (isLost(*ans->ninja, *ans->recordList))
                  ans->list.insertHead(*ans->ninja);
      };

      Ans* ans        = new Ans();
      ans->recordList = &recordList;

      ninjaList.traverse(getlostlist, ans);

      ans->list.reverse();
      if (ans->list.isEmpty())
            print(-1);
      else
            print(ans->list);
      cout << endl;

      delete ans;
      ans = nullptr;
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
            double       distance;
            bool         first;

            Ans(const char* c) {
                  lastStop = new NinjaInfo_t(c);
                  distance = 0;
                  first    = true;
            }
      };

      auto findDistance = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(ans->lastStop->id, info.id) != 0)
                  return;

            if (ans->first) {
                  ans->first = false;
            }

            else {
                  // ans->distance += distance(ans->lastStop, info);
                  // cout << ans->distance << endl;
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

      Ans* ans = new Ans(ninja);
      recordList.traverse(findDistance, ans);

      double distance = ans->distance;

      delete ans;
      ans = nullptr;

      return distance;
}
double TotalTime(L1List<NinjaInfo_t>& recordList, const char* ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* lastStopPlace;
            double       ThinkingTime;
            time_t       firstTime;
            bool         first;
            bool         stop;

            Ans(const char* c) {
                  lastPlace    = new NinjaInfo_t(c);
                  ThinkingTime = 0;
                  firstTime    = 0;
                  first        = true;
                  stop         = false;
            }

            ~Ans() {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
            }
      };

      auto findTotalTime = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(ans->lastPlace->id, info.id) != 0)
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

      Ans* ans = new Ans(ninja);
      recordList.traverse(findTotalTime, ans);

      // if he is still stop till end of time
      if (ans->stop) {
            ans->ThinkingTime +=
               timeInterval(*ans->lastStopPlace, *ans->lastPlace);
      }

      double time = difftime(ans->lastPlace->timestamp, ans->firstTime) -
                    ans->ThinkingTime;

      delete ans;
      ans = nullptr;

      return time;
}
double ThinkingTime(L1List<NinjaInfo_t>& recordList, const char* ninja) {
      struct Ans
      {
            NinjaInfo_t* lastPlace;
            NinjaInfo_t* lastStopPlace;
            double       time;
            bool         first;
            bool         stop;

            Ans(const char* c) {
                  lastPlace = new NinjaInfo_t(c);
                  time      = 0;
                  first     = true;
                  stop      = false;
            }

            ~Ans() {
                  lastPlace     = nullptr;
                  lastStopPlace = nullptr;
            }
      };

      auto findThinkingTime = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(ans->lastPlace->id, info.id) != 0)
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

      Ans* ans = new Ans(ninja);
      recordList.traverse(findThinkingTime, ans);

      // if he is still stop till end of time
      if (ans->stop) {
            ans->time += timeInterval(*ans->lastStopPlace, *ans->lastPlace);
      }

      double time = ans->time;

      delete ans;
      ans = nullptr;

      return time;
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

      Ans* ans   = new Ans();
      ans->ninja = &ninja;

      recordList.traverse(getliststop, ans);

      if (!ans->stop)
            ans->liststop.insertHead(*ans->lastpoint);

      // ans->liststop.removeHead();

      while (!ans->liststop.isEmpty()) {
            try {
                  findloop(ans->liststop);
            } catch (bool b) {
                  delete ans;
                  ans = nullptr;
                  return true;
            }
      }

      delete ans;
      ans = nullptr;
      return false;
}


bool isInList(L1List<char*>& ninjaList, const char* ninja) {

      struct Ans
      {
            char* ninja;
            int   index;

            Ans(const char* c) {
                  ninja = new char[strlen(c)];
                  strcpy(ninja, c);
                  index = -1;
            }

            ~Ans() {
                  delete[] ninja;
                  ninja = nullptr;
            }
      };

      auto findNinja = [](char*& ninjaInList, void* v) {
            Ans* ans = (Ans*) v;

            ans->index++;

            if (strcmp(ninjaInList, ans->ninja) == 0) {
                  throw true;
            }
      };

      Ans* ans = new Ans(ninja);

      try {
            ninjaList.traverse(findNinja, ans);
      } catch (bool b) {
            int index = ans->index;
            delete ans;
            ans = nullptr;
            return index;
      }

      delete ans;
      ans = nullptr;

      return -1;
}

void removeNinja(L1List<char*>& ninjaList, const char* ninja) {
      int index = isInList(ninjaList, ninja);
      ninjaList.remove(index);
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
void print(time_t& t) {
      char* time = new char[26];
      strPrintTime(time, t);
      print(time);
      delete[] time;
      time = nullptr;
}
