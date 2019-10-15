VERSION=0.5.0
ARCHNAME=inputter-$(VERSION)

ARCHDIR=archives/
ARCHFILES=\
	inputter.asm \
	inputter.com \
	apacker-com.cc \
	\
	timeset.asm \
	\
	doc/docmaker.php doc/document.php doc/README.html \
	doc/README \
	\
	makediff.php make.sh make-parallel.sh

inputter.com: inputter.asm apacker-com key.asm
	./make-parallel.sh inputter.asm inputter.com
	@echo
	@ls -al inputter.com
	@echo

apacker-com: apacker-com.cc
	g++ -o $@ $< -Wall -W -O3 -g -fomit-frame-pointer -fopenmp

include depfun.mak
