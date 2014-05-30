TEMPLATE = subdirs

SUBDIRS += LemmaLib
CONFIG(run_lib_tests) {
SUBDIRS += LemmaLibTests
 }
else { 
}

CONFIG += ordered
