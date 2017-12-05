/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa
 * University
 * Description : library for Assignment 1 - Data structures and Algorithms -
 * Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void strPrintTime(char* des, time_t& t) {
      tm* pTime = gmtime(&t);
      strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

void loadNinjaDB(char* fName, L1List<NinjaInfo_t>& db) {
      // TODO: write code to load information from file into db
      ifstream file(fName, ios::in);

      if (!file.is_open()) {
            exit(-1);
      }

      char* buffer = new char[100];
      file.getline(buffer, 100);

      while (file.getline(buffer, 100)) {

            if (buffer[0] == '\0' || buffer[0] == '\r')
                  continue;

            NinjaInfo_t ninja;
            if (!parseNinjaInfo(buffer, ninja)) {
                  exit(-2);
            }
            db.insertHead(ninja);
      }
      delete[] buffer;
      buffer = nullptr;
      file.close();
      db.reverse();
}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
      // TODO: write code to parse information from a string buffer, ignore if
      // you don't use it
      struct tm thisTime;
      int       rev = 0;

      const char* temp = pBuf;

      if (
         sscanf(
            temp,
            "%d,%d/%d/%d %d:%d:%d,%10[a-zA-Z0-9],%lF,%lF,%*s",
            &rev,
            &thisTime.tm_mon,
            &thisTime.tm_mday,
            &thisTime.tm_year,
            &thisTime.tm_hour,
            &thisTime.tm_min,
            &thisTime.tm_sec,
            nInfo.id,
            &nInfo.longitude,
            &nInfo.latitude) != 10)
            return false;

      thisTime.tm_year -= 1900;
      thisTime.tm_mon -= 1;
      thisTime.tm_isdst = -1;

      nInfo.timestamp = timegm(&thisTime);

      size_t idlength = strlen(nInfo.id);
      if (idlength < 4) {
            memmove(nInfo.id + 4 - idlength, nInfo.id, 4);
            for (; idlength < 4; ++idlength) {
                  nInfo.id[4 - idlength - 1] = '0';
            }
      }

      return true;
}


void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
      void** pGData = new void*[2];
      pGData[0]     = &eventList;
      pGData[1]     = &bList;
      initNinjaGlobalData(pGData);

      while (!eventList.isEmpty()) {
            if (!processEvent(eventList[0], bList, pGData))
                  cout << eventList[0].code << " is an invalid event\n";
            eventList.removeHead();
      }

      releaseNinjaGlobalData(pGData);
}


bool initNinjaGlobalData(void** pGData) {
      /// TODO: You should define this function if you would like to use some
      /// extra data
      /// the data should be allocated and pass the address into pGData

      L1List<ninjaEvent_t>* eventList = (L1List<ninjaEvent_t>*) pGData[0];
      L1List<NinjaInfo_t>*  bList     = (L1List<NinjaInfo_t>*) pGData[1];

      /* Delete void* allocated for eventList and bList */
      delete[] pGData;

      pGData = new void*[3];
      /// 1 for allEvents
      /// 1 for allNinjas
      /// 1 for event14

      L1List<char*>*  allEvents = new L1List<char*>();
      L1List<char*>*  allNinjas = new L1List<char*>();
      L1List<char**>* event14   = new L1List<char**>();

      pGData[0] = allEvents;
      pGData[1] = allNinjas;
      pGData[2] = event14;

      auto copyEvents = [](ninjaEvent_t& event, void* v) {
            L1List<char*>* allEvents  = (L1List<char*>*) v;
            char*          copiedCode = new char[EVENT_CODE_SIZE];
            strcpy(copiedCode, event.code);
            allEvents->insertHead(copiedCode);
      };

      auto getNinjaList = [](NinjaInfo_t& ninja, void* v) {
            L1List<char*>* allNinjas = (L1List<char*>*) v;

            auto findExistingNinja = [](char*& ninja, void* v) {
                  char* ninjaTobeFound = (char*) v;
                  if (strcmp(ninja, ninjaTobeFound) == 0) {
                        throw true;
                  }
            };


            char* thisNinjaTag = new char[ID_MAX_LENGTH];
            strcpy(thisNinjaTag, ninja.id);

            try {
                  allNinjas->traverse(findExistingNinja, thisNinjaTag);
            } catch (bool b) {
                  // somehow find in list
                  return;
            }
            allNinjas->insertHead(thisNinjaTag);
      };

      eventList->traverse(copyEvents, allEvents);
      allEvents->reverse();
      bList->traverse(getNinjaList, allNinjas);
      allNinjas->reverse();

      return true;
}

void releaseNinjaGlobalData(void* pGData) {
      /// TODO: You should define this function if you allocated extra data at
      /// initialization stage
      /// The data pointed by pGData should be released
      L1List<char*>** listOfList = (L1List<char*>**) pGData;
      delete[] listOfList;
      listOfList = NULL;
      pGData     = NULL;
}


void printNinjaInfo(NinjaInfo_t& b) {
      printf(
         "%s: (%0.5f, %0.5f), %s\n",
         b.id,
         b.longitude,
         b.latitude,
         ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg) {
      return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad) {
      return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
      double lat1r, lon1r, lat2r, lon2r, u, v;
      lat1r = deg2rad(lat1d);
      lon1r = deg2rad(lon1d);
      lat2r = deg2rad(lat2d);
      lon2r = deg2rad(lon2d);
      u     = sin((lat2r - lat1r) / 2);
      v     = sin((lon2r - lon1r) / 2);
      return 2.0 * earthRadiusKm *
             asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
