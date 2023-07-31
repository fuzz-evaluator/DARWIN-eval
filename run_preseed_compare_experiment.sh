#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
EXPERIMENT_NAME="preseed-eval"

cd "${SCRIPT_DIR}/fuzzbench"

source .venv/bin/activate
PYTHONPATH=. python3 experiment/run_experiment.py \
  --experiment-config "${SCRIPT_DIR}/preseed_config.yaml" \
  --benchmarks freetype2_ftfuzzer libjpeg-turbo_libjpeg_turbo_fuzzer libxml2_xml libxslt_xpath proj4_proj_crs_to_crs_fuzzer sqlite3_ossfuzz \
  --experiment-name "${EXPERIMENT_NAME}" \
  --concurrent-builds 8 \
  --measurers-cpus 12 --runners-cpus 90 \
  --fuzzers darwin darwin_no_pre_seed
