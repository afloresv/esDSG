# Edge-Similarity Dense Subgraph (esDSG)

How to run
---

First, compile using `make`, and create a folder for results called `r` (using `mkdir r`).

Now, the code can be executed directly from the `./run` executable. However, a simplified interface is provided.
Use the `run.sh` file instead to compute dense subgraphs on the datasets included. The sintax is as follows:

	./run.sh <dataset> <fold> <out_sim_threshold> <in_sim_threshold> <file_postfix>

Where:

1. `dataset` can be `nr`, `gpcr`, `e`, `ic`.
2. `fold` would indicate the fold number to be selected, between [0,9]. Use -1 to work with the complete dataset.
3. `out_sim_threshold` is a double between [0,1].
4. `in_sim_threshold` is a double between [0,1]
5. `file_postfix` is the file postfix for the result files.

For example, the call `./run.sh nr -1 0.1832 0.3684 80` will compute the dense subgraphs for the NR graph, using the complete dataset with the given thresholds for the similarity matrices. This will generate two files: `r/nr80.pred` and `r/nr80.tsv` containing the subgraphs computed and its predicted edges, and a TSV file containing details of those subgraphs.
