// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file sIP_distrib_N123.C
/// \brief Macro to plot the probability distrib. of signed Impact Parameter (2D) for b,c,lf jets for 1st, 2nd and 3rd largest IP. Uses the outputs of bjetTreeMerger.cxx
///
/// \author Clement Lotteau <clement.lotteau@cern.ch> IP2I

void sIP_distrib_N123()
{
    std::unique_ptr<TFile> myFile(TFile::Open("myFile.root"));
    TTree *mytree = myFile->Get<TTree>("bjet-tree-merger/myTree");

    // activating errors for all histograms
    TH1::SetDefaultSumw2();
    
    // creating the histogram for sIP (1st, 2nd, 3rd largest IP)
    TH1 *hist_sIP_lf_N1 = new TH1F("h1", "sIP_lf_N1", 400, -0.4, 0.4);
    TH1 *hist_sIP_c_N1 = new TH1F("h2", "sIP_c_N1", 400, -0.4, 0.4);
    TH1 *hist_sIP_b_N1 = new TH1F("h3", "sIP_b_N1", 400, -0.4, 0.4);

    TH1 *hist_sIP_lf_N2 = new TH1F("h4", "sIP_lf_N2", 400, -0.4, 0.4);
    TH1 *hist_sIP_c_N2 = new TH1F("h5", "sIP_c_N2", 400, -0.4, 0.4);
    TH1 *hist_sIP_b_N2 = new TH1F("h6", "sIP_b_N2", 400, -0.4, 0.4);

    TH1 *hist_sIP_lf_N3 = new TH1F("h7", "sIP_lf_N3", 400, -0.4, 0.4);
    TH1 *hist_sIP_c_N3 = new TH1F("h8", "sIP_c_N3", 400, -0.4, 0.4);
    TH1 *hist_sIP_b_N3 = new TH1F("h9", "sIP_b_N3", 400, -0.4, 0.4);

    int flavor;
    float signedIP2D[10];
    mytree->SetBranchAddress("mJetFlavor", &flavor);
    mytree->SetBranchAddress("mSignedIP2D", &signedIP2D);

    // Filling of the histograms with the sIP of the 1st, 2nd and 3rd largest IP (descending order: 0 = 1st largest IP)
    for (int i=0; i<mytree->GetEntries(); i++)
    {
        mytree->GetEntry(i);

        if (flavor==0 or flavor==3) // flavor: none or light flavor
        {
            hist_sIP_lf_N1->Fill(signedIP2D[0]);
            hist_sIP_lf_N2->Fill(signedIP2D[1]);
            hist_sIP_lf_N3->Fill(signedIP2D[2]);
        }
        if (flavor==1) // flavor: charm
        {
            hist_sIP_c_N1->Fill(signedIP2D[0]);
            hist_sIP_c_N2->Fill(signedIP2D[1]);
            hist_sIP_c_N3->Fill(signedIP2D[2]);
        }
        if (flavor==2) // flavor: beauty
        {
            hist_sIP_b_N1->Fill(signedIP2D[0]);
            hist_sIP_b_N2->Fill(signedIP2D[1]);
            hist_sIP_b_N3->Fill(signedIP2D[2]);
        }
        /*
        if (i==10000000) // limit on number of jets analysed
        {
            break;
        }
        */
        // printf("%d\n", i); // this line is to check if the code is running
    }

    // normalization of histograms
    Double_t factor = 1.;
    hist_sIP_b_N1->Scale(factor/hist_sIP_b_N1->GetEntries());
    hist_sIP_c_N1->Scale(factor/hist_sIP_c_N1->GetEntries());
    hist_sIP_lf_N1->Scale(factor/hist_sIP_lf_N1->GetEntries());
    hist_sIP_b_N2->Scale(factor/hist_sIP_b_N2->GetEntries());
    hist_sIP_c_N2->Scale(factor/hist_sIP_c_N2->GetEntries());
    hist_sIP_lf_N2->Scale(factor/hist_sIP_lf_N2->GetEntries());
    hist_sIP_b_N3->Scale(factor/hist_sIP_b_N3->GetEntries());
    hist_sIP_c_N3->Scale(factor/hist_sIP_c_N3->GetEntries());
    hist_sIP_lf_N3->Scale(factor/hist_sIP_lf_N3->GetEntries());

    // canvas creation for N1
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->cd();
    c1->SetLogy();
    // settings for plots
    hist_sIP_b_N1->SetMarkerStyle(20);
    hist_sIP_b_N1->SetMarkerSize(0.5);
    hist_sIP_b_N1->SetMarkerColor(2);
    hist_sIP_b_N1->SetLineColor(2);
    hist_sIP_b_N1->SetLineWidth(2);
    hist_sIP_b_N1->SetStats(0);
    hist_sIP_c_N1->SetMarkerStyle(20);
    hist_sIP_c_N1->SetMarkerSize(0.5);
    hist_sIP_c_N1->SetMarkerColor(3);
    hist_sIP_c_N1->SetLineColor(3);
    hist_sIP_c_N1->SetLineWidth(2);
    hist_sIP_c_N1->SetStats(0);
    hist_sIP_lf_N1->SetMarkerStyle(20);
    hist_sIP_lf_N1->SetMarkerSize(0.5);
    hist_sIP_lf_N1->SetMarkerColor(4);
    hist_sIP_lf_N1->SetLineWidth(2);
    hist_sIP_lf_N1->SetLineColor(4);
    hist_sIP_lf_N1->SetStats(0);
    // drawing histograms
    hist_sIP_b_N1->Draw();
    hist_sIP_c_N1->Draw("SAME");
    hist_sIP_lf_N1->Draw("SAME");
    // set title for plot, x and y axis
    hist_sIP_b_N1->SetTitle("sIP distribution for b-jet tagger - 1st largest IP");
    hist_sIP_b_N1->GetXaxis()->SetTitle("2D signed impact parameter (sIP) (cm)");
    hist_sIP_b_N1->GetYaxis()->SetTitle("Normalized counts");
    // set legend
    TLegend *legend_N1 = new TLegend(0.2,0.55,0.4,0.7);
    legend_N1->AddEntry(hist_sIP_b_N1,"b");
    legend_N1->AddEntry(hist_sIP_c_N1,"c");
    legend_N1->AddEntry(hist_sIP_lf_N1,"lf");
    legend_N1->SetBorderSize(0);
    legend_N1->SetTextSize(0.045);
    legend_N1->Draw("AP");
    // save the distribution for N1
    c1->SaveAs("sIP_distrib_N1.pdf");
    
    // canvas creation for N2
    TCanvas *c2 = new TCanvas("c2","c2");
    c2->cd();
    c2->SetLogy();
    // settings for plots
    hist_sIP_b_N2->SetMarkerStyle(20);
    hist_sIP_b_N2->SetMarkerSize(0.5);
    hist_sIP_b_N2->SetMarkerColor(2);
    hist_sIP_b_N2->SetLineWidth(2);
    hist_sIP_b_N2->SetLineColor(2);
    hist_sIP_b_N2->SetStats(0);
    hist_sIP_c_N2->SetMarkerStyle(20);
    hist_sIP_c_N2->SetMarkerSize(0.5);
    hist_sIP_c_N2->SetMarkerColor(3);
    hist_sIP_c_N2->SetLineWidth(2);
    hist_sIP_c_N2->SetLineColor(3);
    hist_sIP_c_N2->SetStats(0);
    hist_sIP_lf_N2->SetMarkerStyle(20);
    hist_sIP_lf_N2->SetMarkerSize(0.5);
    hist_sIP_lf_N2->SetMarkerColor(4);
    hist_sIP_lf_N2->SetLineWidth(2);
    hist_sIP_lf_N2->SetLineColor(4);
    hist_sIP_lf_N2->SetStats(0);
    // drawing histograms
    hist_sIP_b_N2->Draw();
    hist_sIP_c_N2->Draw("SAME");
    hist_sIP_lf_N2->Draw("SAME");
    // set title for plot, x and y axis
    hist_sIP_b_N2->SetTitle("sIP distribution for b-jet tagger - 2nd largest IP");
    hist_sIP_b_N2->GetXaxis()->SetTitle("2D signed impact parameter (sIP) (cm)");
    hist_sIP_b_N2->GetYaxis()->SetTitle("Normalized counts");
    // set legend
    TLegend *legend_N2 = new TLegend(0.2,0.55,0.4,0.7);
    legend_N2->AddEntry(hist_sIP_b_N2,"b");
    legend_N2->AddEntry(hist_sIP_c_N2,"c");
    legend_N2->AddEntry(hist_sIP_lf_N2,"lf");
    legend_N2->SetBorderSize(0);
    legend_N2->SetTextSize(0.045);
    legend_N2->Draw("AP");
    // save the distribution for N2
    c2->SaveAs("sIP_distrib_N2.pdf");

    // canvas creation for N3
    TCanvas *c3 = new TCanvas("c3","c3");
    c3->cd();
    c3->SetLogy();
    // settings for plots
    hist_sIP_b_N3->SetMarkerStyle(20);
    hist_sIP_b_N3->SetMarkerSize(0.5);
    hist_sIP_b_N3->SetMarkerColor(2);
    hist_sIP_b_N3->SetLineColor(2);
    hist_sIP_b_N3->SetLineWidth(2);
    hist_sIP_b_N3->SetStats(0);
    hist_sIP_c_N3->SetMarkerStyle(20);
    hist_sIP_c_N3->SetMarkerSize(0.5);
    hist_sIP_c_N3->SetMarkerColor(3);
    hist_sIP_c_N3->SetLineColor(3);
    hist_sIP_c_N3->SetLineWidth(2);
    hist_sIP_c_N3->SetStats(0);
    hist_sIP_lf_N3->SetMarkerStyle(20);
    hist_sIP_lf_N3->SetMarkerSize(0.5);
    hist_sIP_lf_N3->SetMarkerColor(4);
    hist_sIP_lf_N3->SetLineColor(4);
    hist_sIP_lf_N3->SetLineWidth(2);
    hist_sIP_lf_N3->SetStats(0);
    // drawing histograms
    hist_sIP_b_N3->Draw();
    hist_sIP_c_N3->Draw("SAME");
    hist_sIP_lf_N3->Draw("SAME");
    // set title for plot, x and y axis
    hist_sIP_b_N3->SetTitle("sIP distribution for b-jet tagger - 3rd largest IP");
    hist_sIP_b_N3->GetXaxis()->SetTitle("2D signed impact parameter (sIP) (cm)");
    hist_sIP_b_N3->GetYaxis()->SetTitle("Normalized counts");
    // set legend
    TLegend *legend_N3 = new TLegend(0.2,0.55,0.4,0.7);
    legend_N3->AddEntry(hist_sIP_b_N3,"b");
    legend_N3->AddEntry(hist_sIP_c_N3,"c");
    legend_N3->AddEntry(hist_sIP_lf_N3,"lf");
    legend_N3->SetBorderSize(0);
    legend_N3->SetTextSize(0.045);
    legend_N3->Draw("AP");
    // save the distribution for N3
    c3->SaveAs("sIP_distrib_N3.pdf");
}