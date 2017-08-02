default: pdf

compile:
	xelatex scl.tex > /dev/null
	xelatex scl.tex > /dev/null

clean:
	rm -rf scl.aux scl.log scl.toc

clean_all: clean
	rm -rf scl.pdf

pdf: compile clean
