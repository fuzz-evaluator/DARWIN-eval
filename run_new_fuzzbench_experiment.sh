#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
EXPERIMENT_NAME=darwin-eval

cd "${SCRIPT_DIR}/fuzzbench"

source .venv/bin/activate
PYTHONPATH=. python3 experiment/run_experiment.py \
  --experiment-config "${SCRIPT_DIR}/config.yaml" \
  --benchmarks bloaty_fuzz_target curl_curl_fuzzer_http freetype2_ftfuzzer harfbuzz_hb-shape-fuzzer libjpeg-turbo_libjpeg_turbo_fuzzer libpng_libpng_read_fuzzer libxml2_xml libxslt_xpath mbedtls_fuzz_dtlsclient openssl_x509 openthread_ot-ip6-send-fuzzer proj4_proj_crs_to_crs_fuzzer re2_fuzzer sqlite3_ossfuzz systemd_fuzz-link-parser vorbis_decode_fuzzer woff2_convert_woff2ttf_fuzzer zlib_zlib_uncompress_fuzzer \
  --experiment-name "${EXPERIMENT_NAME}" \
  --concurrent-builds 2 \
  --runners-cpus 90 --measurers-cpus 10 \
  -a \
  --fuzzers afl_2_55_b darwin darwin_rand mopt
