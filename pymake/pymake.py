#!/usr/bin/env python2.7
import os
import sys
import sets

# Global Variables
PROGRAM_NAME = os.path.basename(sys.argv[0])
file_str = ''               # Path to Makefile
build_str = ''              # Name of build rule within Makefile
SUBSTITUTIONS = {}          # Dictionary of substitution strings
DEPENDENCIES = {}
RULES = {}


# GRAPH FOR KEEPING TRACK OF MAKEFILE STUFF
class mfNode(object):
    def __init__(self, target):
        #A node object, which holds the information for each build target     
        self.target = target
        self.dependencies = DEPENDENCIES[target]
        self.rules = RULES[target]

class mfGraph(object):

    def __init__(self):
        self.nodes = {}
        for key in RULES:
            self.nodes[key] = mfNode(key)

    def makeDepends(self, target):
        # Check if all of the dependencies are present in the local directory
        tmpNode = self.nodes[target]
        for d in tmpNode.dependencies:
            if not os.path.isfile(d):
                print "Dependency: ", d, "Not Installed"
                if d in self.nodes:
                    print "Dependency in build instruction"
                    self.makeDepends(d)
                else:
                    error("ERROR: Dependency {}, for target {}, not found locally or as build target".format(d, target))
        print "ALL DEPENDENCIES FOR ", target, "INSTALLED... RUNNING COMMANDS"
        for c in tmpNode.rules:
            print c
            os.system(c)
  

    def build(self, target):
        if target in self.nodes:
            self.makeDepends(target)

        else:
            error("ERROR: Build Target Not Found")           




# Functions
def error(message, exit_code=1):
    print >>sys.stderr, message
    sys.exit(exit_code)

def usage(exit_code=0):
    error('''Usage: {} <Makefile_Path> <Build_Selection>Options:
    Makefile_Path - relative or absolute path to the makefile
    Build_Selection - The program or set of programs to be built\n'''
    .format(PROGRAM_NAME), exit_code)

def makeSubs():

    for key in SUBSTITUTIONS:
        for target in DEPENDENCIES:
            depends = DEPENDENCIES[target]
            for i in range(0, len(depends)):
                if depends[i] == key:
                   depends[i] = SUBSTITUTIONS[key]

            DEPENDENCIES[target] = depends

        for target in RULES:
            ruleList = RULES[target]
            for i in range(0, len(ruleList)):
                ruleList[i] = ruleList[i].replace(key,SUBSTITUTIONS[key], 10)
                ruleList[i] = ruleList[i].replace('$@',target, 10)
                ruleList[i] = ruleList[i].replace('$^',' '.join(DEPENDENCIES[target]), 10)
            RULES[target] = ruleList


def getBuilds(buildStrings):
    target = ""
    dependencies = []
    tmpRules = []
    for l in buildStrings:
        l = l.strip(' \t\n\r')

        if len(l.split(':')) == 2:
            if target != "":
                RULES[target] = tmpRules
                tmpRules = []
            target, dependencies = l.split(':')
            target = target.strip(' \t\n\r')          
            dependencies = dependencies.strip(' \t\n\r')
            DEPENDENCIES[target] = dependencies.split()

        else:
            tmpRules.extend([l])

def getSubs(subStrings):
    for l in subStrings:
        key, value = l.split('=', 1)
        SUBSTITUTIONS['$('+key.strip(' \t\n\r')+')'] = value.strip(' \t\n\r')

def formatFile(pathStr):
    subs = []
    builds = []
    with open(pathStr) as fileContents:
        for l in fileContents:
            # Delete Commented Lines
            if(l[0] == '#') or (l[0] == '\n'):
                continue
            else:
                # If the line does not have a colon seperator in the middle, or a tab at the beginning, it is a substitution rule
                if(l[0] != '\t') and (len(l.split(':')) != 2):
                    subs.append(l)
                else:
                    builds.append(l)

    return subs, builds
            
def getFile(pathStr):
    subStrs, buildStrs = formatFile(pathStr)
    getSubs(subStrs)
    getBuilds(buildStrs)
    makeSubs()




if __name__ == "__main__":

    #Process the Arguments to pymake.py
    args = sys.argv
    if len(args) == 3:
        make_str = args[1]
        build_str = args[2]
        if not os.path.isfile(make_str):
            error("ERROR: Makefile not found. Check first argument")
        else:
            getFile(make_str)

        graph = mfGraph()
        graph.build(build_str)


    else:
        usage()

 










