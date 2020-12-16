#!/bin/bash

outDir=/star/data01/pwg/sheppel/embed/out/
logDir=/star/data01/pwg/sheppel/embed/log/
schedDir=/star/data01/pwg/sheppel/embed/sched/
filelist=/star/u/sheppel/EmbeddingProcessor/scripts/embedding.list
workDir=`pwd`/..
packageName=embed_proc

star-submit-template -template ../xml/SubmitEmbeddingProcessor.xml -entities logDir=$logDir,filelist=$filelist,outDir=$outDir,schedDir=$schedDir,packageName=$packageName,workDir=$workDir
