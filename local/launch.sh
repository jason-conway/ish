#!/usr/bin/env bash

set -o errexit

cd "$(dirname "$0")" && cd ./../build/

./ish rootfstype=fakefs root=./../alpine/ rw ignore_loglevel
