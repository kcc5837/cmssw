{

int drawOn=1;
int printOn=1;

TFile *f = new TFile("Tree/temp_out_reco_MC.root");
f->cd("gemcrValidation");
//TTree *tree = (TTree*)f->get("tree");

const int maxNchamber = 15;
const int maxNlayer = 30;
const int maxNphi = 3;
const int maxNeta = 8;

int vfatI[maxNlayer][maxNphi][maxNeta];
int vfatF[maxNlayer][maxNphi][maxNeta];
double vfatEff[maxNlayer][maxNphi][maxNeta];
double vfatEffError[maxNlayer][maxNphi][maxNeta];
TH1D *hvfatEff[maxNlayer];

int layerI[maxNlayer];
int layerF[maxNlayer];
double layerEff[maxNlayer];
double layerEffError[maxNlayer];
TH1D *hlayerEff = new TH1D("hlayerEff","Efficiency VS Layer",30,1,31);
hlayerEff->GetXaxis()->SetTitle("layer num");

int chamberI[maxNchamber];
int chamberF[maxNchamber];
double chamberEff[maxNchamber];
double chamberEffError[maxNchamber];
TH1D *hchamberEff = new TH1D("hchamberEff","Efficiency VS Chamber",15,1,31);
hchamberEff->GetXaxis()->SetTitle("chamber num");

TF1 *func = new TF1("func","0.97",0,100);
func->SetLineColor(2);

int nch=0;
TString cutChamberI = "0";
TString cutChamberF = "0";
for(int i=0;i<maxNlayer;i++)
{
	TString hname = Form("hvfat_%d",i);
	TString htitle = Form("Efficiency VS VFAT (Chamber%d Layer%d)",nch*2+1,i%2+1);
	hvfatEff[i] = new TH1D(hname,htitle,24,0,24);
	hvfatEff[i]->GetXaxis()->SetTitle("VFAT num");

	if(i%2==0) 
	{
		cutChamberI = "0";
		cutChamberF = "0";
	}
	//TString cutLayerI = "(0";
	TString cutLayerI = "0";
	TString cutLayerF = "0";
        int nvfat = 0;
	for(int j=0;j<maxNphi;j++)
	{
		for(int k=0;k<maxNeta;k++)
		{
			int vfatId = i*100 + j*10 + k;
			TString cutI = Form("vfatI[%d][%d][%d]==1",i,j,k);
			TString cutF = cutI+"&&"+Form("vfatF[%d][%d][%d]==1",i,j,k);
			vfatI[i][j][k] = tree->GetEntries(cutI);
			vfatF[i][j][k] = tree->GetEntries(cutF);
			if(vfatI[i][j][k]>0)
			{
				vfatEff[i][j][k] = double(vfatF[i][j][k])/vfatI[i][j][k];
				vfatEffError[i][j][k] = sqrt(vfatEff[i][j][k]*(1-vfatEff[i][j][k])/vfatI[i][j][k]);
				cout<<"i "<<i<<", j "<<j<<", k "<<k<<", vfatF "<<vfatF[i][j][k]<<", vfatI "<<vfatI[i][j][k]<<", eff "<<vfatEff[i][j][k]<<" +- "<<vfatEffError[i][j][k]<<endl;
			}

			cutLayerI += "||"+cutI;
			cutLayerF += "||("+cutF+")";

			hvfatEff[i]->SetBinContent(nvfat+1, vfatEff[i][j][k]);
			hvfatEff[i]->SetBinError(nvfat+1, vfatEffError[i][j][k]);
			nvfat++;
		}
	}
	if(drawOn) 
	{
		hvfatEff[i]->Draw();
		func->Draw("same");
		TString png = Form("Tree/eff_VS_vfat_of_chamber%d_layer%d.png",nch*2+1,i%2+1);
		if(printOn) c1->Print(png);
	}
//	cout<<"i "<<i<<"cutLayerI "<<cutLayerI<<endl;
//	cout<<"i "<<i<<"cutLayerF "<<cutLayerF<<endl;
	layerI[i] = tree->GetEntries(cutLayerI);
	layerF[i] = tree->GetEntries(cutLayerF);
	if(layerI[i]>0)
	{
		layerEff[i] = double(layerF[i])/layerI[i];
		layerEffError[i] = sqrt(layerEff[i]*(1-layerEff[i])/layerI[i]);
		hlayerEff->SetBinContent(i+1, layerEff[i]);
		hlayerEff->SetBinError(i+1, layerEffError[i]);
		cout<<"i "<<i<<", layerF "<<layerF[i]<<", layerI "<<layerI[i]<<", eff "<<layerEff[i]<<" +- "<<layerEffError[i]<<endl;
	}

	cutChamberI += "||"+cutLayerI;
	cutChamberF += "||("+cutLayerF+")";
	if(i%2==1)
	{
//		cout<<"nch "<<nch<<"cutChamberI "<<cutChamberI<<endl;
//		cout<<"nch "<<nch<<"cutChamberF "<<cutChamberF<<endl;
		chamberI[nch] = tree->GetEntries(cutChamberI);
		chamberF[nch] = tree->GetEntries(cutChamberF);
		if(chamberI[nch]>0)
		{
			chamberEff[nch] = double(chamberF[nch])/chamberI[nch];
			chamberEffError[nch] = sqrt(chamberEff[nch]*(1-chamberEff[nch])/chamberI[nch]);
			hchamberEff->SetBinContent(nch+1, chamberEff[nch]);
			hchamberEff->SetBinError(nch+1, chamberEffError[nch]);
			cout<<"nch "<<nch<<", chamberF "<<chamberF[nch]<<", chamberI "<<chamberI[nch]<<", eff "<<chamberEff[nch]<<" +- "<<chamberEffError[nch]<<endl;
		}
		nch++;
	}
}

if(drawOn) 
{
	hlayerEff->Draw();
	func->Draw("same");
	TString png ="Tree/eff_VS_layer.png";
	if(printOn) c1->Print(png);
	hchamberEff->Draw();
	func->Draw("same");
	png = "Tree/eff_VS_chamber.png";
	if(printOn) c1->Print(png);
}


}

