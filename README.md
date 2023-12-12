# Artifact Evaluation - DARWIN

This repository contains the FuzzBench setup and experiment configuration we use to reproduce the claims from [DARWIN (paper)](https://www.ndss-symposium.org/ndss-paper/darwin-survival-of-the-fittest-fuzzing-mutators/). DARWIN's source code is at [DARWIN-upstream](https://github.com/fuzz-evaluator/DARWIN-upstream).
In this repository we will guide through the setup of our environment so that you can reproduce our results. You can also find all FuzzBench reports [here](fuzzbench_reports). Please clone the repository and open the `index.html` to view the report. 


## Conducted Experiments
In order to reproduce the results from the paper, we conduct three different experiments:

### Experiment 1: Coverage
First, we reproduce DARWIN's results in terms of coverage. To do so, we use FuzzBench and compare DARWIN against the following competitors:
   * AFL 2.52b (initially; MOpt is based on this version)
   * AFL 2.55b (baseline of DARWIN)
   * MOpt

We ran this experiment twice: The first time, we use DARWIN as implemented in [FuzzBench DARWIN](https://github.com/google/fuzzbench/tree/3cf599ade53f55eb149f018660820b5b50fd6067/fuzzers/darwin), but disabled the *-s* flag as it appeared to enable unstable behavior. You can find the results in [darwinfb_report](fuzzbench_reports/darwinfb_report/). To reproduce this, use [run_fuzzbench_experiment.sh](./run_fuzzbench_experiment.sh)

After contacting the authors, they pointed out that `-s` should be indeed disabled and that FuzzBench runs DARWIN using _per-seed mutations_ (`-p` flag is set); they do *not* recommend setting this flag, which was not part of the paper and worsens performance (we evaluate this in Experiment 3 below).

Thus, we follow the authors' recommendations and re-run this experiment with DARWIN configured as recommended by the authors (neither `-p` nor `-s` set). In our second run, we extend the evaluation to the full set of FuzzBench targets (we previously limited ourselves to seven targets where DARWIN performed best according to their evaluation) but exclude AFL 2.52b (the baseline for MOpt). The results of our second run can be found in the [full_report](fuzzbench_reports/full_report). To reproduce this, use [run_new_fuzzbench_experiment.sh](./run_new_fuzzbench_experiment.sh)


### Experiment 2: New Baseline
To test DARWIN's contribution, we replaced its weighting with a random selection with a constant reweight interval and noticed it did not perform significantly different than DARWIN itself. This implementation, `DARWIN-RAND`, provides a new baseline that allows to better judge DARWIN's contribution of a dynamically adapting mutation selection. We include this version of DARWIN in the reports of Experiment 1 (see the [full_report](fuzzbench_reports/full_report)).

### Experiment 3: Per-Seed Mutation Scheduling
We contacted the DARWIN authors regarding our experimental setup. They confirmed its correctness (including the removal of *-s*), but noted that the per-seed mutation scheduling, enabled by the *-p* flag, was disabled for the evaluation as it worsens performance. To confirm this, we separately evaluated DARWIN with per-seed mutation scheduling disabled<sup>1</sup>. The results can be found in the [preseed_report](fuzzbench_reports/preseed_report/). To reproduce this, use [run_preseed_compare_experiment.sh](./run_preseed_compare_experiment.sh).

## Setup
To reproduce our evaluation, follow these steps:

1. Clone this repository

   ```git clone https://github.com/fuzz-evaluator/DARWIN-eval.git```

2. Execute the `setup.sh` script
3. (Optional) Open a new tmux session

   ```tmux new -s darwin-eval```


4. To execute our default experiment, first copy the [patch_disable_perseed.patch](patch_disable_perseed.patch) into [fuzzbench](fuzzbench), apply it to disable the per-seed operations set by FuzzBench (make sure DARWIN's `fuzzer.py` neither uses `-p` nor `-s`), and then execute our `run_new_fuzzbench_experiment.sh` script
5. To execute our per-seed compare experiment execute the `run_preseed_compare_experiment.sh` script


The final results will be stored in `/opt/fuzzbench/fuzzbench-experiments/darwin-eval`. The runtime of the experiment is set to 24h and 10 trials -- for statistical significance we recommend a minimum of 10 trials. However, the experiment storage, the number of trials and the runtime can be adjusted in the `config.yaml` / `preseed_config.yaml`.

------

<sup>1</sup>Note that, due to a typo, this report is titled "preseed" and not "perseed".
