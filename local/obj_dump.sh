#!/usr/bin/env bash

# Syntax workaround for llvm-objdump in Hotspot

if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi
START=''
STOP=''
while [ $# -gt 0 ]; do
  case "$1" in
    --start-address)
      START="$2"
      ;;
    --stop-address)
      STOP="$2"
      ;;
    *) ;;
  esac
  shift
done

llvm-objdump -d -l -C --start-address=$START --stop-address=$STOP /home/jasonconway/git/ish/build/ish
