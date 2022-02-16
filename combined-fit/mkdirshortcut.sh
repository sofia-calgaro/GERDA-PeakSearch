#! /bin/bash

read -p " Name of the new analysis directory: " new_dir

mkdir JsonFiles/$new_dir
mkdir MarginalizedPDF/$new_dir
mkdir MarginalizedROOT/$new_dir
mkdir Plot/$new_dir
mkdir Priors\&Posteriors/$new_dir
