// Pedro Cipriano, May 2015
// DESY, CMS
// Last Update: 14 May 2015
//
// Provides usefull functions to physics analysis
//

#include <TMath.h>

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

double delta_r(double eta1, double phi1, double eta2, double phi2)
{

bool test = false;

double r = -1.0;

if (test) { cout << "Phi1 = " << phi1 << " Eta1 = " << eta1 << endl; }
if (test) { cout << "Phi2 = " << phi2 << " Eta2 = " << eta2 << endl; }

double delta_phi = TMath::ACos(TMath::Cos(phi1-phi2));

if (test) { cout << "Delta Phi = " << delta_phi << endl; }

r = TMath::Sqrt((eta1-eta2)*(eta1-eta2) + delta_phi*delta_phi);

if (test) { cout << "R = " << r << endl; }

return r;
}
