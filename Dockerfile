FROM ubuntu:22.04 as base

ARG PHP_VERSION=8.2.6
ARG PHP_ZTS="nts"

ENV PATH="$PATH:$HOME/.local/bin:$HOME/php/bin"

RUN apt-get update -y \
    && apt-get upgrade -y \
    && apt-get install -y \
        autoconf \
        pkg-config \
        sudo \
        wget \
        git \
        gcc \
        g++ \
        gdb \
        python3 \
        python3-pip \
        unzip \
        mlocate \
        build-essential \
        ninja-build \
        libasan8 \
        libubsan1 \
    && pip3 install cmake cqlsh \
    && apt-get clean

COPY ./scripts /tmp/scripts

WORKDIR /tmp

RUN ./scripts/compile-php.sh -k -v $PHP_VERSION -o $HOME -s -d no -zts $PHP_ZTS \
    && $HOME/php/bin/php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');" \
    && $HOME/php/bin/php composer-setup.php --install-dir=/bin --filename=composer \
    && $HOME/php/bin/php -r "unlink('composer-setup.php');" \
    && rm -rf /tmp/scripts

ENTRYPOINT ["bash"]

FROM base as build

COPY . /ext-scylladb

WORKDIR /ext-scylladb

RUN ./scripts/compile-extension.sh

ENTRYPOINT ["bash"]
