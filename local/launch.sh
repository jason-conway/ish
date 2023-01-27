#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

cd "$(dirname "$0")"
cd ./../build/

gnome-terminal -- ./ish rootfstype=fakefs root=./../alpine/ rw ignore_loglevel
