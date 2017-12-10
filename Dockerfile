FROM rikorose/gcc-cmake

RUN mkdir FINAL

COPY main.cpp FINAL/main.cpp
COPY processData.cpp FINAL/processData.cpp
COPY dbLib.h FINAL/dbLib.h
COPY dbLib.cpp FINAL/dbLib.cpp
COPY eventLib.h FINAL/eventLib.h
COPY eventLib.cpp FINAL/eventLib.cpp
COPY listLib.h FINAL/listLib.h

COPY CMakeLists.txt FINAL/CMakeLists.txt

RUN mkdir FINAL/build

RUN cmake -B/FINAL/build -H/FINAL -DCMAKE_BUILD_TYPE=MinSizeRel

RUN make -C /FINAL/build

ENV dir "./"
ENV event "events.txt"
ENV data "data.csv"

ENTRYPOINT ["/FINAL/build/a01", "files/events.txt", "files/data_origin.csv"]