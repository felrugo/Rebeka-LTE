#include "RebGame.h"

extern "C"
{

	__declspec(dllexport) void LoadGame(IGame **IG)
	{
		*IG = new RebGame;
	}

	__declspec(dllexport) void ReleaseGame(IGame **IG)
	{
		delete *IG;
	}

}

void RebGame::Init()
{

	
	rimba.LoadModules(&gdc);
	



	/*CreateWindowManager(&winm);
	winm->Init();
	winm->CreateWin("Launcher", 1280, 720, 100, 100);
	winm->EnableRender("Launcher");
	window = winm->GetWindow("Launcher");*/


	/*CreateMEH(&meh);
	mGDC->window = window;
	mGDC->winm = winm;
	mGDC->meh = meh;*/

	//mGDC->meh->Init(mGDC);

	//CreateRenderDevice(&rd);
	//rd->Init(mGDC);
	//rd->SetVP(1280, 720);

	//CreateEntitySystem(&ies, mGDC);

	//CreateAudioDevice(&iad);
	/*ras.GetAudioDevice()->Init();
	ras.GetAudioDevice()->GetMusicPlayer()->Init();
	ras.GetAudioDevice()->GetMusicPlayer()->SetSource(rfs->Search("daft.mp3", "Music").rpath);
	ras.GetAudioDevice()->GetMusicPlayer()->Play();*/
	
	//iad->Init();
	//ras.GetAudioDevice()->GetSoundSystem()->Test();

	

	//RebFile FileTest("daft.mp3");

	
	/*std::vector<TComponent*> tcomps;
	TComponent * viewcompt = new TCompVisViewport();
	TComponent * inpconp = new TCompInpBasicControl();
	tcomps.push_back(viewcompt);
	tcomps.push_back(inpconp);
	res->GetTemplateManager()->CreateEntTemp("tviewport", tcomps);
	Entity * ent = res->GetTemplateManager()->CreateEntByTemp("testviwe", "tviewport");
	res->GetTemplateManager()->CreateEntByTemp("Ter1", "Terrain");
	ent->SetPos(RebVector(0.0f, 0.0f, 0.0f));
	static_cast<CompVisViewport*>(ent->GetComponent("CompVisViewport"))->SetActiveViewport();*/


	//rd->GetEnv()->CreateTerrain();


	gdc.rd->GetVertexCacheManager()->CreateCacheFromFile("testbox1", gdc.rfs->Search(".*/phybox.obj")[0]);
	//rd->GetVertexCacheManager()->CreateCacheFromFile("testbox2", rfs->Search("phybox.obj").rpath);
	//rd->GetVertexCacheManager()->CreateCacheFromFile("testbox3", rfs->Search("phybox.obj").rpath);
	//rd->GetVertexCacheManager()->CreateCacheFromFile("testbox4", rfs->Search("phybox.obj").rpath);
	//rd->GetVertexCacheManager()->CreateCacheFromFile("kepkeret", rfs->Search("kepkeret.obj").rpath);
	////rd->GetVertexCacheManager()->CreateCacheFromFile("szek", rfs->Search("Chair N280615.3DS").rpath);
	////
	//gdc.rd->GetVertexCacheManager()->GetVertexCache("testbox1")->GetTrans()->Scale(5.0f, 5.0f, 5.0f);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox2")->GetTrans()->Translate(0, 1, 0);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox3")->GetTrans()->Scale(0.05f, 0.05f, 0.05f);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox3")->GetTrans()->Translate(0, 1, 4);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox4")->GetTrans()->Scale(0.01f, 0.01f, 0.01f);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox4")->GetTrans()->Translate(2, 24, 0);
	//rd->GetVertexCacheManager()->GetVertexCache("kepkeret")->GetTrans()->Scale(0.1f, 0.1f, 0.1f);
	//rd->GetVertexCacheManager()->GetVertexCache("kepkeret")->GetTrans()->Translate(3, 0, -6);

	/*rd->GetVertexCacheManager()->GetVertexCache("szek")->GetTrans()->Scale(0.01f, 0.01f, 0.01f);
	rd->GetVertexCacheManager()->GetVertexCache("szek")->GetTrans()->Translate(0,1.0f,0);*/

	bool pressed = false;
	gdc.window->TrapMouse(true);

	gdc.grp = true;
}

void RebGame::GameLoop()
{
while(gdc.grp)
	{

		gdc.waem->GetEvent();
		gdc.rd->Render();
		gdc.window->SwapBuff();
   }
}

void RebGame::Release()
{

	//rimba.ReleaseModules(&gdc);

	//winm->TrapMouse(false);
	//ReleaseEntitySystem(&ies);
	///*ras.GetAudioDevice()->GetMusicPlayer()->Stop();*/
	//rd->Release();
	//winm->DisableRender("Launcher");
	//winm->DestroyWindow("Launcher");
	//winm->Release();
	//ReleaseWindowManager(&winm);
	//ReleaseRenderDevice(&rd);
	//delete rfs;
	//iad->Release();
	//ReleaseAudioDevice(&iad);
	//delete mGDC;
}