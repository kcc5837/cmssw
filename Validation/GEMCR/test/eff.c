{

int drawOn=1;
int printOn=1;
int calc_eff_vfat_On=1;
//If you want to see eff vs layer or eff vs chamber without eff vs vfat then set calc_eff_vfat_On=0.
int setMinimumOn=1;

TFile *f = new TFile("Tree/temp_out_reco_MC.root");
f->cd("gemcrValidation");
//TTree *tree = (TTree*)f->get("tree");

const int maxNchamber = 15;
const int maxNlayer = 30;
const int maxNphi = 3;
const int maxNeta = 8;

double maxVfatEff = -1;
double minVfatEff = 100;
int vfatI[maxNlayer][maxNphi][maxNeta];
int vfatF[maxNlayer][maxNphi][maxNeta];
double vfatEff[maxNlayer][maxNphi][maxNeta];
double vfatEffError[maxNlayer][maxNphi][maxNeta];
TH1D *hvfatEff[maxNlayer];
TH2D *hvfatEff2[maxNlayer];

long maxVfatNumerator = -1;
long minVfatNumerator = 10000000;
long maxVfatDenominator = -1;
long minVfatDenominator = 10000000;
TH2D *hvfatNumerator[maxNlayer];
TH2D *hvfatDenominator[maxNlayer];


int layerI[maxNlayer];
int layerF[maxNlayer];
double layerEff[maxNlayer];
double layerEffError[maxNlayer];
TH1D *hlayerEff = new TH1D("hlayerEff","Efficiency VS Layer",maxNlayer,1,maxNlayer+1);
hlayerEff->GetXaxis()->SetTitle("layer num");
hlayerEff->SetMaximum(1.005);
if(setMinimumOn) hlayerEff->SetMinimum(0.9);
TH2D *hlayerEff2 = new TH2D("hlayerEff2","Efficiency VS Layer",3,1,4, 10,1,11);
TH2D *hlayerI2 = new TH2D("hlayerI2","nRecHit per layer (denominator of efficiency)",3,1,4, 10,1,11);
TH2D *hlayerF2 = new TH2D("hlayerF2","nRecHit per layer (numerator of efficiency)",3,1,4, 10,1,11);
TH1D *hlayerHitMul[maxNlayer];

int chamberI[maxNchamber];
int chamberF[maxNchamber];
double chamberEff[maxNchamber];
double chamberEffError[maxNchamber];
TH1D *hchamberEff = new TH1D("hchamberEff","Efficiency VS Chamber",maxNchamber,1,maxNchamber+1);
hchamberEff->GetXaxis()->SetTitle("chamber num");
hchamberEff->SetMaximum(1.005);
if(setMinimumOn) hchamberEff->SetMinimum(0.9);
TH2D *hchamberEff2 = new TH2D("hchamberEff2","Efficiency VS Chamber",3,1,4, 5,1,6);
TH2D *hchamberI2 = new TH2D("hchamberI2","nRecHit per chamber (denominator of efficiency)",3,1,4, 5,1,6);
TH2D *hchamberF2 = new TH2D("hchamberF2","nRecHit per chamber (numerator of efficiency)",3,1,4, 5,1,6);
TH1D *hchamberHitMul[maxNchamber];

TF1 *func = new TF1("func","0.97",0,100); //goal line
func->SetLineColor(3);

int nch=0;
TString cutChamberI = "0";
TString cutChamberF = "0";

TString cutChamberHitMul = "0";

TCanvas *c1;
TCanvas *c2;
if(drawOn) 
{
	c1 = new TCanvas("c1","c1",700,500);
	c2 = new TCanvas("c2","c2",700,500);
	c2->SetRightMargin(0.15);
}
//int i=0;
//for(int i=18;i<20;i++)
for(int i=0;i<maxNlayer;i++)
{
	TString hname = Form("hvfat_%d",i);
	TString htitle = Form("Efficiency VS VFAT (Chamber%d Layer%d)",nch*2+1,i%2+1);
	hvfatEff[i] = new TH1D(hname,htitle,maxNphi*maxNeta,0,maxNphi*maxNeta);
	hvfatEff[i]->GetXaxis()->SetTitle("VFAT num");
	hvfatEff[i]->SetMaximum(1.005);
	if(setMinimumOn) hvfatEff[i]->SetMinimum(0.9);

	hname = Form("hvfatEff2_%d",i);
	htitle = Form("Efficiency VS VFAT (Chamber%d Layer%d)",nch*2+1,i%2+1);
	hvfatEff2[i] = new TH2D(hname,htitle,maxNphi,1,maxNphi+1,maxNeta,1,maxNeta+1);
	hvfatEff2[i]->GetXaxis()->SetTitle("ith-#phi");
	hvfatEff2[i]->GetYaxis()->SetTitle("ith-#eta");

	hname = Form("hvfatNumerator_%d",i);
	htitle = Form("nRecHit per vfat (Chamber%d Layer%d, numerator of eff.)",nch*2+1,i%2+1);
	hvfatNumerator[i] = new TH2D(hname,htitle,maxNphi,1,maxNphi+1,maxNeta,1,maxNeta+1);
	hvfatNumerator[i]->GetXaxis()->SetTitle("ith-#phi");
	hvfatNumerator[i]->GetYaxis()->SetTitle("ith-#eta");
	hname = Form("hvfatDenominator_%d",i);
	htitle = Form("nRecHit per vfat (Chamber%d Layer%d, denominator of eff.)",nch*2+1,i%2+1);
	hvfatDenominator[i] = new TH2D(hname,htitle,maxNphi,1,maxNphi+1,maxNeta,1,maxNeta+1);
	hvfatDenominator[i]->GetXaxis()->SetTitle("ith-#phi");
	hvfatDenominator[i]->GetYaxis()->SetTitle("ith-#eta");

	if(i%2==0) 
	{
		cutChamberI = "0";
		cutChamberF = "0";

		cutChamberHitMul = "0";
	}
	TString cutLayerI = "0";
	TString cutLayerF = "0";

	TString cutLayerHitMul = "0";

        int nvfat = 0;
	for(int j=0, j2=maxNphi;j<maxNphi;j++, j2--) if(calc_eff_vfat_On)
	{
		for(int k=0, k2=maxNeta;k<maxNeta;k++, k2--)
		{
			//int vfatId = i*100 + j*10 + k;
			TString cutI = Form("vfatI[%d][%d][%d]==1",i,j,k);
			TString cutF = cutI+"&&"+Form("vfatF[%d][%d][%d]==1",i,j,k);
			vfatI[i][j][k] = tree->GetEntries(cutI);
			vfatF[i][j][k] = tree->GetEntries(cutF);
			if(vfatI[i][j][k]>0)
			{
				vfatEff[i][j][k] = double(vfatF[i][j][k])/vfatI[i][j][k];
				vfatEffError[i][j][k] = sqrt(vfatEff[i][j][k]*(1-vfatEff[i][j][k])/vfatI[i][j][k]);
				cout<<"i "<<i<<", j "<<j<<", k "<<k<<", vfatF "<<vfatF[i][j][k]<<", vfatI "<<vfatI[i][j][k]<<", eff "<<vfatEff[i][j][k]<<" +- "<<vfatEffError[i][j][k]<<endl;

				if(maxVfatEff < vfatEff[i][j][k]) maxVfatEff = vfatEff[i][j][k];
				if(minVfatEff > vfatEff[i][j][k]) minVfatEff = vfatEff[i][j][k];
			}

			cutLayerI += "||"+cutI;
			cutLayerF += "||("+cutF+")";

			cutLayerHitMul += Form("+vfatF[%d][%d][%d]",i,j,k);

			hvfatEff[i]->SetBinContent(nvfat+1, vfatEff[i][j][k]);
			hvfatEff[i]->SetBinError(nvfat+1, vfatEffError[i][j][k]);
//			hvfatEff2[i]->SetBinContent(j2+1,k2+1, vfatEff[i][j][k]);
//			hvfatNumerator[i]->SetBinContent(j2+1,k2+1,vfatF[i][j][k]);
//			hvfatDenominator[i]->SetBinContent(j2+1,k2+1,vfatI[i][j][k]);
			hvfatEff2[i]->SetBinContent(j+1,k+1, vfatEff[i][j][k]);
			hvfatNumerator[i]->SetBinContent(j+1,k+1,vfatF[i][j][k]);
			hvfatDenominator[i]->SetBinContent(j+1,k+1,vfatI[i][j][k]);
//			hvfatNumerator[i]->SetBinContent(j2,k+1,vfatF[i][j][k]);
//			hvfatDenominator[i]->SetBinContent(j2,k+1,vfatI[i][j][k]);

			if(maxVfatNumerator < vfatF[i][j][k]) maxVfatNumerator = vfatF[i][j][k];			
			if(minVfatNumerator > vfatF[i][j][k]) minVfatNumerator = vfatF[i][j][k];			
			if(maxVfatDenominator < vfatI[i][j][k]) maxVfatDenominator = vfatI[i][j][k];			
			if(minVfatDenominator > vfatI[i][j][k]) minVfatDenominator = vfatI[i][j][k];			

			nvfat++;
		}
	}
	if(drawOn && calc_eff_vfat_On) 
	{
		c1->cd();
		hvfatEff[i]->Draw();
		hvfatEff[i]->Fit("pol0");
//		func->Draw("same");
		TString png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d.png",nch*2+1,i%2+1);
		if(printOn) c1->Print(png);

		c2->cd();
		hvfatEff2[i]->Draw("colz text");
		png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d_2D.png",nch*2+1,i%2+1);
		if(printOn) c2->Print(png);

		hvfatNumerator[i]->Draw("colz text");
//		png = Form("Tree/calc_eff_of_chamber%d_layer%d_for_numerator.png",nch*2+1,i%2+1);
		png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d_Numerator.png",nch*2+1,i%2+1);
		if(printOn) c2->Print(png);
		hvfatDenominator[i]->Draw("colz text");
//		png = Form("Tree/calc_eff_of_chamber%d_layer%d_for_Denominator.png",nch*2+1,i%2+1);
		png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d_Denominator.png",nch*2+1,i%2+1);
		if(printOn) c2->Print(png);
	}
	cutLayerI = Form("vfatI[%d]==1",i);
	cutLayerF = cutLayerI + "&&" + Form("vfatF[%d]==1",i);
//	cout<<"i "<<i<<", cutLayerF "<<cutLayerF<<", cutLayerI "<<cutLayerI<<endl;
	layerI[i] = tree->GetEntries(cutLayerI);
	layerF[i] = tree->GetEntries(cutLayerF);
	if(layerI[i]>0)
	{
		c1->cd();
		layerEff[i] = double(layerF[i])/layerI[i];
		layerEffError[i] = sqrt(layerEff[i]*(1-layerEff[i])/layerI[i]);
		hlayerEff->SetBinContent(i+1, layerEff[i]);
		hlayerEff->SetBinError(i+1, layerEffError[i]);

		hlayerI2->SetBinContent(i/10+1, i%10+1, layerI[i]);
		hlayerF2->SetBinContent(i/10+1, i%10+1, layerF[i]);
		hlayerEff2->SetBinContent(i/10+1, i%10+1, layerEff[i]);

		cout<<"i "<<i<<", layerF "<<layerF[i]<<", layerI "<<layerI[i]<<", eff "<<layerEff[i]<<" +- "<<layerEffError[i]<<endl;
	}

	hname = Form("hlayerHitMul_%d",i);
	htitle = Form("hit multiplicity (Chamber%d Layer%d)",nch*2+1,i%2+1);
	hlayerHitMul[i] = new TH1D(hname,htitle,10,0,10);
	hlayerHitMul[i]->GetXaxis()->SetTitle("nRecHit");
	tree->Project(hname, cutLayerHitMul);

	if(drawOn)
	{
		c1->cd();
		hlayerHitMul[i]->Draw();
		TString png = Form("Tree/hit_multiplicity_of_chamber%d_layer%d.png",nch*2+1,i%2+1);
		if(printOn) c1->Print(png);

		int maxHitMul = 0;
		for(int nbin=0;nbin<hlayerHitMul[i]->GetNbinsX();nbin++)
		{
			int yValue = hlayerHitMul[i]->GetBinContent(nbin+1);
			if(yValue>0) maxHitMul = nbin;
		}
		cout<<"i "<<i<<", max hit multiplicity "<<maxHitMul<<endl;
	}

	cutChamberI += "||"+cutLayerI;
	cutChamberF += "||("+cutLayerF+")";

	cutChamberHitMul += "+"+cutLayerHitMul;

	if(i%2==1)
	{
//		cout<<"nch "<<nch<<", cutChamberF "<<cutChamberF<<", cutChamberI "<<cutChamberI<<endl;
		chamberI[nch] = tree->GetEntries(cutChamberI);
		chamberF[nch] = tree->GetEntries(cutChamberF);
		if(chamberI[nch]>0)
		{
			chamberEff[nch] = double(chamberF[nch])/chamberI[nch];
			chamberEffError[nch] = sqrt(chamberEff[nch]*(1-chamberEff[nch])/chamberI[nch]);
			hchamberEff->SetBinContent(nch+1, chamberEff[nch]);
			hchamberEff->SetBinError(nch+1, chamberEffError[nch]);

			hchamberI2->SetBinContent(nch/5+1, nch%5+1, chamberI[nch]);
			hchamberF2->SetBinContent(nch/5+1, nch%5+1, chamberF[nch]);
			hchamberEff2->SetBinContent(nch/5+1, nch%5+1, chamberEff[nch]);

			cout<<"nch "<<nch<<", chamberF "<<chamberF[nch]<<", chamberI "<<chamberI[nch]<<", eff "<<chamberEff[nch]<<" +- "<<chamberEffError[nch]<<endl;
		}

		hname = Form("hchamberHitMul_%d",i);
		htitle = Form("hit multiplicity (Chamber%d)",nch*2+1);
		hchamberHitMul[nch] = new TH1D(hname,htitle,10,0,10);
		hchamberHitMul[nch]->GetXaxis()->SetTitle("nRecHit");
		tree->Project(hname, cutChamberHitMul);

		if(drawOn)
		{
			c1->cd();
			hchamberHitMul[nch]->Draw();
			TString png = Form("Tree/hit_multiplicity_of_chamber%d.png",nch*2+1);
			if(printOn) c1->Print(png);

			int maxHitMul = 0;
			for(int nbin=0;nbin<hchamberHitMul[nch]->GetNbinsX();nbin++)
			{
				int yValue = hchamberHitMul[nch]->GetBinContent(nbin+1);
				if(yValue>0) maxHitMul = nbin;
			}
			cout<<"nch "<<nch<<", max hit multiplicity "<<maxHitMul<<endl;
		}

		nch++;
	}
}

cout<<endl<<"maxVfatEff "<<maxVfatEff<<", minVfatEff "<<minVfatEff<<", maxVfatNumerator "<<maxVfatNumerator<<", minVfatNumerator "<<minVfatNumerator<<", maxVfatDenominator "<<maxVfatDenominator<<", minVfatDenominator "<<minVfatDenominator<<endl;

for(int i=0;i<maxNlayer;i++) if(drawOn && calc_eff_vfat_On) 
{
	c2->cd();
	hvfatEff2[i]->SetMaximum(maxVfatEff + (maxVfatEff-minVfatEff)*0.05);
	hvfatEff2[i]->SetMinimum(minVfatEff - (maxVfatEff-minVfatEff)*0.05);
	hvfatEff2[i]->Draw("colz");
	TString png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d_fixRange_2D.png",(i/2)*2+1,i%2+1);
	if(printOn) c2->Print(png);

	hvfatNumerator[i]->SetMaximum(maxVfatNumerator + (maxVfatNumerator-minVfatNumerator)*0.05);
	hvfatNumerator[i]->SetMinimum(minVfatNumerator - (maxVfatNumerator-minVfatNumerator)*0.05);
	hvfatNumerator[i]->Draw("colz");
	png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d_fixRange_Numerator.png",(i/2)*2+1,i%2+1);
	if(printOn) c2->Print(png);
	hvfatDenominator[i]->SetMaximum(maxVfatDenominator + (maxVfatDenominator-minVfatDenominator)*0.05);
	hvfatDenominator[i]->SetMinimum(minVfatDenominator - (maxVfatDenominator-minVfatDenominator)*0.05);
	hvfatDenominator[i]->Draw("colz");
	png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d_fixRange_Denominator.png",(i/2)*2+1,i%2+1);
	if(printOn) c2->Print(png);
}

if(drawOn) 
{
	c1->cd();
	hlayerEff->Draw();
//	hlayerEff->Fit("pol0");
	TString png ="Tree/eff_VS_layer.png";
	if(printOn) c1->Print(png);
	hchamberEff->Draw();
//	hchamberEff->Fit("pol0");
	png = "Tree/eff_VS_chamber.png";
	if(printOn) c1->Print(png);

	c2->cd();
	hlayerI2->Draw("colz text");
	png ="Tree/eff_VS_layer_2D_denominator.png";
	if(printOn) c2->Print(png);
	hlayerF2->Draw("colz text");
	png ="Tree/eff_VS_layer_2D_numerator.png";
	if(printOn) c2->Print(png);
	hlayerEff2->Draw("colz text");
	png ="Tree/eff_VS_layer_2D.png";
	if(printOn) c2->Print(png);

	hchamberI2->Draw("colz text");
	png = "Tree/eff_VS_chamber_2D_denominator.png";
	if(printOn) c2->Print(png);
	hchamberF2->Draw("colz text");
	png = "Tree/eff_VS_chamber_2D_numerator.png";
	if(printOn) c2->Print(png);
	hchamberEff2->Draw("colz text");
	png = "Tree/eff_VS_chamber_2D.png";
	if(printOn) c2->Print(png);
}



}

