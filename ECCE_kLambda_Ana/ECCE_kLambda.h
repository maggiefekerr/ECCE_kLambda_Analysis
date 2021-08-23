// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef ECCE_KLAMBDA_ANA_H
#define ECCE_KLAMBDA_ANA_H

#include <fun4all/SubsysReco.h>

#include <string>
#include <memory>
#include <string>
#include <utility>  // std::pair, std::make_pair                                                                                                                                                            
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"

class Fun4AllHistoManager;
class PHCompositeNode;
class TFile;
class TNtuple;
class JetEvalStack;

class ECCE_kLambda : public SubsysReco
{
 public:

  ECCE_kLambda(const std::string &name = "ECCE_kLambda", const std::string &fname = "MyNtuple.root");

  virtual ~ECCE_kLambda();

  /** Called during initialization.
      Typically this is where you can book histograms, and e.g.
      register them to Fun4AllServer (so they can be output to file
      using Fun4AllServer::dumpHistos() method).
   */
  int Init(PHCompositeNode *topNode) override;

  /** Called for first event when run number is known.
      Typically this is where you may want to fetch data from
      database, because you know the run number. A place
      to book histograms which have to know the run number.
   */
  int InitRun(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Clean up internals after each event.
  int ResetEvent(PHCompositeNode *topNode) override;

  /// Called at the end of each run.
  int EndRun(const int runnumber) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

  /// Reset
  int Reset(PHCompositeNode * /*topNode*/) override;

  void Print(const std::string &what = "ALL") const override;

  bool Check_eKaon(PHCompositeNode *);
  bool Check_hits(PHCompositeNode *);

  void use_initial_vertex(const bool b = true) {initial_vertex = b;}

  //private:

 protected:

  //! flag to use initial vertex in track evaluator 
  bool initial_vertex = false;

  std::string detector;
  std::string outfilename;
  Fun4AllHistoManager *hm;

  TFile *outfile;
  unsigned long long int event_itt;
  gsl_rng* m_RandomGenerator;

  //*********************************
  // Energy and Position smearing

  float EMCAL_Smear(float E);
  float HCAL_Smear(float E);
  float PbWO4_Smear(float E);
  float Position_Smear(float E);

  //---------------------
  // From ejana

  double true_q2;
  double true_x;
  double true_s_e;
  double true_xpi;
  double true_ypi;
  double true_tpi;

  double have_true_dis_info = false;
  
  bool  HIT_IN_ZDC;
  bool  HIT_IN_EMCAL;
  bool  HIT_IN_HCAL;
  bool  CLUS_IN_EMCAL;
  bool  CLUS_IN_HCAL;
  bool  HIT_IN_HEC;	

  double e_beam_energy;
  double ion_beam_energy;

  double crossing_angle;

  TLorentzVector r_lelectron;
//  TLorentzVector r_lproton;

  TLorentzVector r_lscatelec;
  TLorentzVector r_l_scat_nucleon;

  TLorentzVector lproton;

  // Particle Masses
  Double_t mPionP = 0.139570;
  Double_t mPionN = 0.1349768;
  Double_t mElec = 0.000510998950;
  Double_t mNeut = 0.93965420;
  Double_t mProt = 0.9381940722; // added by Maggie Kerr, August 2, 2021 // Should I be using the missing mass instead? // 1836*mElec
  Double_t mLamb = 1.115683;
  Double_t mKaonP = 0.493677; 
  Double_t mGamma = 0;

  // Quantities we want to determine
  TVector3 eVect;
  TVector3 eVectSmeared;
  TVector3 piVect;
  TVector3 piVectSmeared;
  TVector3 kaonVect;
  TVector3 kaonVectSmeared;
  TVector3 g1Vect;
  TVector3 g1VectSmeared;
  TVector3 g2Vect;
  TVector3 g2VectSmeared;
  TVector3 nZDCPos;
  TVector3 nZDCPosSmeared;
  TVector3 lZDCPos;
  TVector3 lZDCPosSmeared;
  TLorentzVector e4Vect;
  TLorentzVector e4VectSmeared;
  TLorentzVector pi4Vect;
  TLorentzVector pi4VectSmeared;
  TLorentzVector kaon4Vect;
  TLorentzVector kaon4VectSmeared;
  TLorentzVector g14Vect;
  TLorentzVector g14VectSmeared;
  TLorentzVector g24Vect;
  TLorentzVector g24VectSmeared;
  TLorentzVector n4Vect;
  TLorentzVector n4VectSmeared;
  TLorentzVector l4Vect;
  TLorentzVector l4VectSmeared;
  TLorentzVector e4VectTruth;
  TLorentzVector pi4VectTruth;
  TLorentzVector kaon4VectTruth;
  TLorentzVector g14VectTruth;
  TLorentzVector g24VectTruth;
  TLorentzVector n4VectTruth;
  TLorentzVector l4VectTruth;
  TLorentzVector eBeam4Vect;
  TLorentzVector pBeam4Vect;
  TLorentzVector virtphoton4Vect;
  TLorentzVector t4Vect;
  TLorentzVector pmiss4Vect;
  TLorentzVector virtphoton4VectTruth;
  TLorentzVector t4VectTruth;
  TLorentzVector pmiss4VectTruth;
  TLorentzVector s4Vect; // added by Maggie Kerr, August 2, 2021
  TVector3 trackVect;
  TLorentzVector track4Vect;

  Double_t nEDep;
  Double_t nEDepSmeared;
  Double_t nTheta;
  Double_t nThetaSmeared;
  Double_t nPhi;
  Double_t nPhiSmeared;
  Double_t nPMag;
  Double_t nPMagSmeared;

  Double_t lEDep;
  Double_t lEDepSmeared;
  Double_t lTheta;
  Double_t lThetaSmeared;
  Double_t lPhi;
  Double_t lPhiSmeared;
  Double_t lPMag;
  Double_t lPMagSmeared;

  Double_t Q2;
  Double_t W;
  Double_t t;
  Double_t xb;
  Double_t xi;
  Double_t Q2_truth;
  Double_t W_truth;
  Double_t t_truth;
  Double_t xb_truth;
  Double_t xi_truth;
  Double_t s;
  /*Double_t y;
  Double_t e;*/

  Int_t ZDC_hit;
  Int_t EEMC_hit;

  // Histogram Definitons

  // lambda

  TH1F* h1_lTruth_E;
  TH1F* h1_lTruth_P;
  TH1F* h1_lTruth_Px;
  TH1F* h1_lTruth_Py;
  TH1F* h1_lTruth_Pz;
  TH1F* h1_lTruth_Theta;
  TH1F* h1_lTruth_Phi;
  TH2F* h1_lTruth_PxPy;
  TH2F* h1_lTruth_ThetaP;

  // neutron

  TH1F* h1_nTruth_E;
  TH1F* h1_nTruth_P;
  TH1F* h1_nTruth_Px;
  TH1F* h1_nTruth_Py;
  TH1F* h1_nTruth_Pz;
  TH1F* h1_nTruth_Theta;
  TH1F* h1_nTruth_Phi;
  TH2F* h1_nTruth_PxPy;
  TH2F* h1_nTruth_ThetaP;

  // scattered electron

  TH1F* h1_eTruth_E;
  TH1F* h1_eTruth_P;
  TH1F* h1_eTruth_Px;
  TH1F* h1_eTruth_Py;
  TH1F* h1_eTruth_Pz;
  TH1F* h1_eTruth_Theta;
  TH1F* h1_eTruth_Phi;
  TH2F* h1_eTruth_PxPy;
  TH2F* h1_eTruth_ThetaP;

  // kaon

  TH1F* h1_kTruth_E;
  TH1F* h1_kTruth_P;
  TH1F* h1_kTruth_Px;
  TH1F* h1_kTruth_Py;
  TH1F* h1_kTruth_Pz;
  TH1F* h1_kTruth_Theta;
  TH1F* h1_kTruth_Phi;
  TH2F* h1_kTruth_PxPy;
  TH2F* h1_kTruth_ThetaP;

  /*
  // pion

  TH1F* h1_piTruth_E;
  TH1F* h1_Truth_P;
  TH1F* h1_piTruth_Px;
  TH1F* h1_piTruth_Py;
  TH1F* h1_piTruth_Pz;
  TH1F* h1_piTruth_Theta;
  TH1F* h1_piTruth_Phi;
  TH2F* h1_piTruth_PxPy;
  TH2F* h1_piTruth_ThetaP;
  */

  // gamma 1

  TH1F* h1_g1Truth_E;
  TH1F* h1_g1Truth_P;
  TH1F* h1_g1Truth_Px;
  TH1F* h1_g1Truth_Py;
  TH1F* h1_g1Truth_Pz;
  TH1F* h1_g1Truth_Theta;
  TH1F* h1_g1Truth_Phi;
  TH2F* h1_g1Truth_PxPy;
  TH2F* h1_g1Truth_ThetaP;

  // gamma 2

  TH1F* h1_g2Truth_E;
  TH1F* h1_g2Truth_P;
  TH1F* h1_g2Truth_Px;
  TH1F* h1_g2Truth_Py;
  TH1F* h1_g2Truth_Pz;
  TH1F* h1_g2Truth_Theta;
  TH1F* h1_g2Truth_Phi;
  TH2F* h1_g2Truth_PxPy;
  TH2F* h1_g2Truth_ThetaP;

  // kinematics

  TH1F* h1_Q2_Dist;
  TH1F* h1_W_Dist;
  TH1F* h1_t_Dist;
  TH1F* h1_xb_Dist;
  TH1F* h1_xi_Dist;

  // kinematics truth

  TH1F* h1_Q2Truth_Dist;
  TH1F* h1_WTruth_Dist;
  TH1F* h1_tTruth_Dist;
  TH1F* h1_xbTruth_Dist;
  TH1F* h1_xiTruth_Dist;

  // kinematics coverage for Q2
  TH2F* h2_tTruthvQ2_0_25_Dist;
  TH2F* h2_tTruthvQ2_25_375_Dist;
  TH2F* h2_tTruthvQ2_375_5_Dist;
  TH2F* h2_tTruthvQ2_5_625_Dist;
  TH2F* h2_tTruthvQ2_625_75_Dist;
  TH2F* h2_tTruthvQ2_75_875_Dist;
  TH2F* h2_tTruthvQ2_875_10_Dist;
  TH2F* h2_tTruthvQ2_10_1125_Dist;
  TH2F* h2_tTruthvQ2_g1125_Dist;

  TH1F* h1_trackCharge_Dist;
  TH1F* h1_trackPz_Dist;
  TH1F* h1_nTracks_Dist;
  TH2F* h2_trackPvsTheta_Dist; 

};

#endif // ECCE_DEMP_ANA_H

