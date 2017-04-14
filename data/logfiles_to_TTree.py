import os
import ROOT
import numpy as np
from datetime import datetime

os.chdir('log_files')

#File parsing functions

#Global list declarations
entryList = []
entry_builder = []
masterList = []
newintName = 0

#Returns line without excess string info
def getLine(line, junk):
	newLine = line.split(junk)
	line = newLine[1]
	if "\n" in line:
		newLine = line.split('\n')
		line = newLine[0]
	return line

#Returns time values
def getTimes(timePile):
	newTimePile = []
	counter = 0
	
	t_total = str(int(timePile[3])-int(timePile[0]))
	t_copy = str(int(timePile[3])-int(timePile[2]))
	t_merge = str(int(timePile[1])-int(timePile[0]))
	t_addInfo = str(int(timePile[2])-int(timePile[1]))
	newTimePile.append(t_total)
	newTimePile.append(t_copy)
	newTimePile.append(t_merge)
	newTimePile.append(t_addInfo)
	
	return newTimePile

def getName(name):
	if "sdsc" in name:
		return 1;
	else:
		return 0;
	

#Class definitions
class Entry:
	def __init__(self, name, intName, events, t_total, t_copy, t_merge, t_addInfo, time):
		self.name = name
		self.intName = intName
		self.events = events
		self.t_total = t_total
		self.t_copy = t_copy
		self.t_merge = t_merge
		self.t_addInfo = t_addInfo
		self.TperE = float(t_total)/float(events)
		self.TimeStamp = time
		
#Parse through log files, create Entry objects
for file in os.listdir(os.curdir):
	try:
		if file.endswith('.out'):
			timePile=[]
			dataCheck=[]
			curfile = open(file,'r')
			for line in curfile:
				if '[merge wrapper] host: ' in line:
					line = getLine(line, '[merge wrapper] host: ')
					dataCheck.append(line)
				if 't before mergeScript.C' in line:
					line = getLine(line, '[merge wrapper] t before mergeScript.C: ')
					timePile.append(line)
				if '[merge] Merged Entries: ' in line:
					line = getLine(line, '[merge] Merged Entries: ')
					dataCheck.append(line)
				if '[merge wrapper] t before addBranches.C: ' in line:
					line = getLine(line, '[merge wrapper] t before addBranches.C: ')
					timePile.append(line)
				if '[merge wrapper] t after addBranches.C: ' in line:
					line = getLine(line, '[merge wrapper] t after addBranches.C: ')
					timePile.append(line)
				if '[merge wrapper] t after lcg-cp: ' in line:
					line = getLine(line, '[merge wrapper] t after lcg-cp: ')
					timePile.append(line)
			if len(timePile) == 4 and len(dataCheck) == 2:
				entry_builder = []
				for i in dataCheck:
					entry_builder.append(i)
					
				for j in getTimes(timePile):
					entry_builder.append(j)
				
				if entry_builder[0] not in masterList:
					masterList.append(entry_builder[0])
				newintName = masterList.index(entry_builder[0])

				newEntry = Entry(entry_builder[0], newintName, entry_builder[1], entry_builder[2], entry_builder[3], entry_builder[4], entry_builder[5], float(timePile[0]))
				entryList.append(newEntry)
			else:
				pass		
	except:
		pass

#Global array Definitions
intNames_arr = np.zeros(1, dtype = int)
days_arr = np.zeros(1, dtype = int)
months_arr = np.zeros(1, dtype = int)
years_arr = np.zeros(1, dtype = int)
events_arr = np.zeros(1, dtype = float)
t_totals_arr = np.zeros(1, dtype = float)
t_copies_arr = np.zeros(1, dtype = float)
t_merges_arr = np.zeros(1, dtype = float)
t_addInfos_arr = np.zeros(1, dtype = float)
TperEs_arr = np.zeros(1, dtype = float)
isSDSC_arr = np.zeros(1, dtype = int)

#TFile and TTree object pointer declarations
f = ROOT.TFile("metadata_TTree.root","recreate")
t = ROOT.TTree("t","Entries")

#Build TTree
def build_TTree():
	t.Branch('ComputerNumber', intNames_arr, "ComputerNumber/I")
	t.Branch('Day', days_arr, "Day/I")
	t.Branch('Month', months_arr, "Month/I")
	t.Branch('Year', years_arr, "Year/I")
	t.Branch('EventsProcessed', events_arr, "EventsProcessed/D")
	t.Branch('JobTime', t_totals_arr, "JobTime/D")
	t.Branch('CopyTime', t_copies_arr, "CopyTime/D")
	t.Branch('MergeTime', t_merges_arr, "MergeTime/D")
	t.Branch('AddInfoTime', t_addInfos_arr, "AddInfoTime/D")
	t.Branch('TimePerEvent', TperEs_arr, "TimePerEvent/D")
	t.Branch('isSDSC', isSDSC_arr, "isSDSC/I")

#Write TTree
def write_TTree():
	for entry in entryList:
		dt = datetime.fromtimestamp(entry.TimeStamp)
		intNames_arr[0] = entry.intName
		days_arr[0] = dt.day
		months_arr[0] = dt.month
		years_arr[0] = dt.year
		events_arr[0] = entry.events
		t_totals_arr[0] = entry.t_total
		t_copies_arr[0] = entry.t_copy
		t_merges_arr[0] = entry.t_merge
		t_addInfos_arr[0] = entry.t_addInfo
		TperEs_arr[0] = entry.TperE
		isSDSC_arr[0] = getName(entry.name)
		
		t.Fill()
	return

#Using functions defined above, build TTree
build_TTree()
write_TTree()

#Write to TFile and close
f.Write()
f.Close()
