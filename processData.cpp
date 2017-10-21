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
void problem1(L1List<NinjaInfo_t>&);
void problem2(L1List<NinjaInfo_t>&);
void problem3(L1List<NinjaInfo_t>&);
void problem4(L1List<NinjaInfo_t>&);
void problem5(L1List<NinjaInfo_t>&, char*);
void problem6(L1List<NinjaInfo_t>&, char*);
void problem7(L1List<NinjaInfo_t>&, char*);
void problem8(L1List<NinjaInfo_t>&, char*);
void problem9(L1List<NinjaInfo_t>&);
void problem10(L1List<NinjaInfo_t>&);
void problem11(L1List<NinjaInfo_t>&, char*);
void problem12(L1List<NinjaInfo_t>&);
void problem13(L1List<NinjaInfo_t>&, char*);
void problem14(L1List<NinjaInfo_t>&);

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
double TotalDistance(L1List<NinjaInfo_t>*, const char*);
double TotalTime(L1List<NinjaInfo_t>*, const char*);
double ThinkingTime(L1List<NinjaInfo_t>*, const char*);
bool   isTrap(L1List<NinjaInfo_t>*, const char*, double*);

// print the result
void print() {
      cout << " Something's not right";
}
void print(char*&);
void print(const char*);
void print(const int&);
void print(const double&);
void print(L1List<char*>*);
void print(time_t&);


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
                  problem9(nList);
                  break;
            case 10:
                  problem10(nList);
                  break;
            case 11:
                  problem11(nList, args);
                  break;
            case 12:
                  problem12(nList);
                  break;
            case 13:
                  problem13(nList, args);
                  break;
            case 14:
                  problem14(nList);
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

void problem1(L1List<NinjaInfo_t>& list) {}
void problem2(L1List<NinjaInfo_t>& list) {}
void problem3(L1List<NinjaInfo_t>& list) {}
void problem4(L1List<NinjaInfo_t>& list) {}
void problem5(L1List<NinjaInfo_t>& list, char* ninja) {}
void problem6(L1List<NinjaInfo_t>& list, char* ninja) {}
void problem7(L1List<NinjaInfo_t>& list, char* ninja) {}
void problem8(L1List<NinjaInfo_t>& list, char* ninja) {}
void problem9(L1List<NinjaInfo_t>& list) {}
void problem10(L1List<NinjaInfo_t>& list) {}
void problem11(L1List<NinjaInfo_t>& list, char* ninja) {}
void problem12(L1List<NinjaInfo_t>& list) {}
void problem13(L1List<NinjaInfo_t>& list, char* ninja) {}
void problem14(L1List<NinjaInfo_t>& list) {}


double TotalDistance(L1List<NinjaInfo_t>*, const char*) {}
double TotalTime(L1List<NinjaInfo_t>*, const char*) {}
double ThinkingTime(L1List<NinjaInfo_t>*, const char*) {}
bool   isTrap(L1List<NinjaInfo_t>*, const char*, double*) {}

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
void print(L1List<char*>* l) {
      void (*op)(char*&) = &print;
      l->traverse(op);
}
void print(time_t& t) {
      char* time = new char[26];
      strPrintTime(time, t);
      print(time);
}