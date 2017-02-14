#ifndef ALIANALYSISTASKEMCALJETSPECTRA8TEVTRIGGERQA_H
#define ALIANALYSISTASKEMCALJETSPECTRA8TEVTRIGGERQA_H
/**
 * \file AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA.h
 * \brief Declaration of class AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA
 *
 * In this header file the class AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA is declared.
 * This is a jet task that calculates the EMCal trigger spectra and does
 * additional QA for the EMCal trigger for the 8 TeV jet spectra analysis
 *
 * \author Andrew Castro <andrew.john.castro@cern.ch>, University of Tennessee
 * \date Feb 05, 2017
 */

/* Copyright(c) 1998-2017, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

#include "AliAnalysisTaskEmcalJet.h"
#include "THistManager.h"

/**
 * \class AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA
 * \brief Implementation of a EMCal spectra task and QA for EMCal triggers
 *
 * This class in an implementation of a trigger QA for the EMCal
 * It derives from AliAnalysisTaskEmcalJet.
 * It also performs a QA of the cluster-track matching.
 * Note: if jets are not used this class can be simplified by deriving
 * from AliAnalysisTaskEmcal and removing the functions DoJetLoop()
 * and AllocateJetHistograms().
 */
class AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA : public AliAnalysisTaskEmcalJet {
 public:

  AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA()                                               ;
  AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA(const char *name)                               ;
  virtual ~AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA()                                      ;

  void                        UserCreateOutputObjects()                         ;
  void                        Terminate(Option_t *option)                       ;

 protected:
  void                        ExecOnce()                                        ;
  Bool_t                      FillHistograms()                                  ;
  Bool_t                      Run()                                             ;

  void                        AllocateJetHistograms()                           ;
  void                        AllocateTrackHistograms()                         ;
  void                        AllocateClusterHistograms()                       ;
  void                        AllocateCellHistograms()                          ;

  void                        DoJetLoop()                                       ;
  void                        DoTrackLoop()                                     ;
  void                        DoClusterLoop()                                   ;
  void                        DoCellLoop()                                      ;

  THistManager                fHistManager                                      ;///< Histogram manager

 private:
  AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA(const AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA&)           ; // not implemented
  AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA &operator=(const AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA&); // not implemented

  /// \cond CLASSIMP
  ClassDef(AliAnalysisTaskEmcalJetSpectra8TeVTriggerQA, 7);
  /// \endcond
};
#endif
