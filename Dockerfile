FROM ubuntu:18.04
LABEL maintainer "JYPark09 <jyp10987@gmail.com>"

RUN apt-get update && apt-get install -y \
	build-essential \
	libx11-dev \
	freeglut3-dev \
	libudev-dev \
	libfreetype6-dev \
	cmake \
	--no-install-recommends \
	&& rm -rf /var/lib/apt/lists/*

COPY . /app

WORKDIR /app/build
RUN cmake .. && \
	make -j "$(nproc)" && \
	make install && \
	bin/UnitTest

WORKDIR /