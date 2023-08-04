# Artifact Evaluation - DARWIN

This repository contains the FuzzBench setup and experiment configuration we use to reproduce the claims from [DARWIN (paper)](https://www.ndss-symposium.org/ndss-paper/darwin-survival-of-the-fittest-fuzzing-mutators/). In this repository we will guide through the setup of our environment so that you can reproduce our results. You can also find all FuzzBench reports [here](fuzzbench_reports). Please clone the repository and open the `index.html` to view the report. 

## Conducted Experiments
In order to reproduce the results from the paper, we conduct three different experiments:

1. Coverage:
We use DARWIN as implemented in [FuzzBench DARWIN](https://github.com/google/fuzzbench/tree/3cf599ade53f55eb149f018660820b5b50fd6067/fuzzers/darwin) to reproduce its results in terms of coverage, but disabled the *-s* flag as it appeared to enable unstable behavior. We compare it against the following competitors:
   * AFL 2.52b
   * AFL 2.55b
   * MOpt

2. New Baseline:
To test DARWIN's contribution, we replaced its weighting with a random selection with a constant reweight interval and noticed it did not perform worse than DARWIN itself. This implementation, `DARWIN-RAND`, provides a new baseline that allows to better judge DARWIN's contribution of a dynamically adapting mutation selection.

3. Per-Seed Mutation Scheduling:
We contacted the DARWIN authors regarding our experimental setup. They confirmed its correctness (including the removal of *-s*), but noted that the per-seed mutation scheduling, enabled by the *-p* flag, was disabled for the evaluation as it worsens performance. To confirm this, we separately evaluated DARWIN with per-seed mutation scheduling disabled<sup>1</sup>.

## Setup
To reproduce our evaluation, follow these steps:

1. Clone this repository

   ```git clone https://github.com/fuzz-evaluator/DARWIN-eval.git```

2. Execute the `setup.sh` script
3. (Optional) Open a new tmux session

   ```tmux new -s darwin-eval```


4. To execute the our default experiment execute the `run_fuzzbench_experiment.sh` script
5. To execute the our per-seed compare experiment execute the `run_preseed_compare_experiment.sh` script


The final results will be stored in `/opt/fuzzbench/fuzzbench-experiments/darwin-eval`. The runtime of the experiment is set to 24h and 10 trials -- for statistical significance we recommend a minimum of 10 trials. However, the experiment storage, the number of trials and the runtime can be adjusted in the `config.yaml` / `preseed_config.yaml`.

------

<sup>1</sup>Note that, due to a typo, this report is titled "preseed" and not "perseed".
