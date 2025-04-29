FROM ubuntu:22.04

RUN apt-get update && apt-get install cmake build-essential libboost-log-dev libboost-program-options-dev -yy

WORKDIR /app

COPY . .

RUN mkdir "cmake-build-release" && \
    cd "cmake-build-release" && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_DEPENDS_USE_COMPILER=FALSE -G "CodeBlocks - Unix Makefiles" .. && \
    cmake --build . --target sudoku_gen -- -j 4

FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install libboost-log1.74.0 libboost-program-options1.74.0 apt-transport-https ca-certificates gnupg -yy && \
    echo "deb [signed-by=/usr/share/keyrings/cloud.google.gpg] https://packages.cloud.google.com/apt cloud-sdk main" | tee -a /etc/apt/sources.list.d/google-cloud-sdk.list && \
    curl https://packages.cloud.google.com/apt/doc/apt-key.gpg | tee /usr/share/keyrings/cloud.google.gpg && \
    apt-get update -y && \
    apt-get install google-cloud-cli -y && \
    gcloud init

WORKDIR /app

COPY --from=0 /app/cmake-build-release/sudoku_gen .

CMD /app/sudoku_gen
