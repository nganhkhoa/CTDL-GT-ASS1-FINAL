/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa
 * University
 * Description : library for Assignment 1 - Data structures and Algorithms -
 * Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"


/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t>& eList) {
      std::ifstream file(fName, std::ios::in);

      if (!file.is_open()) {
            cout << "File not found\n";
            cout << "Exiting\n";
            exit(-1);
      }

      char* buffer = new char[100];
      file.getline(buffer, 100);

      char* code      = new char[20]{0};
      int   codeIndex = 0;
      do {
            if (string(buffer).empty())
                  continue;

            for (int i = 0; buffer[i] != '\0'; ++i) {
                  if (buffer[i] == ' ' || buffer[i] == ';') {
                        ninjaEvent_t event;
                        strcpy(event.code, code);
                        eList.push_back(event);

                        delete[] code;
                        code      = new char[20]{0};
                        codeIndex = 0;
                  }
                  else {
                        code[codeIndex++] = buffer[i];
                  }
            }
      } while (file.getline(buffer, 100));
      delete[] buffer;
      buffer = NULL;
      file.close();

      if (code[0] != '\0') {
            ninjaEvent_t event;
            strcpy(event.code, code);
            eList.push_back(event);
      }

      delete[] code;
      code = NULL;
}
