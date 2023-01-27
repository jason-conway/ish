#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

if [[ "${1-}" =~ ^-*h(elp)?$ ]]; then
    echo 'Usage: ./rebuild.sh

Rebuild iSH CLI

'
    exit
fi

cd "$(dirname "$0")"

main() {
    cd ..
    CC=clang LD=lld meson setup --wipe build
    cd build
    ninja
}

main "$@"
