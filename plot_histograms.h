// Pedro Cipriano, Nov 2012
// DESY, CMS
// Last Update: 11 May 2015
//
// Provides functions to plot histograms with ROOT
//
// set_legend_position(string legend_position, int size, double &x1, double &y1, double &x2, double &y2)
// sets the x1, y1, x2, y2 to draw the legend according to legend_positions and size
//
// print_plots(TCanvas *c, string path, string fileout)
// saves a given TCanvas c into path path with filename fileout
//
// format_histogram(TH1 *hist, int color, int style)
// formats an histogram with color, style and line width
//
// double get_non0_minimum(TH1D, bool detail = false)
// similar to TH1 GetMinimum but ignores the entries with value 0
//
// set_histogram_min_max(TH1 *histogram, double &min, double &max, bool detail = false)
// given a min and a max, this funtion will check if they fit on the histogram range, if not it will change them
//
// normalize_histogram(TH1D *histogram, string name, bool fullnorm = false, bool detail = false)
// normalize a histogram
//
// plot_histogram(TH1D *histogram, string path, string fileout, TString label, string legend_position, bool isunc = false)
//plots an histogram with errors, also plots uncertainties histograms
//
// plot_2histograms(TH1 *hist1 = 0, TString label1 = "label1", TH1 *hist2 = 0, TString label2 = "label2", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
// plots the two distributions in the same plot
//
// plot_3histograms(TH1D *hist1 = 0, TString label1 = "label1", TH1D *hist2 = 0, TString label2 = "label2", TH1D *hist3 = 0, TString label3 = "label3", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
// plots three distributions in the same plot
//
// plot_4histograms(TH1D *hist1 = 0, TString label1 = "label1", TH1D *hist2 = 0, TString label2 = "label2", TH1D *hist3 = 0, TString label3 = "label3", TH1D *hist4 = 0, TString label4 = "label4", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
// plots four distributions in the same plot
//



#include <TH1.h>
#include <TGraph.h>
#include <TH2.h>
#include <TF1.h>
#include <TString.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void set_legend_position(string legend_position, int size, double &x1, double &y1, double &x2, double &y2)
{
//sets the x1, y1, x2, y2 to draw the legend according to legend_positions and size

bool test = false;

//cheking the input of the function

    if (test)
	{
        cout << "set_legend_position run on test mode!" << endl;
	cout << "Input:" << endl;
	cout << "legend_position = " << legend_position << endl;
	cout << "size = " << size << endl;
	}

    if (legend_position == "")
	{
	cout << "No position specified! The default value of 'top_left' will be used!" << endl;
	legend_position = "top_left";
	}

    if (size < 1)
	{
	cout << "The choosen size = " << size << " is too small! The default value of '1' will be used!" << endl;
	size = 1;
	}

    if (size > 6)
	{
	cout << "The choosen size = " << size << " is too big! The default value of '6' will be used!" << endl;
	size = 6;
	}

//set the legend limits
    if (legend_position == "top_left")
    	{
    	x1 = 0.13;
    	y1 = 0.98;
    	x2 = 0.55;
    	if (size == 1) { y2 = 0.88; }
    	if (size == 2) { y2 = 0.83; }
    	if (size == 3) { y2 = 0.78; }
    	if (size == 4) { y2 = 0.73; }
    	if (size == 5) { y2 = 0.68; }
    	if (size == 6) { y2 = 0.63; }
   	}

    if (legend_position == "bottom_left")
    	{
    	x1 = 0.13;
    	y1 = 0.20;
    	x2 = 0.55;
    	if (size == 1) { y2 = 0.30; }
    	if (size == 2) { y2 = 0.35; }
    	if (size == 3) { y2 = 0.40; }
    	if (size == 4) { y2 = 0.45; }
    	if (size == 5) { y2 = 0.50; }
    	if (size == 6) { y2 = 0.55; }
    	}
    
    if (legend_position == "bottom_middle")
    	{
    	x1 = 0.33;
    	y1 = 0.18;
    	x2 = 0.76;
    	if (size == 1) { y2 = 0.28; }
    	if (size == 2) { y2 = 0.33; }
    	if (size == 3) { y2 = 0.38; }
    	if (size == 4) { y2 = 0.43; }
    	if (size == 5) { y2 = 0.43; }
    	if (size == 6) { y2 = 0.43; }
    	}
    
    if (legend_position == "top_right")
    	{
    	x1 = 0.55;
    	y1 = 0.98;
    	x2 = 0.98;
    	if (size == 1) { y2 = 0.88; }
    	if (size == 2) { y2 = 0.83; }
    	if (size == 3) { y2 = 0.78; }
    	if (size == 4) { y2 = 0.73; }
    	if (size == 5) { y2 = 0.68; }
    	if (size == 6) { y2 = 0.63; }
    	}

    if (legend_position == "bottom_right")
    	{
    	x1 = 0.55;
    	y1 = 0.15;
    	x2 = 0.98;
    	if (size == 1) { y2 = 0.25; }
    	if (size == 2) { y2 = 0.30; }
    	if (size == 3) { y2 = 0.35; }
    	if (size == 4) { y2 = 0.40; }
    	if (size == 5) { y2 = 0.45; }
    	if (size == 6) { y2 = 0.50; }
    	}
    
    if (legend_position == "middle_left")
    	{
    	x1 = 0.13;
    	y1 = 0.48;
    	x2 = 0.50;
    	y2 = 0.68;
    	}

    if (legend_position == "top_middle")
    	{
    	x1 = 0.33;
    	y1 = 0.73;
    	x2 = 0.76;
    	y2 = 0.98;
    	}

    if (test)
	{
	cout << "Output:" << endl;
	cout << "x1 = " << x1 << endl;
	cout << "x2 = " << x2 << endl;
	cout << "y1 = " << y1 << endl;
	cout << "y2 = " << y2 << endl;
	cout << "End of routine!" << endl;
	}

}


void print_plots(TCanvas *c = 0, string path = "../output/", string file_name = "fileout")
{
//saves a given TCanvas c into path path with filename fileout

bool test = false;


//check the inputs of the function
    if (test)
	{
        cout << "print_plots run on test mode!" << endl;
	cout << "Input:" << endl;
	cout << "path = " << path << endl;
	cout << "file_name = " << file_name << endl;
	}

   if (c == 0)
	{
	cout << "TCanvas is not provided!" << endl;
	if (test) { cout << "End of routine!" << endl; }
	return;
	} 

//setting the output files
   string file_png = path + "png/" + file_name + ".png";
   string file_c = path + "c/" + file_name + ".C";
   string file_eps = path + "eps/" + file_name + ".eps";

//save the file and close the canvas
    c->Print( file_png.c_str() );
    c->Print( file_c.c_str() );
    c->Print( file_eps.c_str() );
    c->Close();

    if (test)
	{
	cout << "Output:" << endl;
	cout << "file_png = " << file_png << endl;
	cout << "file_c = " << file_c << endl;
	cout << "file_eps = " << file_eps << endl;
	cout << "End of routine!" << endl;
	}

}


void format_histogram(TH1 *hist = 0, int color = 1, int style = 1)
{
//formats an histogram with color, style and line width

bool test = false;

//check the inputs of the function
    if (test)
	{
        cout << "format_histogram run on test mode!" << endl;
	cout << "Input:" << endl;
	cout << "color = " << color << endl;
	cout << "style = " << style << endl;
	}

   if (hist == 0)
	{
	cout << "Histogram is not provided!" << endl;
	if (test) { cout << "End of routine!" << endl; }
	return;
	} 

    hist->SetLineColor(color);
    hist->SetLineStyle(style);
    hist->SetLineWidth(4);
    hist->SetFillColor(0);

    if (test)
	{
	cout << "End of routine!" << endl;
	}
}



double get_non0_minimum(TH1 *histogram = 0, bool detail = false)
{
//similar to TH1 GetMinimum but ignores the entries with value 0
double min = 1e50;

    for(Int_t i=1;i<=histogram->GetNbinsX();i++)
    {
	if (min > histogram->GetBinContent(i) && histogram->GetBinContent(i) > 0.0) { min = histogram->GetBinContent(i); }
    }
    
    if (min == 0.0) { min = 1.0; }
    if (detail) { cout << "Non zero minimum required = " << min << endl; }    

return min;
}

void set_histogram_min_max(TH1 *histogram, double &min, double &max, bool detail = false)
{
//given a min and a max, this funtion will check if they fit on the histogram range, if not it will change them
    if (min > histogram->GetMinimum() && histogram->GetMinimum() > 0.0) { min = histogram->GetMinimum(); }
    if (min > get_non0_minimum(histogram) && histogram->GetMinimum() == 0.0) { min = get_non0_minimum(histogram,detail); }
    if (max < histogram->GetMaximum()) { max = histogram->GetMaximum(); }
}

void normalize_histogram(TH1D *histogram, string name, bool fullnorm = false, bool detail = false)
{
//normalize a histogram

    double integral = 0.0;
    integral = histogram->Integral();
    if (detail) { cout<<name<<" = "<<integral<<" pb^-1"<<endl; }
    
    for(Int_t i=1;i<=histogram->GetNbinsX();i++)
    	{
    	Float_t cont = histogram->GetBinContent(i);
    //	Float_t width = histogram->GetBinWidth(i);
        Float_t error = histogram->GetBinError(i);
     //   cont /= width;
     //   error /= width;
	if (fullnorm)
		{
        	histogram->SetBinContent(i,cont/integral);
        	histogram->SetBinError(i,error/integral);
		}
	else
		{
        	histogram->SetBinContent(i,cont);
        	histogram->SetBinError(i,error);
    		}
    	}
    
histogram->SetEntries(histogram->GetEntries() - histogram->GetNbinsX());

}


void plot_histogram(TH1D *histogram, string path, string fileout, TString label, string legend_position, bool logscale = false, bool isunc = false)
{
//plots an histogram with errors, also plots uncertainties histograms

//declaring the canvas
    TCanvas *c1 = new TCanvas("c1","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    //gStyle->SetErrorX(0);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);
    if (logscale) { gPad->SetLogy(); }

//format and ploting the histogram
    if (isunc) { histogram->SetMinimum(0); histogram->SetMaximum(0.7); }
    format_histogram(histogram, 2, 1);
    histogram->Draw("e1");
    
//sets and draw the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 1, x1, y1, x2, y2);

    TLegend *leg00 = new TLegend(x1, y1, x2, y2);
    leg00->AddEntry(histogram,label,"l");
    leg00->SetFillColor(0);
    leg00->SetLineWidth(1);
    leg00->SetLineColor(0);
    leg00->SetFillStyle(1001);
    leg00->Draw();
    
    print_plots(c1, path, fileout);
}


void plot_graph(TGraph *graph = 0, TGraph *point = 0, string path = "/", string fileout = "test", TString label = "label", string legend_position = "bottom_right", bool logscale = false)
{
//plots an graph and a working point if it is supplied

//declaring the canvas
    TCanvas *c1 = new TCanvas("c1","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    //gStyle->SetErrorX(0);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);
    if (logscale) { gPad->SetLogy(); }

//format and ploting the histogram
   graph->Draw("AL");
   graph->SetLineWidth(3);
   graph->GetYaxis()->SetRangeUser(0.8,1.0);
   graph->GetXaxis()->SetRangeUser(0.0,1.0);
   graph->GetXaxis()->SetTitle("Background Efficiency");
   graph->GetYaxis()->SetTitle("Signal Efficiency");
   if (point != 0)   
	{
	point->Draw("*");
	point->SetMarkerStyle(21);
	point->SetMarkerSize(3);
	}
    
//sets and draw the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 1, x1, y1, x2, y2);

    TLegend *leg00 = new TLegend(x1, y1, x2, y2);
    leg00->AddEntry(graph,label,"l");
    leg00->SetFillColor(0);
    leg00->SetLineWidth(1);
    leg00->SetLineColor(0);
    leg00->SetFillStyle(1001);
    leg00->Draw();
    
    print_plots(c1, path, fileout);
}


void plot_2dhistogram(TH2D *histogram, string path, string fileout, TString label, string legend_position)
{
//plots an histogram with errors, also plots uncertainties histograms

//declaring the canvas
    TCanvas *c1 = new TCanvas("c1","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    //gStyle->SetErrorX(0);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);

//format and ploting the histogram
    histogram->Draw("e1");
    
//sets and draw the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 1, x1, y1, x2, y2);

    TLegend *leg00 = new TLegend(x1, y1, x2, y2);
    leg00->AddEntry(histogram,label,"l");
    leg00->SetFillColor(0);
    leg00->SetLineWidth(1);
    leg00->SetLineColor(0);
    leg00->SetFillStyle(1001);
    leg00->Draw();
    
    print_plots(c1, path, fileout);
}


void plot_2histograms(TH1 *hist1 = 0, TString label1 = "label1", TH1 *hist2 = 0, TString label2 = "label2", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
{
// plots the two distributions in the same plot

// check if there are any histograms inputed
if (hist1 == 0) { cout << "Histogram1 is not provided!" << endl; return; } 
if (hist2 == 0) { cout << "Histogram2 is not provided!" << endl; return; } 

    if (detail) { cout<<"Ploting "<<fileout<<endl; }
// declare and configure the canvas
    TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    if (logscale) { gPad->SetLogy(); }
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);

//calculate the plooting range
    double min = 0.0;
    double max = hist1->GetMaximum();
    if (hist1->GetMinimum() == 0.0)
    {
    min = get_non0_minimum(hist1,detail);
    }
    else
    {
    min = hist1->GetMinimum();
    }    
    
    set_histogram_min_max(hist2, min, max, detail);
    
    max = 1.05 * max;
    min = 0.80 * min;

//plooting
    hist1->SetMaximum(max);
    hist1->SetMinimum(min);
    format_histogram(hist1, 1, 1);
    hist1->Draw("e1");
    format_histogram(hist2, 2, 2);
    hist2->Draw("e1same");

//assign the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 2, x1, y1, x2, y2);

    TLegend *leg01 = new TLegend(x1, y1, x2, y2);
    leg01->AddEntry(hist1,label1,"l");
    leg01->AddEntry(hist2,label2,"l");
    leg01->SetFillColor(0);
    leg01->SetLineWidth(1);
    leg01->SetLineColor(0);
    leg01->SetFillStyle(1001);
    leg01->Draw();

    print_plots(c01, path, fileout);
}


void plot_3histograms(TH1D *hist1 = 0, TString label1 = "label1", TH1D *hist2 = 0, TString label2 = "label2", TH1D *hist3 = 0, TString label3 = "label3", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
{
// plots three distributions in the same plot

// check if there are any histograms inputed
if (hist1 == 0) { cout << "Histogram1 is not provided!" << endl; return; } 
if (hist2 == 0) { cout << "Histogram2 is not provided!" << endl; return; } 
if (hist3 == 0) { cout << "Histogram3 is not provided!" << endl; return; } 

    if (detail) { cout<<"Ploting "<<fileout<<endl; }
// declare and configure the canvas
    TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    if (logscale) { gPad->SetLogy(); }
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);

//calculate the plooting range
    double min = 0.0;
    double max = hist1->GetMaximum();
    if (hist1->GetMinimum() == 0.0)
    {
    min = get_non0_minimum(hist1,detail);
    }
    else
    {
    min = hist1->GetMinimum();
    }    
    
    set_histogram_min_max(hist2, min, max, detail);
    set_histogram_min_max(hist3, min, max, detail);
    
    max = 1.3 * max;
    min = 0.7 * min;

//plooting
    hist1->SetMaximum(max);
    hist1->SetMinimum(min);
    format_histogram(hist1, 1, 1);
    hist1->Draw("e1");
    format_histogram(hist2, 2, 2);
    hist2->Draw("e1 same");
    format_histogram(hist3, 4, 4);
    hist3->Draw("e1 same");

//assign the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 3, x1, y1, x2, y2);

    TLegend *leg01 = new TLegend(x1, y1, x2, y2);
    leg01->AddEntry(hist1,label1,"l");
    leg01->AddEntry(hist2,label2,"l");
    leg01->AddEntry(hist3,label3,"l");
    leg01->SetFillColor(0);
    leg01->SetLineWidth(1);
    leg01->SetLineColor(0);
    leg01->SetFillStyle(1001);
    leg01->Draw();

    print_plots(c01, path, fileout);
}


void plot_3graphs(TGraph *gr1 = 0, TGraph *point1 = 0, TString label1 = "label1", TGraph *gr2 = 0, TGraph *point2 = 0, TString label2 = "label2", TGraph *gr3 = 0, TGraph *point3 = 0, TString label3 = "label3", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
{
// plots three distributions in the same plot

// check if there are any histograms inputed
if (gr1 == 0) { cout << "Graph1 is not provided!" << endl; return; } 
if (gr2 == 0) { cout << "Graph2 is not provided!" << endl; return; } 
if (gr3 == 0) { cout << "Graph3 is not provided!" << endl; return; } 

    if (detail) { cout<<"Ploting "<<fileout<<endl; }
// declare and configure the canvas
    TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    if (logscale) { gPad->SetLogy(); }
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);

//plooting
   gr1->Draw("AL");
   if (point1 != 0)
	{
   	point1->Draw("*");
   	point1->SetMarkerStyle(21);
   	point1->SetMarkerSize(3);
	}
   gr2->Draw("L");
   gr2->SetLineColor(2);
   if (point2 != 0)
	{
	point2->Draw("*");
	point2->SetMarkerColor(2);
	point2->SetMarkerStyle(21);
	point2->SetMarkerSize(3);
	}
   gr3->Draw("L");
   gr3->SetLineColor(4);
   if (point3 != 0)
	{
   	point3->Draw("*");
   	point3->SetMarkerColor(4);
   	point3->SetMarkerStyle(21);
   	point3->SetMarkerSize(3);
	}

//assign the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 3, x1, y1, x2, y2);

    TLegend *leg01 = new TLegend(x1, y1, x2, y2);
    leg01->AddEntry(gr1,label1,"l");
    leg01->AddEntry(gr2,label2,"l");
    leg01->AddEntry(gr3,label3,"l");
    leg01->SetFillColor(0);
    leg01->SetLineWidth(1);
    leg01->SetLineColor(0);
    leg01->SetFillStyle(1001);
    leg01->Draw();

    print_plots(c01, path, fileout);
}



void plot_4histograms(TH1D *hist1 = 0, TString label1 = "label1", TH1D *hist2 = 0, TString label2 = "label2", TH1D *hist3 = 0, TString label3 = "label3", TH1D *hist4 = 0, TString label4 = "label4", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
{
// plots four distributions in the same plot

// check if there are any histograms inputed
if (hist1 == 0) { cout << "Histogram1 is not provided!" << endl; return; } 
if (hist2 == 0) { cout << "Histogram2 is not provided!" << endl; return; } 
if (hist3 == 0) { cout << "Histogram3 is not provided!" << endl; return; }
if (hist4 == 0) { cout << "Histogram4 is not provided!" << endl; return; } 

    if (detail) { cout<<"Ploting "<<fileout<<endl; }
// declare and configure the canvas
    TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    if (logscale) { gPad->SetLogy(); }
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);

//calculate the plooting range
    double min = 0.0;
    double max = hist1->GetMaximum();
    if (hist1->GetMinimum() == 0.0)
    {
    min = get_non0_minimum(hist1,detail);
    }
    else
    {
    min = hist1->GetMinimum();
    }    
    
    set_histogram_min_max(hist2, min, max, detail);
    set_histogram_min_max(hist3, min, max, detail);
    set_histogram_min_max(hist4, min, max, detail);
    
    max = 1.5 * max;
    min = 0.7 * min;

//plooting
    hist1->SetMaximum(max);
    hist1->SetMinimum(min);
    format_histogram(hist1, 1, 1);
    hist1->Draw("e1");
    format_histogram(hist2, 2, 2);
    hist2->Draw("e1 same");
    format_histogram(hist3, 4, 4);
    hist3->Draw("e1 same");
    format_histogram(hist4, 6, 6);
    hist4->Draw("e1 same");

//assign the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 4, x1, y1, x2, y2);

    TLegend *leg01 = new TLegend(x1, y1, x2, y2);
    leg01->AddEntry(hist1,label1,"l");
    leg01->AddEntry(hist2,label2,"l");
    leg01->AddEntry(hist3,label3,"l");
    leg01->AddEntry(hist4,label4,"l");
    leg01->SetFillColor(0);
    leg01->SetLineWidth(1);
    leg01->SetLineColor(0);
    leg01->SetFillStyle(1001);
    leg01->Draw();

    print_plots(c01, path, fileout);
}


void ratio_2histograms(TH1D *hist1 = 0, TH1D *hist2 = 0, TString label = "label", string path= "../output/", string fileout = "test", string legend_position = "top_left", bool detail = false)
{
// plots the two distributions

// check if there are any histograms inputed
if (hist1 == 0) { cout << "Histogram1 is not provided!" << endl; return; } 
if (hist2 == 0) { cout << "Histogram2 is not provided!" << endl; return; } 

TH1D *ratio;
ratio = static_cast<TH1D*>(hist1->Clone());
ratio->Divide(hist1,hist2,1.,1.,"B");

    if (detail) { cout<<"Ploting "<<fileout<<endl; }
// declare and configure the canvas
    TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);

//calculate the plooting range
    //double min = 0.0;
    //double max = ratio->GetMaximum();
    //if (ratio->GetMinimum() == 0.0)
    //{
    //min = get_non0_minimum(ratio,detail);
    //}
    //else
    //{
    //min = ratio->GetMinimum();
    //}
    
    //max = 1.3 * max;
    //min = 0.7 * min;

//plooting
    //ratio->SetMaximum(max);
    //ratio->SetMinimum(min);
    format_histogram(ratio, 2, 1);
    ratio->Draw("e1");

//assign the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 1, x1, y1, x2, y2);

    TLegend *leg01 = new TLegend(x1, y1, x2, y2);
    leg01->AddEntry(ratio,label,"l");
    leg01->SetFillColor(0);
    leg01->SetLineWidth(1);
    leg01->SetLineColor(0);
    leg01->SetFillStyle(1001);
    leg01->Draw();

    print_plots(c01, path, fileout);
}

void plot_efficiency(TH1D *hratio, string prefix, string fileout, string path= "../output/trigger_eff/", string legend_position = "top_left", bool detail = false)
{
//plots the correction factor

    if (detail) { cout<<"Ploting "<<fileout<<endl; }
//declare and configure the canvas
    TCanvas *c01 = new TCanvas("c01","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    //gPad->SetLogy();
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);

    hratio->SetMinimum(0);
    double max = hratio->GetMaximum();
    hratio->SetMaximum(max*1.3);
    format_histogram(hratio, 4, 2);
    hratio->Draw("e1");

//assign the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 1, x1, y1, x2, y2);

    TLegend *leg01 = new TLegend(x1, y1, x2, y2);
    leg01->AddEntry(hratio,"Trigger Efficiency","l");
    leg01->SetFillColor(0);
    leg01->SetLineWidth(1);
    leg01->SetLineColor(0);
    leg01->SetFillStyle(1001);
    leg01->Draw();

    print_plots(c01, path, prefix + fileout);
}


void plot_six_dist(TH1D *dist1, TString label1, TH1D *dist2, TString label2, TH1D *dist3, TString label3, TH1D *dist4, TString label4, TH1D *dist5, TString label5, TH1D *dist6, TString label6, string path, string prefix, string name, string legend_position = "top_left", bool logscale = true, bool detail = false)
{
//declaring the canvas
    if (detail) { cout << "Ploting " << name << endl; }
    TCanvas *c1 = new TCanvas("c1","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gStyle->SetPalette(1);
    gStyle->SetPaintTextFormat("4.2g");
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);
    if (logscale) { gPad->SetLogy(); }

//calculate the plooting range
    double min = 0.0;
    double max = dist1->GetMaximum();
    if (dist1->GetMinimum() == 0.0)
    {
    min = get_non0_minimum(dist1,detail);
    }
    else
    {
    min = dist1->GetMinimum();
    }    
    
    set_histogram_min_max(dist2, min, max, detail);
    set_histogram_min_max(dist3, min, max, detail);
    set_histogram_min_max(dist4, min, max, detail);
    set_histogram_min_max(dist5, min, max, detail);
    set_histogram_min_max(dist6, min, max, detail);
        
    max = 1.3 * max;
    min = 0.7 * min;

//plooting
    dist1->SetMaximum(max);
    dist1->SetMinimum(0);
    dist1->SetLineWidth(4);
    dist1->SetLineColor(2);
    dist1->SetLineStyle(1);
    dist1->Draw("e1");
    dist2->SetLineWidth(4);
    dist2->SetLineColor(3);
    dist2->SetLineStyle(2);
    dist2->Draw("e1same");
    dist3->SetLineWidth(4);
    dist3->SetLineColor(4);
    dist3->SetLineStyle(3);
    dist3->Draw("e1same");
    dist4->SetLineWidth(4);
    dist4->SetLineColor(8);
    dist4->SetLineStyle(4);
    dist4->Draw("e1same");
    dist5->SetLineWidth(4);
    dist5->SetLineColor(6);
    dist5->SetLineStyle(5);
    dist5->Draw("e1same");
    dist6->SetLineWidth(4);
    dist6->SetLineColor(7);
    dist6->SetLineStyle(6);
    dist6->Draw("e1same");

//sets and draw the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 6, x1, y1, x2, y2);

    TLegend *leg00 = new TLegend(x1,y1,x2,y2);
    leg00->AddEntry(dist1,label1,"l");
    leg00->AddEntry(dist2,label2,"l");
    leg00->AddEntry(dist3,label3,"l");
    leg00->AddEntry(dist4,label4,"l");
    leg00->AddEntry(dist5,label5,"l");
    leg00->AddEntry(dist6,label6,"l");
    leg00->SetFillColor(0);
    leg00->SetLineStyle(1);
    leg00->SetLineWidth(1);
    leg00->SetLineColor(0);
    leg00->SetFillStyle(1001);
    leg00->Draw();

//setting the output files
   string fileout = prefix + name;
   string out_png = path + "png/" + fileout + ".png";
   string out_c = path + "c/" + fileout + ".C";
   string out_eps = path + "eps/" + fileout + ".eps";
    
//save the file and close the canvas
    c1->Print( out_png.c_str() );
    c1->Print( out_c.c_str() );
    c1->Print( out_eps.c_str() );
    c1->Close();
 
}

void plot_6graph(TGraph *gr1 = 0, TGraph *point1 = 0, TString label1 = "", TGraph *gr2 = 0, TGraph *point2 = 0, TString label2 = "", TGraph *gr3 = 0, TGraph *point3 = 0, TString label3 = "", TGraph *gr4 = 0, TGraph *point4 = 0, TString label4 = "", TGraph *gr5 = 0, TGraph *point5 = 0, TString label5 = "", TGraph *gr6 = 0, TGraph *point6 = 0, TString label6 = "", string path = "/", string name = "test", string legend_position = "top_left", bool logscale = true, bool detail = false)
{
//declaring the canvas
    if (detail) { cout << "Ploting " << name << endl; }
    TCanvas *c1 = new TCanvas("c1","Canvas",0,29,1450,870);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gStyle->SetPalette(1);
    gStyle->SetPaintTextFormat("4.2g");
    gPad->SetFillColor(0);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(2);
    gPad->SetLeftMargin(0.10);
    gPad->SetRightMargin(0.01);
    gPad->SetTopMargin(0.01);
    gPad->SetFrameBorderMode(0);
    if (logscale) { gPad->SetLogy(); }

//plooting
   gr1->Draw("AL");
   gr1->SetLineColor(1);
   gr1->SetLineWidth(3);
   if (point1 != 0)
	{
   	point1->Draw("*");
   	point1->SetMarkerStyle(21);
   	point1->SetMarkerSize(3);
   	point1->SetMarkerColor(1);
	}
   gr2->Draw("L");
   gr2->SetLineColor(2);
   gr2->SetLineWidth(3);
   if (point2 != 0)
	{
   	point2->Draw("*");
   	point2->SetMarkerStyle(21);
   	point2->SetMarkerSize(3);
   	point2->SetMarkerColor(2);
	}
   gr3->Draw("L");
   gr3->SetLineColor(4);
   gr3->SetLineWidth(3);
   if (point3 != 0)
	{
   	point3->Draw("*");
   	point3->SetMarkerStyle(21);
   	point3->SetMarkerSize(3);
   	point3->SetMarkerColor(4);
	}
   gr4->Draw("L");
   gr4->SetLineColor(3);
   gr4->SetLineWidth(3);
   if (point4 != 0)
	{
   	point4->Draw("*");
   	point4->SetMarkerStyle(21);
   	point4->SetMarkerSize(3);
   	point4->SetMarkerColor(3);
	}
   gr5->Draw("L");
   gr5->SetLineColor(5);
   gr5->SetLineWidth(3);
   if (point5 != 0)
	{
   	point5->Draw("*");
   	point5->SetMarkerStyle(21);
   	point5->SetMarkerSize(3);
   	point5->SetMarkerColor(5);
	}
   gr6->Draw("L");
   gr6->SetLineColor(6);
   gr6->SetLineWidth(3);
   if (point6 != 0)
	{
   	point6->Draw("*");
   	point6->SetMarkerStyle(21);
   	point6->SetMarkerSize(3);
   	point6->SetMarkerColor(6);
	};

//sets and draw the legend
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
    set_legend_position(legend_position, 6, x1, y1, x2, y2);

    TLegend *leg00 = new TLegend(x1,y1,x2,y2);
    leg00->AddEntry(gr1,label1,"l");
    leg00->AddEntry(gr2,label2,"l");
    leg00->AddEntry(gr3,label3,"l");
    leg00->AddEntry(gr4,label4,"l");
    leg00->AddEntry(gr5,label5,"l");
    leg00->AddEntry(gr6,label6,"l");
    leg00->SetFillColor(0);
    leg00->SetLineStyle(1);
    leg00->SetLineWidth(1);
    leg00->SetLineColor(0);
    leg00->SetFillStyle(1001);
    leg00->Draw();

//setting the output files
   string out_png = path + "png/" + name + ".png";
   string out_c = path + "c/" + name + ".C";
   string out_eps = path + "eps/" + name + ".eps";
    
//save the file and close the canvas
    c1->Print( out_png.c_str() );
    c1->Print( out_c.c_str() );
    c1->Print( out_eps.c_str() );
    c1->Close();
 
}
