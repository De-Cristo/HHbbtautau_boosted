#!/bin/bash

cd nanoaod_base_analysis #To update the main code
git pull origin py3 #To update the main code
cd ..
source setup.sh
law index --verbose #If we have added some tasks in our user code.
voms-proxy-init --rfc --voms cms -valid 192:00 #To identify yourself with a valid proxy in case you don't have it.


law run PreprocessRDF --version prod_test --category-name base --config-name run3_2022_preEE_licheng --dataset-name VBFHHto2B2Tau_CV-1_C2V-1_C3-1 --modules-file HtautauMassRDF --workers 4 --branch -1 --max-runtime 4h --workflow local --keep-and-drop-file run3_keep_and_drop_file_test_licheng --transfer-logs true

law run PreprocessRDF --version prod_test --category-name base --config-name run3_2022_preEE_licheng --dataset-name VBFHHto2B2Tau_CV-1_C2V-1_C3-1 --modules-file HtautauMass --workers 4 --branch 0 --max-runtime 4h --workflow local --keep-and-drop-file run3_keep_and_drop_file_test_licheng --transfer-logs true

law run PreCounter --version prod_test --config-name run3_2022_preEE_licheng --dataset-name VBFHHto2B2Tau_CV-1_C2V-1_C3-1 --workers 10 --branch -1 --max-runtime 4h --workflow htcondor

law run PreprocessRDF --version prod_test --category-name base --config-name run3_2022_preEE_licheng --dataset-name VBFHHto2B2Tau_CV-1_C2V-1_C3-1 --modules-file pnet_licheng --workers 4 --branch -1 --max-runtime 4h --workflow htcondor --keep-and-drop-file run3_keep_and_drop_file_test_licheng --transfer-logs true

law run PreprocessRDF --version prod_test --category-name base --config-name run3_2022_preEE_licheng --dataset-name VBFHHto2B2Tau_CV-m0p962_C2V-0p959_C3-m1p43 --modules-file pnet_licheng --max-runtime 4h --workflow htcondor --keep-and-drop-file run3_keep_and_drop_file_test_licheng

law run Categorization --version prod_test --category-name boosted_dummy --config-name run3_2022_preEE_licheng --dataset-name VBFHHto2B2Tau_CV-1_C2V-1_C3-1 --workflow htcondor --keep-and-drop-file run3_keep_and_drop_file_test_licheng --feature-modules-file pnet_cat_licheng --transfer-logs true

rm -rfv nanoaod_base_analysis/data/tmp/*
rm -rfv nanoaod_base_analysis/data/jobs/*
rm -rfv nanoaod_base_analysis/data/store/*

