TEX = pdflatex
FIGS = one_and_two_references.png                  \
       more_time_plots.png                         \
       fraction_threshold_walking_to_bicycling.png \
       fraction_threshold_walking_to_jogging.png   \
       ROC_walk_to_bike.png                        \
       ROC_walk_to_run.png

all: $(FIGS)
	$(TEX) paper.tex
	bibtex paper

clean:
	rm *.aux *.log *.pdf *.blg *.bbl *~ $(FIGS)

one_and_two_references.png: make_timing_plots.py
	./make_timing_plots.py

more_time_plots.png: make_timing_plots.py
	./make_timing_plots.py

fraction_threshold_walking_to_bicycling.png: make_graphs_walking_biking.py
	./make_graphs_walking_biking.py

fraction_threshold_walking_to_jogging.png: make_graphs_walking_running.py
	./make_graphs_walking_running.py

ROC_walk_to_bike.png: make_graphs_walking_biking.py
	./make_graphs_walking_biking.py

ROC_walk_to_run.png: make_graphs_walking_running.py
	./make_graphs_walking_running.py
