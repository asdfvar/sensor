TEX = pdflatex

all: one_and_two_references.png
	$(TEX) paper.tex
	bibtex paper

clean:
	rm *.aux *.log *.pdf *.blg *.bbl *~ one_and_two_references.png

one_and_two_references.png: make_timing_plots.py
	./make_timing_plots.py
