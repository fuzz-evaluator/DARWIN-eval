#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

git submodule update --init --recursive

cd "${SCRIPT_DIR}/fuzzbench"

sudo apt update
sudo apt -y install build-essential python3.10-dev python3.10-venv

sudo mkdir /opt/fuzzbench
sudo chown -hR $USER:$USER /opt/fuzzbench

make install-dependencies
