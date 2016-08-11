# Edge-Similarity Dense Subgraph (esDSG)

## How to run

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

## Result's format

### Predictions (.pred)

The following is an example of a `.pred` file. For each subgraph computed, the program outputs each of its real and predicted edges. The desciption of these edges contains: the _out_ edge, the _in_ edge, a indicator of the edge being real or predicted (`R` or `P`), and its edge-similarity value. Edges belonging to the same subgraph are printed together, and separated from different subgraphs by `----------`.

	hsa:146	D00607	R	0.914634
	hsa:146	D02237	P	0.914634
	----------
	hsa:3360	D01994	R	1
	...

### Extra data (.tsv)

The following is an example of a `.tsv` file. The first line contains the column names, followed by a number of rows. Each row details each subgraph computed: The number of _in_ nodes (`I`), _out_ nodes (`O`), total nodes (`V`), edges (`E`), missing/predicted edges (`M`), the density of the subgraph (`D`), the es-Density of the subgraph (`esDSG`), and the time (millisecond) where that subgraph was computed (`time`).

	I	O	V	E	M	D	esD	time
	20	11	31	105	115	7.0791	2.59637	789
	8	3	11	23	1	4.69486	2.86636	871
	6	5	11	28	2	5.11208	2.85893	943
	5	5	10	25	0	5	2.24565	1009
	...
