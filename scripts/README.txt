Contents:
logfiles_to_TTree.py - converts log files from local directory into a .root file with desired information
plot1DHist.C - plots a 1D histogram from metadata_TTree.root, currently plots the time per number of events
plot2DColzHist.C - plots a 2D histogram as a heatmap, currently plots the total job time by number of events processed
plotCvsA.C - plots copy time vs. add info time
plotJvsA.C - plots job time vs. add info time for job time > 2500s
plotJvsC.C - plots job time vs. copy time for job time > 2500s
plotJvsM.C - plots job time vs. merge time for job time > 2500s
plotLJTJ.C - plots (long jobs)/(total jobs) by day
plotLJTJHrly.C - plots (long jobs)/(total jobs) by hour
plotLJTJSame.C - plots long jobs by day and total jobs by day on the same graph
plotLJTJHrlySame.C - plots long jobs by hour and total jobs by hour on the same graph
plotLSCopy.C - plots copy times for jobs longer than 30 mins and for jobs less than 30mins on the same graph
plotLSEvents.C - plots events processed for jobs longer than 30 mins and for jobs less than 30 mins on the same graph
plotMvsA.C - plots merge time vs. add info time
plotMvsC.C - plots merge time vs. copy time
plotTProfile.C - plots a 2D histogram with error bars, currently plots time per event processed by machine number
plotTimes.C - plots the distribution of times for all three steps of process as well as total job time on the same 1D plot
