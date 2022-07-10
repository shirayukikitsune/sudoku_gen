FROM ubuntu:22.04

RUN apt-get update && apt-get install cmake build-essential libboost-log-dev libboost-program-options-dev -yy

WORKDIR /app

COPY . .

RUN mkdir "cmake-build-release" && \
    cd "cmake-build-release" && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_DEPENDS_USE_COMPILER=FALSE -G "CodeBlocks - Unix Makefiles" .. && \
    cmake --build . --target sudoku_gen -- -j 4

FROM ubuntu:22.04

RUN apt-get update && apt-get install libboost-log1.74.0 libboost-program-options1.74.0 -yy

WORKDIR /app

COPY --from=0 /app/cmake-build-release/sudoku_gen .

CMD /app/sudoku_gen
