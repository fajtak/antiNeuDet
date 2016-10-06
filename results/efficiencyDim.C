void efficiencyDim(void)
{
    TH1F* eff = new TH1F("eff","Antineutrino detection efficiency;Detector dimension [cm];Efficiency [%]",10,5,105);

    eff->Fill(10,0.76);
    eff->Fill(20,8.58);
    eff->Fill(30,21.82);
    eff->Fill(40,34.04);
    eff->Fill(50,42.52);
    eff->Fill(60,50.40);
    eff->Fill(70,55.48);
    eff->Fill(80,60.53);
    eff->Fill(90,64.91);
    eff->Fill(100,68.11);

    eff->SetStats(0);
    eff->Draw();
}
