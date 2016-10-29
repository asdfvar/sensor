Images = one_and_two_references.png                  \
         flops_graph.png                             \
         fraction_threshold_walking_to_bicycling.png \
         fraction_threshold_walking_to_jogging.png   \
         more_time_plots.png                         \
         ROC_walk_to_bike.png                        \
         ROC_walk_to_run.png

all: $(Images)
	pdflatex example.tex
	bibtex example

clean:
	rm -v example.pdf example.log example.out example.snm      \
        example.toc example.aux example.nav example.bbl example.blg \
        $(Images)

one_and_two_references.png: make_timing_plots.py
	python make_timing_plots.py

flops_graph.png: make_flop_bar_graph.py
	python make_flop_bar_graph.py
 
more_time_plots.png: make_timing_plots.py
	python make_timing_plots.py

fraction_threshold_walking_to_bicycling.png: make_graphs_walking_biking.py
	python make_graphs_walking_biking.py

fraction_threshold_walking_to_jogging.png: make_graphs_walking_running.py
	python make_graphs_walking_running.py

ROC_walk_to_bike.png: make_graphs_walking_biking.py
	python make_graphs_walking_biking.py

ROC_walk_to_run.png: make_graphs_walking_running.py
	python make_graphs_walking_running.py
