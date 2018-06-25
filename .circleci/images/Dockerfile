FROM ubuntu:18.10


# obtained some of this from here
# https://stackoverflow.com/questions/25899912/install-nvm-in-docker

# Replace shell with bash so we can source files
RUN rm /bin/sh && ln -s /bin/bash /bin/sh

# Set debconf to run non-interactively
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# Install base dependencies
RUN apt-get update && apt-get install -y -q --no-install-recommends \
        git \
        ssh \
        tar \
        gzip \
        apt-transport-https \
        build-essential \
        ca-certificates \
        curl \
        libssl-dev \
        wget \
        python-pip \
    && rm -rf /var/lib/apt/lists/*


RUN wget https://cmake.org/files/v3.11/cmake-3.11.1.tar.gz
RUN tar -xzvf cmake-3.11.1.tar.gz
RUN cd ./cmake-3.11.1 && chmod +x bootstrap && ./bootstrap
RUN cd ./cmake-3.11.1 && make
RUN cd ./cmake-3.11.1 && make install
RUN rm -rf ./cmake-3.11.1

WORKDIR /wrk

ENTRYPOINT ["/bin/bash"]
