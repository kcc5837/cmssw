{

//TFile *f = new TFile("/afs/cern.ch/work/j/jslee/QC8/temp_out_reco_MC_102-103.root");
TFile *f = new TFile("/afs/cern.ch/work/j/jslee/QC8/temp_out_reco_MC_106.root");
f->cd("gemcrValidation");

cout<<"nev "<<hev->GetBinContent(1)<<endl;

new TCanvas;
//c1->SetRightMargin(0.15);

/*
double vfatI020 = tree->GetEntries("vfatI[0][2][0]");
double vfatF020 = tree->GetEntries("vfatF[0][2][0]");
double eff020 = vfatF020/vfatI020; //0.957710
double vfatI020_alpha = tree->GetEntries("vfatI[0][2][0] && acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>80");
double vfatF020_alpha = tree->GetEntries("vfatF[0][2][0] && acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>80");
double eff020_alpha = vfatF020_alpha/vfatI020_alpha; //0.955847
*/
//alpha angle
/*
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958:trajHitZ[0][0][0]>>i000(50,43,52,50,30,90)","vfatI[0][0][0]","colz");
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958:trajHitZ[0][0][0]>>f000(50,43,52,50,30,90)","vfatI[0][0][0]&&vfatF[0][0][0]","colz");
f000->Divide(f000,i000);
f000->Draw("colz");
*/
//1 rad = 57.2958 degree

tree->Draw("trajPhi*57.2958>>i92(30,60,120)","vfatI[9][2]");
tree->Draw("trajPhi*57.2958>>f92(30,60,120)","vfatF[9][2]");
c1->Print("eff_VS_phi_chamber9_layer2_edge_denominator.png");
f92->SetTitle("#phi of trajectory (edge vfats of chamber9 layer2)");
f92->GetXaxis()->SetTitle("degree");
i92->Sumw2();
f92->Sumw2();
f92->Divide(f92,i92,1,1,"b");
f92->Draw();
c1->Print("eff_VS_phi_chamber9_layer2.png");

/*
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>>i92(15,30,90)","vfatI[9][2]");
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>>f92(15,30,90)","vfatI[9][2]&&vfatF[9][2]");
f92->SetTitle("angle between trajectory and vfat surface (edge vfats of chamber9 layer2)");
f92->GetXaxis()->SetTitle("degree");
c1->Print("eff_VS_alpha_chamber9_layer2_edge_denominator.png");
i92->Sumw2();
f92->Sumw2();
f92->Divide(f92,i92,1,1,"b");
f92->Draw();
c1->Print("eff_VS_alpha_chamber9_layer2_edge.png");
*/
/*
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>>i001(15,30,90)","vfatI[0][0][1]");
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>>f001(15,30,90)","vfatI[0][0][1]&&vfatF[0][0][1]");
i001->Sumw2();
f001->Sumw2();
f001->Divide(f001,i001,1,1,"b");
f001->Draw();
*/
/*
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>>i000(15,30,90)","vfatI[0][0][0]");
tree->Draw("acos(sqrt(sin(trajTheta)*cos(trajPhi)*sin(trajTheta)*cos(trajPhi) + cos(trajPhi)*cos(trajPhi)))*57.2958>>f000(15,30,90)","vfatI[0][0][0]&&vfatF[0][0][0]");
c1->Print("temp/eff_VS_alpha_degree_numerator.png");
i000->Sumw2();
f000->Sumw2();
f000->Divide(f000,i000,1,1,"b");
f000->Draw();
c1->Print("temp/eff_VS_alpha_degree.png");
*/
/*
new TCanvas;
c1->SetRightMargin(0.15);
tree->Draw("trajHitX[0][1][1]:trajHitZ[0][1][1]>>i1(200,0,60,200,-55,-20)","vfatI[0][1][1]","colz");
tree->Draw("trajHitX[0][1][1]:trajHitZ[0][1][1]>>f1(200,0,60,200,-55,-20)","vfatI[0][1][1]&&vfatF[0][1][1]","colz");
f1->SetTitle("efficiency using trajHit in XZ plane (chamber1 layer1 vfat1)")
f1->Divide(f1,i1);
f1->Draw("colz");
c1->Print("eff_using_trajHit_inXZ_Ch1La1Vfat1.png")
*/
/*
new TCanvas;
c1->SetRightMargin(0.15);
tree->Draw("genHitX[0][0][1]:genHitZ[0][0][1]>>i1(50,0,60,50,-65,-40)","vfatI[0][0][1]","colz");
tree->Draw("genHitX[0][0][1]:genHitZ[0][0][1]>>f1(50,0,60,50,-65,-40)","vfatI[0][0][1]&&vfatF[0][0][1]","colz");
f1->SetTitle("efficiency using genHit in XZ plane (chamber1 layer1 vfat1)")
f1->Divide(f1,i1);
f1->Draw("colz");
c1->Print("eff_using_genHit_inXZ_Ch1La1Vfat1.png")

tree->Draw("genHitZ[0][0][0]>>i2(50,20,65)","vfatI[0][0][0]");
tree->Draw("genHitZ[0][0][0]>>f2(50,20,65)","vfatI[0][0][0]&&vfatF[0][0][0]");
i2->Sumw2();
f2->Sumw2();
f2->Divide(f2,i2,1,1,"b");
f2->Draw();

tree->Draw("trajHitZ[0][0][0]-genHitZ[0][0][0]>>i000(50,-25,25)","vfatI[0][0][0]");
tree->Draw("trajHitZ[0][0][0]-genHitZ[0][0][0]>>f000(50,-25,25)","vfatI[0][0][0]&&vfatF[0][0][0]");
i000->Sumw2();
f000->Sumw2();
f000->Divide(f000,i000,1,1,"b");
f000->Draw();

tree->Draw("trajHitZ[0][1][0]-genHitZ[0][1][0]>>i010(50,-25,25)","vfatI[0][1][0]");
tree->Draw("trajHitZ[0][1][0]-genHitZ[0][1][0]>>f010(50,-25,25)","vfatI[0][1][0]&&vfatF[0][1][0]");
i010->Sumw2();
f010->Sumw2();
f010->Divide(f010,i010,1,1,"b");
f010->Draw();

tree->Draw("trajHitZ[0][0][7]-genHitZ[0][0][7]>>i007(50,-25,25)","vfatI[0][0][7]");
tree->Draw("trajHitZ[0][0][7]-genHitZ[0][0][7]>>f007(50,-25,25)","vfatI[0][0][7]&&vfatF[0][0][7]");
i007->Sumw2();
f007->Sumw2();
f007->Divide(f007,i007,1,1,"b");
f007->Draw();

tree->Draw("trajHitZ[4][0][0]-genHitZ[4][0][0]>>i400(50,-25,25)","vfatI[4][0][0]");
tree->Draw("trajHitZ[4][0][0]-genHitZ[4][0][0]>>f400(50,-25,25)","vfatI[4][0][0]&&vfatF[4][0][0]");
i400->Sumw2();
f400->Sumw2();
f400->Divide(f400,i400,1,1,"b");
f400->Draw();

tree->Draw("trajHitZ[9][0][0]-genHitZ[9][0][0]>>i900(50,-25,25)","vfatI[9][0][0]");
tree->Draw("trajHitZ[9][0][0]-genHitZ[9][0][0]>>f900(50,-25,25)","vfatI[9][0][0]&&vfatF[9][0][0]");
i900->Sumw2();
f900->Sumw2();
f900->Divide(f900,i900,1,1,"b");
f900->Draw();

tree->Draw("trajHitZ[19][0][0]-genHitZ[19][0][0]>>i1900(50,-25,25)","vfatI[19][0][0]");
tree->Draw("trajHitZ[19][0][0]-genHitZ[19][0][0]>>f1900(50,-25,25)","vfatI[19][0][0]&&vfatF[19][0][0]");
i1900->Sumw2();
f1900->Sumw2();
f1900->Divide(f1900,i1900,1,1,"b");
f1900->Draw();

tree->Draw("diffX[0][0][0]:diffZ[0][0][0]>>hi(50,-35,35,50,-3,3)","vfatI[0][0][0]","colz");
tree->Draw("diffX[0][0][0]:diffZ[0][0][0]>>hf(50,-35,35,50,-3,3)","vfatI[0][0][0]&&vfatF[0][0][0]","colz");
hi->Sumw2();
hf->Sumw2();
hf->Divide(hf,hi);
c1->SetRightMargin(0.15);
hf->Draw("colz");

tree->Draw("sqrt(diffX[0][0][0]*diffX[0][0][0]+diffZ[0][0][0]*diffZ[0][0][0])>>i1(50,0,25)","vfatI[0][0][0]");
tree->Draw("sqrt(diffX[0][0][0]*diffX[0][0][0]+diffZ[0][0][0]*diffZ[0][0][0])>>f1(50,0,25)","vfatI[0][0][0]&&vfatF[0][0][0]");
i1->Sumw2();
f1->Sumw2();
f1->Divide(f1,i1,1,1,"b");
f1->Draw();

tree->Draw("trajHitZ-genHitZ>>i11(50,-25,25)","vfatI");
tree->Draw("trajHitZ-genHitZ>>f11(50,-25,25)","vfatI&&vfatF");
i11->Sumw2();
f11->Sumw2();
f11->SetTitle("efficiency with all vfats");
f11->GetXaxis()->SetTitle("trajHitZ - genHitZ");
f11->Divide(f11,i11,1,1,"b");
f11->Draw();
c1->Print("eff_VS_trajHitZ-genHitZ.png");

//tree->Draw("diffX[0][0][0]>>i1(50,-3,3)","vfatI[0][0][0]");
tree->Draw("diffZ[0][0][0]>>i1(50,-25,25)","vfatI[0][0][0]");
//tree->Draw("diffZ[0]>>i1(R5,-25,25)","vfatI[0]");
//tree->Draw("diffX>>i1(50,-3,3)","vfatI"); //good
//tree->Draw("diffZ>>i1(50,-25,25)","vfatI"); //good
i1->DrawCopy();
new TCanvas;
//tree->Draw("diffX[0][0][0]>>f1(50,-3,3)","vfatI[0][0][0]&&vfatF[0][0][0]");
tree->Draw("diffZ[0][0][0]>>f1(50,-25,25)","vfatI[0][0][0]&&vfatF[0][0][0]");
//tree->Draw("diffZ[0]>>f1(50,-25,25)","vfatI[0]&&vfatF[0]");
//tree->Draw("diffX>>f1(50,-3,3)","vfatI&&vfatF"); //good
//tree->Draw("diffZ>>f1(50,-25,25)","vfatI&&vfatF"); //good
f1->DrawCopy();
i1->Sumw2();
f1->Sumw2();
f1->Divide(f1,i1,1,1,"b");
new TCanvas;
f1->Draw();


//tree->Draw("trajHitX[0][0][1]:trajHitZ[0][0][1]>>t001(100,0,60,100,-65,-40)","vfatF[0][0][1]");
//tree->Draw("genHitX[0][0][1]:genHitZ[0][0][1]>>g001(100,0,60,100,-65,-40)","vfatF[0][0][1]");
//tree->Draw("recHitX[0][0][1]:recHitZ[0][0][1]>>r001(100,0,60,100,-65,-40)","vfatF[0][0][1]");
TH2D *t001 = new TH2D("t001","trajHitX vs trajHitZ (chamber1 layer1 vfat1)",100,0,60,100,-65,-40);
t001->GetXaxis()->SetTitle("trajHitZ");
t001->GetYaxis()->SetTitle("trajHitX");
tree->Project("t001","trajHitX[0][0][1]:trajHitZ[0][0][1]","vfatF[0][0][1]");
t001->Draw();
c1->Draw("hit2D_ch1_la1_vfat1_trajHitX_trajHitZ.png");
TH2D *g001 = new TH2D("g001","genHitX vs genHitZ (chamber1 layer1 vfat1)",100,0,60,100,-65,-40);
g001->GetXaxis()->SetTitle("genHitZ");
g001->GetYaxis()->SetTitle("genHitX");
tree->Project("g001","genHitX[0][0][1]:genHitZ[0][0][1]","vfatF[0][0][1]");
g001->Draw();
c1->Draw("hit2D_ch1_la1_vfat1_genHitX_genHitZ.png");
TH2D *r001 = new TH2D("r001","recHitX vs recHitZ (chamber1 layer1 vfat1)",100,0,60,100,-65,-40);
r001->GetXaxis()->SetTitle("recHitZ");
r001->GetYaxis()->SetTitle("recHitX");
tree->Project("r001","recHitX[0][0][1]:recHitZ[0][0][1]","vfatF[0][0][1]");
r001->Draw();
c1->Draw("hit2D_ch1_la1_vfat1_recHitX_recHitZ.png");
*/
/*
TCanvas *c1 = new TCanvas("c1","c1",700,500);
c1->SetRightMargin(0.15);
TString hname = "t011I";
TH2D *t011I = new TH2D(hname,"trajHitX vs trajHitZ (chamber1 layer1 vfat9, denominator)",200,0,60,200,-55,-20);
tree->Project(hname,"trajHitX[0][1][1]:trajHitZ[0][1][1]","vfatI[0][1][1]");
hname = "t011F";
TH2D *t011F = new TH2D(hname,"trajHitX vs trajHitZ (chamber1 layer1 vfat9, numerator)",200,0,60,200,-55,-20);
t011F->GetXaxis()->SetTitle("trajHitZ");
t011F->GetYaxis()->SetTitle("trajHitX");
tree->Project(hname,"trajHitX[0][1][1]:trajHitZ[0][1][1]","vfatI[0][1][1]&&vfatF[0][1][1]");
t011F->DrawCopy("colz");
c1->Print("hit2D_ch1_la1_vfat9_trajHitX_trajHitZ_numerator.png");
t011F->Divide(t011F,t011I);
t011F->Draw("colz");
c1->Print("hit2D_ch1_la1_vfat9_trajHitX_trajHitZ_eff.png");
*/
/*
hname = "g011";
TH2D *g011 = new TH2D(hname,"genHitX vs genHitZ (chamber1 layer1 vfat9)",200,0,60,200,-55,-20);
g011->GetXaxis()->SetTitle("genHitZ");
g011->GetYaxis()->SetTitle("genHitX");
tree->Project(hname,"genHitX[0][1][1]:genHitZ[0][1][1]","vfatF[0][1][1]");
g011->Draw("colz");
c1->Print("hit2D_ch1_la1_vfat1_genHitX_genHitZ.png");
hname = "r011";
TH2D *r011 = new TH2D(hname,"recHitX vs recHitZ (chamber1 layer1 vfat9)",200,0,60,200,-55,-20);
r011->GetXaxis()->SetTitle("recHitZ");
r011->GetYaxis()->SetTitle("recHitX");
tree->Project(hname,"recHitX[0][1][1]:recHitZ[0][1][1]","vfatF[0][1][1]");
r011->Draw("colz");
c1->Print("hit2D_ch1_la1_vfat1_recHitX_recHitZ.png");
*/




}
