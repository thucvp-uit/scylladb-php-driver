#!/usr/bin/env bash
# -*- coding: utf-8 -*-

cmake --preset CI || exit 1
pushd out/CI || exit 1
ninja || exit 1

ninja install || exit 1

popd || exit 1

PHP_INI=$("/root/php/bin/php" --ini | grep "php.ini" | awk '{ print $5 }' | xargs -I {} printf '%s/php.ini' {})

cat cassandra.ini >>"$PHP_INI" || exit 1
