#ifndef EcalTBMCInfoProducer_H
#define EcalTBMCInfoProducer_H
/*
 * \file EcalTBMCInfoProducer.h
 *
 *
*/
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/EcalTestBeam/interface/PEcalTBInfo.h"
#include "Geometry/EcalTestBeam/interface/EcalTBCrystalMap.h"

#include "Math/GenVector/Rotation3D.h"

class EcalTBMCInfoProducer: public edm::stream::EDProducer<>
{  
public:
  
  /// Constructor
  explicit EcalTBMCInfoProducer(const edm::ParameterSet& ps);
  
  /// Destructor
  virtual ~EcalTBMCInfoProducer();
  
  /// Produce digis out of raw data
  void produce(edm::Event & event, const edm::EventSetup& eventSetup);
  
private:

  double beamEta;
  double beamPhi;
  double beamTheta;

  int crysNumber;

  double beamXoff;
  double beamYoff;

  double partXhodo;
  double partYhodo;

  EcalTBCrystalMap * theTestMap;

  ROOT::Math::Rotation3D * fromCMStoTB;

  edm::EDGetTokenT<edm::HepMCProduct> GenVtxToken;
};

#endif
