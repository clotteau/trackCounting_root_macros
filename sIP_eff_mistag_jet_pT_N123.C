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

/// \file sIP_eff_mistag_jet_pT_N123.C
/// \brief Macro to plot the efficiency of b tagging with signed Impact Parameter (2D) and mistagging rates of c-lf jets vs. jet pT for 1st, 2nd and 3rd largest IP. Uses the outputs of bjetTreeMerger.cxx
///
/// \author Clement Lotteau <clement.lotteau@cern.ch> IP2I

void sIP_eff_mistag_jet_pT_N123()
{
    std::unique_ptr<TFile> myFile(TFile::Open("myFile.root"));
    TTree *mytree = myFile->Get<TTree>("bjet-tree-merger/myTree");

    // activating errors for all histograms
    TH1::SetDefaultSumw2();

    // creating the histograms for jet pT and sIP (1st, 2nd, 3rd largest IP)
    TH2D *hist_jetpt_sIP_lf_N1 = new TH2D("h1", "jetpt_sIP_lf_N1", 195, 5, 200, 400, -0.4, 0.4);
    TH2D *hist_jetpt_sIP_c_N1 = new TH2D("h2", "jetpt_sIP_c_N1", 195, 5, 200, 400, -0.4, 0.4);
    TH2D *hist_jetpt_sIP_b_N1 = new TH2D("h3", "jetpt_sIP_b_N1", 195, 5, 200, 400, -0.4, 0.4);

    TH2D *hist_jetpt_sIP_lf_N2 = new TH2D("h4", "jetpt_sIP_lf_N2", 195, 5, 200, 400, -0.4, 0.4);
    TH2D *hist_jetpt_sIP_c_N2 = new TH2D("h5", "jetpt_sIP_c_N2", 195, 5, 200, 400, -0.4, 0.4);
    TH2D *hist_jetpt_sIP_b_N2 = new TH2D("h6", "jetpt_sIP_b_N2", 195, 5, 200, 400, -0.4, 0.4);

    TH2D *hist_jetpt_sIP_lf_N3 = new TH2D("h7", "jetpt_sIP_lf_N2=3", 195, 5, 200, 400, -0.4, 0.4);
    TH2D *hist_jetpt_sIP_c_N3 = new TH2D("h8", "jetpt_sIP_c_N3", 195, 5, 200, 400, -0.4, 0.4);
    TH2D *hist_jetpt_sIP_b_N3 = new TH2D("h9", "jetpt_sIP_b_N3", 195, 5, 200, 400, -0.4, 0.4);

    int flavor;
    float signedIP2D[10];
    float jetpt;
    mytree->SetBranchAddress("mJetFlavor", &flavor);
    mytree->SetBranchAddress("mSignedIP2D", &signedIP2D);
    mytree->SetBranchAddress("mJetpT", &jetpt);
    
    // Filling of the histograms with jet pT and sIP of the 1st, 2nd and 3rd largest IP (descending order: 0 = 1st largest IP)
    for (int i=0; i<mytree->GetEntries(); i++)
    {
        mytree->GetEntry(i);

        if (flavor==0 or flavor==3) // flavor: none or light flavor
        {
            hist_jetpt_sIP_lf_N1->Fill(jetpt,signedIP2D[0]);
            hist_jetpt_sIP_lf_N2->Fill(jetpt,signedIP2D[1]);
            hist_jetpt_sIP_lf_N3->Fill(jetpt,signedIP2D[2]);
        }
        if (flavor==1) // flavor: charm
        {
            hist_jetpt_sIP_c_N1->Fill(jetpt,signedIP2D[0]);
            hist_jetpt_sIP_c_N2->Fill(jetpt,signedIP2D[1]);
            hist_jetpt_sIP_c_N3->Fill(jetpt,signedIP2D[2]);
        }
        if (flavor==2) // flavor: beauty
        {
            hist_jetpt_sIP_b_N1->Fill(jetpt,signedIP2D[0]);
            hist_jetpt_sIP_b_N2->Fill(jetpt,signedIP2D[1]);
            hist_jetpt_sIP_b_N3->Fill(jetpt,signedIP2D[2]);
        }
        /*
        if (i==10000000) // limit on number of jets analysed
        {
            break;
        }
        */
        // printf("%d\n", i); // this line is to check if the code is running
    }
    
    // setting sIP threshold (cm) you can adjust the tagger working point here
    double sIPmin = 0.008;

    //creating projections to compute efficiency N1
    TH1D *projected_b_N1 = hist_jetpt_sIP_b_N1->ProjectionX("projected_b_N1", hist_jetpt_sIP_b_N1->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_b_N1_full = hist_jetpt_sIP_b_N1->ProjectionX("projected_b_N1_full", 0, -1);
    TH1D *efficiency_N1 = (TH1D*) projected_b_N1->Clone("efficiency_N1");
    efficiency_N1->Reset();
    efficiency_N1->Divide(projected_b_N1,projected_b_N1_full,1,1,"B");
    //creating projections to compute c mistagging N1
    TH1D *projected_c_N1 = hist_jetpt_sIP_c_N1->ProjectionX("projected_c_N1", hist_jetpt_sIP_c_N1->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_c_N1_full = hist_jetpt_sIP_c_N1->ProjectionX("projected_c_N1_full", 0, -1);
    TH1D *mistagging_c_N1 = (TH1D*) projected_c_N1->Clone("mistagging_c_N1");
    mistagging_c_N1->Reset();
    mistagging_c_N1->Divide(projected_c_N1,projected_c_N1_full,1,1,"B");
    //creating projections to compute lf mistagging N1
    TH1D *projected_lf_N1 = hist_jetpt_sIP_lf_N1->ProjectionX("projected_lf_N1", hist_jetpt_sIP_lf_N1->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_lf_N1_full = hist_jetpt_sIP_lf_N1->ProjectionX("projected_lf_N1_full", 0, -1);
    TH1D *mistagging_lf_N1 = (TH1D*) projected_lf_N1->Clone("mistagging_lf_N1");
    mistagging_lf_N1->Reset();
    mistagging_lf_N1->Divide(projected_lf_N1,projected_lf_N1_full,1,1,"B");

    //creating projections to compute efficiency N2
    TH1D *projected_b_N2 = hist_jetpt_sIP_b_N2->ProjectionX("projected_b_N2", hist_jetpt_sIP_b_N2->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_b_N2_full = hist_jetpt_sIP_b_N2->ProjectionX("projected_b_N2_full", 0, -1);
    TH1D *efficiency_N2 = (TH1D*) projected_b_N2->Clone("efficiency_N2");
    efficiency_N2->Reset();
    efficiency_N2->Divide(projected_b_N2,projected_b_N2_full,1,1,"B");
    //creating projections to compute c mistagging N2
    TH1D *projected_c_N2 = hist_jetpt_sIP_c_N2->ProjectionX("projected_c_N2", hist_jetpt_sIP_c_N2->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_c_N2_full = hist_jetpt_sIP_c_N2->ProjectionX("projected_c_N2_full", 0, -1);
    TH1D *mistagging_c_N2 = (TH1D*) projected_c_N2->Clone("mistagging_c_N2");
    mistagging_c_N2->Reset();
    mistagging_c_N2->Divide(projected_c_N2,projected_c_N2_full,1,1,"B");
    //creating projections to compute lf mistagging N2
    TH1D *projected_lf_N2 = hist_jetpt_sIP_lf_N2->ProjectionX("projected_lf_N2", hist_jetpt_sIP_lf_N2->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_lf_N2_full = hist_jetpt_sIP_lf_N2->ProjectionX("projected_lf_N2_full", 0, -1);
    TH1D *mistagging_lf_N2 = (TH1D*) projected_lf_N2->Clone("mistagging_lf_N2");
    mistagging_lf_N2->Reset();
    mistagging_lf_N2->Divide(projected_lf_N2,projected_lf_N2_full,1,1,"B");

    //creating projections to compute efficiency N3
    TH1D *projected_b_N3 = hist_jetpt_sIP_b_N3->ProjectionX("projected_b_N3", hist_jetpt_sIP_b_N3->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_b_N3_full = hist_jetpt_sIP_b_N3->ProjectionX("projected_b_N3_full", 0, -1);
    TH1D *efficiency_N3 = (TH1D*) projected_b_N3->Clone("efficiency_N3");
    efficiency_N3->Reset();
    efficiency_N3->Divide(projected_b_N3,projected_b_N3_full,1,1,"B");
    //creating projections to compute c mistagging N3
    TH1D *projected_c_N3 = hist_jetpt_sIP_c_N3->ProjectionX("projected_c_N3", hist_jetpt_sIP_c_N3->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_c_N3_full = hist_jetpt_sIP_c_N3->ProjectionX("projected_c_N3_full", 0, -1);
    TH1D *mistagging_c_N3 = (TH1D*) projected_c_N3->Clone("mistagging_c_N3");
    mistagging_c_N3->Reset();
    mistagging_c_N3->Divide(projected_c_N3,projected_c_N3_full,1,1,"B");
    //creating projections to compute lf mistagging N3
    TH1D *projected_lf_N3 = hist_jetpt_sIP_lf_N3->ProjectionX("projected_lf_N3", hist_jetpt_sIP_lf_N3->GetYaxis()->FindBin(sIPmin), -1);
    TH1D *projected_lf_N3_full = hist_jetpt_sIP_lf_N3->ProjectionX("projected_lf_N3_full", 0, -1);
    TH1D *mistagging_lf_N3 = (TH1D*) projected_lf_N3->Clone("mistagging_lf_N3");
    mistagging_lf_N3->Reset();
    mistagging_lf_N3->Divide(projected_lf_N3,projected_lf_N3_full,1,1,"B");

    // canvas creation for N1
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->cd();
    // settings for plots
    efficiency_N1->SetMarkerStyle(20);
    efficiency_N1->SetMarkerSize(0.5);
    efficiency_N1->SetMarkerColor(2);
    efficiency_N1->SetLineColor(2);
    efficiency_N1->SetLineWidth(2);
    efficiency_N1->SetStats(0);
    mistagging_c_N1->SetMarkerStyle(20);
    mistagging_c_N1->SetMarkerSize(0.5);
    mistagging_c_N1->SetMarkerColor(3);
    mistagging_c_N1->SetLineColor(3);
    mistagging_c_N1->SetLineWidth(2);
    mistagging_c_N1->SetStats(0);
    mistagging_lf_N1->SetMarkerStyle(20);
    mistagging_lf_N1->SetMarkerSize(0.5);
    mistagging_lf_N1->SetMarkerColor(4);
    mistagging_lf_N1->SetLineWidth(2);
    mistagging_lf_N1->SetLineColor(4);
    mistagging_lf_N1->SetStats(0);
    // drawing histograms
    efficiency_N1->Draw();
    mistagging_c_N1->Draw("SAME");
    mistagging_lf_N1->Draw("SAME");
    // set title for plot, x and y axis
    efficiency_N1->SetTitle("Efficiency and mistagging rates of sIP b-jet tagger - 1st largest IP");
    efficiency_N1->GetXaxis()->SetTitle("jet pT (GeV/c)");
    efficiency_N1->GetYaxis()->SetTitle("Efficiency and mistagging rates");
    // set legend
    TLegend *legend_N1 = new TLegend(0.13,0.85,0.3,0.75);
    legend_N1->AddEntry(efficiency_N1,"Efficiency");
    legend_N1->AddEntry(mistagging_c_N1,"Mistagging c");
    legend_N1->AddEntry(mistagging_lf_N1,"Mistagging lf");
    legend_N1->SetBorderSize(0);
    legend_N1->SetTextSize(0.03);
    legend_N1->Draw("AP");
    // set limits on plot
    efficiency_N1->SetMinimum(0);
    efficiency_N1->SetMaximum(1);
    // save the plot for N3
    c1->SaveAs("sIP_eff_mistag_jet_pT_N1.pdf");

    // canvas creation for N2
    TCanvas *c2 = new TCanvas("c2","c2");
    c2->cd();
    // settings for plots
    efficiency_N2->SetMarkerStyle(20);
    efficiency_N2->SetMarkerSize(0.5);
    efficiency_N2->SetMarkerColor(2);
    efficiency_N2->SetLineColor(2);
    efficiency_N2->SetLineWidth(2);
    efficiency_N2->SetStats(0);
    mistagging_c_N2->SetMarkerStyle(20);
    mistagging_c_N2->SetMarkerSize(0.5);
    mistagging_c_N2->SetMarkerColor(3);
    mistagging_c_N2->SetLineColor(3);
    mistagging_c_N2->SetLineWidth(2);
    mistagging_c_N2->SetStats(0);
    mistagging_lf_N2->SetMarkerStyle(20);
    mistagging_lf_N2->SetMarkerSize(0.5);
    mistagging_lf_N2->SetMarkerColor(4);
    mistagging_lf_N2->SetLineWidth(2);
    mistagging_lf_N2->SetLineColor(4);
    mistagging_lf_N2->SetStats(0);
    // drawing histograms
    efficiency_N2->Draw();
    mistagging_c_N2->Draw("SAME");
    mistagging_lf_N2->Draw("SAME");
    // set title for plot, x and y axis
    efficiency_N2->SetTitle("Efficiency and mistagging rates of sIP b-jet tagger - 2nd largest IP");
    efficiency_N2->GetXaxis()->SetTitle("jet pT (GeV/c)");
    efficiency_N2->GetYaxis()->SetTitle("Efficiency and mistagging rates");
    // set legend
    TLegend *legend_N2 = new TLegend(0.13,0.85,0.3,0.75);
    legend_N2->AddEntry(efficiency_N2,"Efficiency");
    legend_N2->AddEntry(mistagging_c_N2,"Mistagging c");
    legend_N2->AddEntry(mistagging_lf_N2,"Mistagging lf");
    legend_N2->SetBorderSize(0);
    legend_N2->SetTextSize(0.03);
    legend_N2->Draw("AP");
    // set limits on plot
    efficiency_N2->SetMinimum(0);
    efficiency_N2->SetMaximum(1);
    // save the plot for N2
    c2->SaveAs("sIP_eff_mistag_jet_pT_N2.pdf");

    // canvas creation for N3
    TCanvas *c3 = new TCanvas("c3","c3");
    c3->cd();
    // settings for plots
    efficiency_N3->SetMarkerStyle(20);
    efficiency_N3->SetMarkerSize(0.5);
    efficiency_N3->SetMarkerColor(2);
    efficiency_N3->SetLineColor(2);
    efficiency_N3->SetLineWidth(2);
    efficiency_N3->SetStats(0);
    mistagging_c_N3->SetMarkerStyle(20);
    mistagging_c_N3->SetMarkerSize(0.5);
    mistagging_c_N3->SetMarkerColor(3);
    mistagging_c_N3->SetLineColor(3);
    mistagging_c_N3->SetLineWidth(2);
    mistagging_c_N3->SetStats(0);
    mistagging_lf_N3->SetMarkerStyle(20);
    mistagging_lf_N3->SetMarkerSize(0.5);
    mistagging_lf_N3->SetMarkerColor(4);
    mistagging_lf_N3->SetLineWidth(2);
    mistagging_lf_N3->SetLineColor(4);
    mistagging_lf_N3->SetStats(0);
    // drawing histograms
    efficiency_N3->Draw();
    mistagging_c_N3->Draw("SAME");
    mistagging_lf_N3->Draw("SAME");
    // set title for plot, x and y axis
    efficiency_N3->SetTitle("Efficiency and mistagging rates of sIP b-jet tagger - 3rd largest IP");
    efficiency_N3->GetXaxis()->SetTitle("jet pT (GeV/c)");
    efficiency_N3->GetYaxis()->SetTitle("Efficiency and mistagging rates");
    // set legend
    TLegend *legend_N3 = new TLegend(0.13,0.85,0.3,0.75);
    legend_N3->AddEntry(efficiency_N3,"Efficiency");
    legend_N3->AddEntry(mistagging_c_N3,"Mistagging c");
    legend_N3->AddEntry(mistagging_lf_N3,"Mistagging lf");
    legend_N3->SetBorderSize(0);
    legend_N3->SetTextSize(0.03);
    legend_N3->Draw("AP");
    // set limits on plot
    efficiency_N3->SetMinimum(0);
    efficiency_N3->SetMaximum(1);
    // save the plot for N3
    c3->SaveAs("sIP_eff_mistag_jet_pT_N3.pdf");
}