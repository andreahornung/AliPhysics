#if !defined (__CINT__) || defined (__CLING__)
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskPPvsRT_TPCTOF.h"
#include "AliAnalysisFilter.h"
#include "TInterpreter.h"
#include "TChain.h"
#include <TString.h>
#include <TList.h>
#endif

AliAnalysisTaskPPvsRT_TPCTOF* AddTaskPPvsRT_TPCTOF(
		bool AnalysisMC     = kFALSE,
		int  system         = 1, // 0(pp) & 1 (Pb-Pb)
		const double TrkLCut = 5.0,
		const char* Period  = "l",
		const double MeanCh = 7.266,
		const bool isLower  = kTRUE,
	        const int ncl = 70, 
		const char* flag_container = "tpc_tof"		
		)   
{

	// get the manager via the static access member. since it's static, you don't need
	// an instance of the class to call the function
	AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
	if (!mgr) {
		return 0x0;
	}
	// get the input event handler, again via a static method. 
	// this handler is part of the managing system and feeds events
	// to your task
	if (!mgr->GetInputEventHandler()) {
		return 0x0;
	}

	AliAnalysisFilter* trackFilterGolden = new AliAnalysisFilter("trackFilter");
	AliESDtrackCuts* esdTrackCutsGolden = AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(kFALSE,1);
	if(isLower){
	esdTrackCutsGolden->SetMinNCrossedRowsTPC(60);
	esdTrackCutsGolden->SetMaxDCAToVertexZ(1);
		}else{
	esdTrackCutsGolden->SetMinNCrossedRowsTPC(80);
	esdTrackCutsGolden->SetMaxChi2PerClusterTPC(5);
	esdTrackCutsGolden->SetMaxDCAToVertexZ(3);}
	trackFilterGolden->AddCuts(esdTrackCutsGolden);

	AliAnalysisFilter* trackFilterTPC = new AliAnalysisFilter("trackFilterTPC");
	AliESDtrackCuts* esdTrackCutsTPC = AliESDtrackCuts::GetStandardTPCOnlyTrackCuts();
	trackFilterTPC->AddCuts(esdTrackCutsTPC);

	AliAnalysisFilter* trackFilterGolden2015PbPb = new AliAnalysisFilter("trackFilter2015PbPb");
  	AliESDtrackCuts* esdTrackCutsGolden2015PbPb = AliESDtrackCuts::GetStandardITSTPCTrackCuts2015PbPb(kFALSE,1,kTRUE ,kFALSE);
  	trackFilterGolden2015PbPb->AddCuts(esdTrackCutsGolden2015PbPb);


	// by default, a file is open for writing. here, we get the filename
	TString fileName = AliAnalysisManager::GetCommonFileName();
	//fileName += Form(":%.2f-%.2f",minCent,maxCent);      // create a subfolder in the file
	//fileName += ":Output";      // create a subfolder in the file


	// now we create an instance of your task
	AliAnalysisTaskPPvsRT_TPCTOF* task = new AliAnalysisTaskPPvsRT_TPCTOF("taskHighPtDeDxpp");   
	if(!task) return 0x0;

	TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"
	task->SetAnalysisType(type);
	task->SetAnalysisMC(AnalysisMC);
//	task->SetAddLowPt(LowpT);
	task->SetPeriod(Period);
	task->SetMeanCh(MeanCh);

	if(system==1){
		task->SetAnalysisPbPb(kTRUE);
		task->SetMinCent(0.0);
		task->SetMaxCent(90.0);
	}
	else
		task->SetAnalysisPbPb(kFALSE);
	
	task->SetNcl(ncl);
        task->SetLeadingCut(TrkLCut);
	task->SetDebugLevel(0);
	task->SetEtaCut(0.8);
	task->SetTrackFilterGolden(trackFilterGolden);
	task->SetTrackFilterTPC(trackFilterTPC);
	task->SetTrackFilter2015PbPb(trackFilterGolden2015PbPb);
//	task->SetAnalysisTask(PostCalib);
//	task->SetAnalysisPID(MakePid);

	// add your task to the manager
	mgr->AddTask(task);
	// your task needs input: here we connect the manager to your task
	mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
	// same for the output
	mgr->ConnectOutput(task,1,mgr->CreateContainer(Form("MyOutputContainer_%s_ncl_%d",flag_container,ncl), TList::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
	// in the end, this macro returns a pointer to your task. this will be convenient later on
	// when you will run your analysis in an analysis train on grid
	return task;
}

