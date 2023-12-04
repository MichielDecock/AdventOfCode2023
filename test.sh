#!/usr/bin/env bash
cd "$(dirname "$0")"

./build.sh
./build/tests/TestRunner
