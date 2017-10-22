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
void problem3(L1List<NinjaInfo_t>&);
void problem4(L1List<NinjaInfo_t>&);
void problem5(L1List<NinjaInfo_t>&, char*);
void problem6(L1List<NinjaInfo_t>&, char*);
void problem7(L1List<NinjaInfo_t>&, char*);
void problem8(L1List<NinjaInfo_t>&, char*);
void problem9(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem10(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem11(L1List<char*>&, char*);
void problem12(L1List<NinjaInfo_t>&, L1List<char*>&);
void problem13(L1List<NinjaInfo_t>&, L1List<char*>&, char*);
void problem14(L1List<NinjaInfo_t>&, L1List<char*>&);

// time frome lhs, to rhs
double timeInterval(NinjaInfo_t& lhs, NinjaInfo_t& rhs) {
      return difftime(rhs.timestamp, lhs.timestamp);
}
// distance between lhs and rhs
double distance(NinjaInfo_t& lhs, NinjaInfo_t& rhs) {
      return distanceEarth(
         lhs.latitude, lhs.longitude, rhs.latitude, rhs.longitude);
}
// whether ninja stop between lhs and rhs
bool isStop(NinjaInfo_t& lhs, NinjaInfo_t& rhs) {
      return distance(lhs, rhs) / 1000 <= 5;
}

// total distance of a ninja
double TotalDistance(L1List<NinjaInfo_t>&, const char*);
double TotalTime(L1List<NinjaInfo_t>&, const char*);
double ThinkingTime(L1List<NinjaInfo_t>&, const char*);
bool   isTrap(L1List<NinjaInfo_t>&, const char*, double[4]);

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

      char* args = NULL;
      int   code = extractEvent(event, args);

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
                  problem3(nList);
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
                  problem8(nList, args);
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
                  problem13(nList, *allNinjas, args);
                  break;
            case 14:
                  problem14(nList, *allNinjas);
                  break;
            default:
                  delete args;
                  args = NULL;
                  return false;
      }

      delete args;
      args = NULL;
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
                  return Event.code[0] - '0';
            case 2:
                  return 10 * (Event.code[0] - '0') + (Event.code[1] - '0');
            case 5:
                  args = new char[5];
                  for (int i    = 0; i < 4; ++i)
                        args[i] = Event.code[i + 1];
                  args[4]       = '\0';
                  return Event.code[0] - '0';
            case 6:
                  args = new char[5];
                  for (int i    = 0; i < 4; ++i)
                        args[i] = Event.code[i + 2];
                  args[4]       = '\0';
                  return 10 * (Event.code[0] - '0') + (Event.code[1] - '0');
            case 18:
                  args = new char[17];
                  for (int i    = 0; i < 16; ++i)
                        args[i] = Event.code[i + 2];
                  args[16]      = '\0';
                  return 13;
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
      cout << "0:";
      print(allEvents);
      cout << "\n";
}


void problem1(L1List<NinjaInfo_t>& recordList) {
      cout << "1:";
      print(recordList[0].id);
      cout << "\n";
}
void problem2(L1List<NinjaInfo_t>& recordList) {
      cout << "2:";
      print(recordList[recordList.getSize() - 1].id);
      cout << "\n";
}
void problem3(L1List<NinjaInfo_t>& ninjaList) {
      cout << "3:";
      int ninjaSize = ninjaList.getSize();
      print(ninjaSize);
      cout << "\n";
}
void problem4(L1List<NinjaInfo_t>& ninjaList) {
      char* maxId = new char[10];

      auto findMaxId = [](NinjaInfo_t& ninja, void* v) {
            char* maxId = (char*) v;
            if (strcmp(ninja.id, maxId) > 0)
                  strcpy(maxId, ninja.id);
      };

      ninjaList.traverse(findMaxId, maxId);

      cout << "4:";
      print(maxId);
      cout << "\n";

      delete maxId;
      maxId = NULL;
}
void problem5(L1List<NinjaInfo_t>& recordList, char* ninja) {
      auto findFirstShowUp = [](NinjaInfo_t& ninjaRecord, void* v) {
            NinjaInfo_t* ans = (NinjaInfo_t*) v;
            if (strcmp(ans->id, "") == 0)
                  return;

            if (strcmp(ans->id, ninjaRecord.id) == 0) {
                  ans->timestamp = ninjaRecord.timestamp;
                  strcpy(ans->id, "");
            }
      };

      NinjaInfo_t* ans = new NinjaInfo_t(ninja);
      recordList.traverse(findFirstShowUp, ans);

      cout << "5:";
      if (strcmp(ans->id, "") == 0)
            print(ans->timestamp);
      else
            print(-1);
      cout << "\n";
      delete ans;
      ans = NULL;
}
void problem6(L1List<NinjaInfo_t>& recordList, char* ninja) {
      struct Ans
      {
            NinjaInfo_t lastTime;
            time_t      returnTime;
            bool        first;

            Ans(char* n) : lastTime(n) {
                  returnTime = 0;
                  first      = true;
            }
      };

      auto findLastStopTime = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;
            if (strcmp(ans->lastTime.id, info.id) != 0)
                  return;

            if (ans->first)
                  ans->first = false;

            else if (isStop(ans->lastTime, info))
                  ans->returnTime = info.timestamp;

            ans->lastTime = info;
      };

      Ans* ans = new Ans(ninja);
      recordList.traverse(findLastStopTime, ans);

      cout << "6:";
      if (ans->first)
            print(-1);
      else
            print(ans->returnTime);
      cout << "\n";

      delete ans;
      ans = NULL;
}
void problem7(L1List<NinjaInfo_t>& recordList, char* ninja) {
      struct Ans
      {
            NinjaInfo_t lastTime;
            int         timeStop;
            bool        first;

            Ans(char* n) : lastTime(n) {
                  timeStop = 0;
                  first    = true;
            }
      };

      auto findTimeStop = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;
            if (strcmp(ans->lastTime.id, info.id) != 0)
                  return;

            if (ans->first)
                  ans->first = false;

            else if (isStop(ans->lastTime, info))
                  ans->timeStop++;

            ans->lastTime = info;
      };

      Ans* ans = new Ans(ninja);
      recordList.traverse(findTimeStop, ans);

      cout << "7:";
      if (ans->first)
            print(-1);
      else
            print(ans->timeStop);
      cout << "\n";

      delete ans;
      ans = NULL;
}
void problem8(L1List<NinjaInfo_t>& recordList, char* ninja) {
      double distance = TotalDistance(recordList, ninja);

      cout << "8:";
      if (distance == 0)
            print(-1);
      else
            print(distance);
      cout << "\n";
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
                  ninja = NULL;
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

      cout << "9:";
      print(ans->ninja);
      cout << "\n";
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
                  ninja = NULL;
            }
      };

      auto findDistanceMax = [](char*& ninja, void* v) {
            Ans*   ans          = (Ans*) v;
            double maxThisNinja = TotalTime(ans->recordList, ninja);

            if (ans->maxTime >= maxThisNinja)
                  return;

            ans->maxTime = maxThisNinja;
            strcpy(ans->ninja, ninja);
      };

      Ans* ans = new Ans(recordList);
      ninjaList.traverse(findDistanceMax, ans);

      cout << "10:";
      print(ans->ninja);
      cout << "\n";
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
                  attackedNinja = NULL;
                  fakeNinja     = NULL;
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

      cout << "11:";
      if (strcmp(ans->attackedNinja, "") == 0)
            print(-1);
      else
            print(ans->attackedNinja);
      cout << "\n";

      delete ans;
      ans = NULL;
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
                  ninja = NULL;
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

      cout << "12:";
      print(ans->ninja);
      cout << "\n";
}
void problem13(
   L1List<NinjaInfo_t>& recordList,
   L1List<char*>&       ninjaList,
   char*                trap) {}
void problem14(L1List<NinjaInfo_t>& recordList, L1List<char*>& ninjaList) {}


//
// ──────────────────────────────────────────────────────────────────────── II
//   :::::: N I N J A   A T T R I B U T E S : :  :   :    :     :        : :
// ──────────────────────────────────────────────────────────────────────────────────
//


double TotalDistance(L1List<NinjaInfo_t>& recordList, const char* ninja) {

      struct Ans
      {
            NinjaInfo_t lastStop;
            double      distance;

            Ans(const char* c) : lastStop(c) {
                  distance = 0;
            }
      };

      auto findDistance = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(ans->lastStop.id, info.id) != 0)
                  return;

            ans->distance += distance(ans->lastStop, info);
            ans->lastStop = info;
      };

      Ans* ans = new Ans(ninja);
      recordList.traverse(findDistance, ans);
      if (ans->distance == 0)
            return 0;
      return ans->distance;
}
double TotalTime(L1List<NinjaInfo_t>& recordList, const char* ninja) {
      struct Ans
      {
            NinjaInfo_t lastStop;
            double      time;

            Ans(const char* c) : lastStop(c) {
                  time = 0;
            }
      };

      auto findDistance = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(ans->lastStop.id, info.id) != 0)
                  return;

            ans->time += timeInterval(ans->lastStop, info);
            ans->lastStop = info;
      };

      Ans* ans = new Ans(ninja);
      recordList.traverse(findDistance, ans);
      if (ans->time == 0)
            return 0;
      return ans->time;
}
double ThinkingTime(L1List<NinjaInfo_t>& recordList, const char* ninja) {
      struct Ans
      {
            NinjaInfo_t lastStop;
            double      time;

            Ans(const char* c) : lastStop(c) {
                  time = 0;
            }
      };

      auto findDistance = [](NinjaInfo_t& info, void* v) {
            Ans* ans = (Ans*) v;

            if (strcmp(ans->lastStop.id, info.id) != 0)
                  return;

            if (isStop(ans->lastStop, info))
                  ans->time += timeInterval(ans->lastStop, info);
            ans->lastStop = info;
      };

      Ans* ans = new Ans(ninja);
      recordList.traverse(findDistance, ans);
      if (ans->time == 0)
            return 0;
      return ans->time;
}
bool isTrap(
   L1List<NinjaInfo_t>& recordList,
   const char*          ninja,
   double (&trapPlace)[4]) {
      return false;
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
}