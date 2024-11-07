# Root macros for b-jet tagging using track counting method

These macros use the ```.root``` output of the ```O2Physics``` task ```bjetTreeMerger```. This task merges the TTrees created with the task ```bjetTreeCreator``` and, unlike ```bjetTreeCreator```, ```bjetTreeMerger``` cannot be used on the Hyperloop - only locally.

```N123``` is written in the names of the macros because they were created to compare different distribution (efficiency, purity, sIP) for the 3 tracks with the largest Impact Parameter.

## First macro: ```sIP_distrib_N123.C```

This macro plots the probability distributions of the 2D signed Impact Parameter (sIP) for b,c and lf jets for the tracks with the highest IP (1st, 2nd and 3rd)


## Second macro: ```sIP_eff_mistag_jet_pT_N123.C```

This macro computes and plots the efficiency of the b-jet tagging and the mmistagging rates for c- and lightflavor-jets for the three higest IP against the jet transverse momentum pT. The efficiency of the tagger is the number of b-jets tagged as b over the total number of b-jets. The mistagging rate of the tagger is the number of c- or lf-jets tagged as b over the total number of c- or lf-jets. Binomial errors were used.