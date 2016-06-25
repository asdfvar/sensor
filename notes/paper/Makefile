TEX = pdflatex
FIGS = one_and_two_references.png \
       more_time_plots.png

all: $(FIGS)
	$(TEX) paper.tex
	bibtex paper

clean:
	rm *.aux *.log *.pdf *.blg *.bbl *~ one_and_two_references.png more_time_plots.png

one_and_two_references.png: make_timing_plots.py
	./make_timing_plots.py

more_time_plots.png: make_timing_plots.py
	./make_timing_plots.py
