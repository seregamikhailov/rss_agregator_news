FROM gcc:12

RUN apt-get update && apt-get install -y \
    curl \
    libcurl4-openssl-dev \
    libtinyxml2-dev \
    libjsoncpp-dev \
    && apt-get clean

RUN curl -LO https://cmake.org/files/v3.29/cmake-3.29.0-linux-x86_64.tar.gz \
    && tar -zxvf cmake-3.29.0-linux-x86_64.tar.gz \
    && mv cmake-3.29.0-linux-x86_64 /opt/cmake \
    && ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

RUN cmake --version

WORKDIR /app
COPY . /app

RUN mkdir build && cd build && cmake .. && make

RUN ls -l /app/build

WORKDIR /app/build

EXPOSE 8080

CMD ["./rss_agregator_rss"]

