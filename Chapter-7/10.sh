# **
# Let a and b denote object modules or static libraries in the current directory
# and let a->b denote that a depends on b, in the sense that b defines a symbol
# that is referenced by a. For each of the following scenarios, show the minimal
# command line (i.e., one with the least number of object file and library
# arguments) that will allow the static linker to resolve all symbol references.
#
#  A. p.o -> libx.a -> p.o
#  B. p.o -> libx.a -> liby.a and liby.a -> libx.a
#  B. p.o -> libx.a -> liby.a -> libz.a and liby.a -> libx.a -> libz.a

gcc p.o libx.a p.o

gcc p.o libx.a liby.a libx.a

gcc p.o libx.a liby.a libx.a libz.a
