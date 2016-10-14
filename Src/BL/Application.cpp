#include "Application.h"

#include "Editor/Editor.h"

#include "BL/Scene.h"
#include "BL/SynthScene.h"
#include "BL/SynthComponentFactory.h"
#include "BL/Command.h"
#include "BL/CommandManager.h"

#include "Audio/AudioManager.h"

#include "Render/RenderManager.h"

#include "Graphics/GraphicsManager.h"

#include "Assist/Logger.h"
#include "Assist/Thread.h"
#include "Assist/ThreadManager.h"
#include "Assist/UIDGenerator.h"
#include "Assist/NameGenerator.h"

DEFINE_SINGLETON_IMPL(Application);

Application::Application()
	: mArgc(0)
	, mArgv(NULL)
	, mAppThread(NULL)
	, mEditorThread(NULL)
	, mScene(NULL)
	, mSynth(NULL)
{
}

Application::~Application()
{
	// TODO release threads
}

int Application::run(int argc, char** argv)
{
	mArgc = argc;
	mArgv = argv;

	initializeBasic();
	LOGINFO("---> Application basic functionality reached.");

	// Initialize App
	LOGINFO("Starting Application thread...");
	mAppThread = ThreadManager::getInstance()->createThread();
	Thread::ThreadTaskDelegate appStartTask = Thread::ThreadTaskDelegate(this, &Application::start);
	mAppThread->addTask(appStartTask);
	mAppThread->start();

	// Initialize Editor
	LOGINFO("Starting Editor thread...");
	mEditorThread = ThreadManager::getInstance()->createThread();
	Thread::ThreadTaskDelegate editorStartTask = Thread::ThreadTaskDelegate(this, &Application::startEditor);
	mEditorThread->addTask(editorStartTask);
	mEditorThread->start();
	
	// Wait for both App and Editor thread to finish
	Array<Thread*> threadsToJoin;
	threadsToJoin.append(mEditorThread);
	threadsToJoin.append(mAppThread);
	ThreadManager::getInstance()->joinAll(threadsToJoin);

	LOGINFO("Exiting...");
	return 0;
}

void Application::startEditor()
{
	Editor::getInstance()->startEditor(mArgc, mArgv);
}

void Application::start()
{
	LOGINFO("Waiting for editor to initialize...");
	Editor::getInstance()->initializedSignal.wait();

	initializeRender();
	initializeAudio();
	initializeScene();

	LOGINFO("---> Application total functionality reached");

	LOGINFO("Entering main loop");
	enterMainLoop();
}

void Application::initializeBasic()
{
	Logger::createSingletonInstance();
	LOGINFO("Logger created.");
	
	LOGINFO("--- BoloDemoEditor ---");
	LOGINFO("                      ");
	LOGINFO("      (rawr!)         ");
	LOGINFO("                      ");
	LOGINFO("----------------------");

	UIDGenerator::createSingletonInstance();
	NameGenerator::createSingletonInstance();
	ThreadManager::createSingletonInstance();

	Editor::createSingletonInstance();
}

namespace {

	const char gDebugShaderCodeTest[] =
		"#define NLIGHTS 2\r\n"
		"\r\n"
		"struct VertexIn\r\n"
		"{\r\n"
		"    float3 pos     : POSITION;  // in object coordinates\r\n"
		"    float3 normal  : NORMAL;    // in object coordinates\r\n"
		"    float3 tangent : TANGENT;   // in object coordinates\r\n"
		"    float2 uv      : TEXCOORD0; // in object coordinates\r\n"
		"};\r\n"
		"\r\n"
		"struct VertexOut\r\n"
		"{\r\n"
		"    float4 posH               : SV_POSITION; // in homogenous coordinates\r\n"
		"    float2 uv                 : TEXCOORD0;\r\n"
		"    float3 posV               : TEXCOORD1;   // in camera coordinates\r\n"
		"    float3 normalV            : TEXCOORD2;   // in camera coordinates\r\n"
		"    float3 tangentV           : TEXCOORD3;   // in camera coordinates\r\n"
		"    float3 lightDirV[NLIGHTS] : TEXCOORD4;   // in camera coordinates\r\n"
		"};\r\n"
		"\r\n"
		"struct LightSource\r\n"
		"{\r\n"
		"    float4 pos;\r\n"
		"    float4 dir;\r\n"
		"    float4 color;\r\n"
		"};\r\n"
		"\r\n"
		"cbuffer MatrixBuffer : register(b0)\r\n"
		"{\r\n"
		"    //float4x4 gWorldMatrix;\r\n"
		"    //float4x4 gViewMatrix;\r\n"
		"    //float4x4 gProjMatrix;\r\n"
		"    float4x4 gModelViewMatrix;\r\n"
		"    float4x4 gModelViewProjMatrix;\r\n"
		"    float4x4 gNormalMatrix;\r\n"
		"};\r\n"
		"\r\n"
		"cbuffer MaterialBuffer : register(b1)\r\n"
		"{\r\n"
		"    float4 gMatColorDiffuse;\r\n"
		"    float4 gMatColorSpecular;\r\n"
		"    float  gMatRoughness;\r\n"
		"    float  gMatF0;\r\n"
		"};\r\n"
		"\r\n"
		"cbuffer LightBuffer : register(b2)\r\n"
		"{\r\n"
		"    LightSource gLights[NLIGHTS];\r\n"
		"};\r\n"
		"\r\n"
		"Texture2D gMaterialDiffuseTex;\r\n"
		"SamplerState gMaterialDiffuseTexSampler;\r\n"
		"\r\n"
		"float safediv(float num, float den, float def)\r\n"
		"{\r\n"
		"    if (den < 0.00001)\r\n"
		"        return def;\r\n"
		"    return num / den;\r\n"
		"}\r\n"
		"\r\n"
		"VertexOut v(VertexIn IN)\r\n"
		"{\r\n"
		"    VertexOut OUT = (VertexOut)0;\r\n"
		"    \r\n"
		"    //float4 posH = float4(IN.pos, 1.0);\r\n"
		"    //posH = mul(gWorldMatrix, posH);\r\n"
		"    //posH = mul(gViewMatrix , posH);\r\n"
		"    //posH = mul(gProjMatrix , posH);\r\n"
		"    //OUT.posH = posH;\r\n"
		"    OUT.posH     = mul(gModelViewProjMatrix, float4(IN.pos,     1.0));\r\n"
		"    OUT.posV     = mul(gModelViewMatrix,     float4(IN.pos,     1.0)).xyz;\r\n"
		"    OUT.normalV  = mul(gNormalMatrix,        float4(IN.normal,  0.0)).xyz;\r\n"
		"    OUT.tangentV = mul(gNormalMatrix,        float4(IN.tangent, 0.0)).xyz;\r\n"
		"    \r\n"
		"    OUT.uv = IN.uv;\r\n"
		"    \r\n"
		"    for(int i = 0; i < NLIGHTS; ++i)\r\n"
		"        if (gLights[i].pos.w == 0) // directional or point light\r\n"
		"            OUT.lightDirV[i] = mul(gNormalMatrix,    float4(-gLights[i].dir.xyz, 0.0)).xyz;\r\n"
		"        else\r\n"
		"            OUT.lightDirV[i] = mul(gModelViewMatrix, float4(gLights[i].pos.xyz, 1.0)).xyz - OUT.posV;\r\n"
		"    \r\n"
		"    return OUT;\r\n"
		"}\r\n"
		"\r\n"
		"float4 p(VertexOut IN) : SV_TARGET\r\n"
		"{\r\n"
		"    float3 rcolor = float3(0.0,0.0,0.0);\r\n"
		"\r\n"
		"    float3 N = normalize(IN.normalV);\r\n"
		"    \r\n"
		"    for(int i = 0; i < NLIGHTS; ++i)\r\n"
		"    {\r\n"
		"        float3 L = normalize(-IN.lightDirV[i]);\r\n"
		"        float3 V = normalize(-IN.posV);\r\n"
		"        float3 H = normalize(V+L);\r\n"
		"        \r\n"
		"        float NdotL = saturate( dot( N, L ) );\r\n"
		"        float NdotH = saturate( dot( N, H ) );\r\n"
		"        float NdotV = saturate( dot( N, V ) );\r\n"
		"        float VdotH = saturate( dot( V, H ) );\r\n"
		"        float LdotH = saturate( dot( L, H ) );\r\n"
		"        \r\n"
		"        // ---------------- FRESNEL TERM ---------------- \r\n"
		"\r\n"
		"        float F0 = gMatF0;\r\n"
		"        // -- classic\r\n"
		"        float F_term = pow(1.0 - VdotH, 5.0) * (1.0 - F0) + F0;\r\n"
		"        // -- Cook-Torrance (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)\r\n"
		"        //float F_F0sqrt = sqrt(F0);\r\n"
		"        //float F_n = (1.0 + F_F0sqrt) / (1.0 - F_F0sqrt);\r\n"
		"        //float F_c = VdotH;\r\n"
		"        //float F_g = sqrt(F_n * F_n + F_c * F_c - 1.0);\r\n"
		"        //float F_a = (F_g - F_c) / (F_g + F_c);\r\n"
		"        //float F_b = ((F_g + F_c) * F_c - 1.0) / ((F_g - F_c) * F_c + 1.0);\r\n"
		"        //float F_term = 0.5 * F_a * F_a * (1 + F_b*F_b);\r\n"
		"        \r\n"
		"        // ---------------- ROUGHNESS TERM ---------------- \r\n"
		"        \r\n"
		"        float rsq = gMatRoughness * gMatRoughness;\r\n"
		"        // -- ?? method\r\n"
		"        //float R_c = 1.0;\r\n"
		"        //float R_exp = - NdotH / (gMatRoughness * gMatRoughness);\r\n"
		"        //float R_term = R_c * exp( R_exp );\r\n"
		"        // -- ?? method\r\n"
		"        //float R_a = 1.0f / ( 4.0f * rsq * pow( NdotH, 4 ) );\r\n"
		"        //float R_b = NdotH * NdotH - 1.0f;\r\n"
		"        //float R_c = rsq * NdotH * NdotH;\r\n"
		"        //float R_term = R_a * exp(R_b / R_c);\r\n"
		"        // -- Gauss method (http://content.gpwiki.org/index.php/D3DBook:(Lighting)_Cook-Torrance)\r\n"
		"        //float R_c = 0.8; // varying coeff\r\n"
		"        //float R_exp = - acos(NdotH) / rsq;\r\n"
		"        //float R_term = R_c * exp(R_exp);\r\n"
		"        // -- Beckman method (http://content.gpwiki.org/index.php/D3DBook:(Lighting)_Cook-Torrance)\r\n"
		"        //float R_NdotH2 = NdotH * NdotH;\r\n"
		"        //float R_c = safediv(1.0, rsq * R_NdotH2 * R_NdotH2, 0.0);\r\n"
		"        //float R_exp = safediv(R_NdotH2 - 1.0, rsq * R_NdotH2, 0.0);\r\n"
		"        //float R_term = R_c * exp(R_exp);\r\n"
		"        // -- Gauss method (http://renderman.pixar.com/view/cook-torrance-shader)\r\n"
		"        //float R_c = 4; // varying coeff\r\n"
		"        //float R_alpha = acos(NdotH);\r\n"
		"        //float R_exp = safediv(-R_alpha*R_alpha, rsq,0);\r\n"
		"        //float R_term = R_c * exp(R_exp);\r\n"
		"        // -- GGX method (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)\r\n"
		"        float R_num = rsq;\r\n"
		"        float R_a = NdotH * NdotH * (rsq - 1.0) + 1.0;\r\n"
		"        float R_den = 3.14 * R_a * R_a;\r\n"
		"        float R_term = safediv(R_num, R_den, 0);\r\n"
		"\r\n"
		"        // ---------------- GEOMETRY TERM ---------------- \r\n"
		"        \r\n"
		"        // -- Implicit (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)\r\n"
		"        //float G_term = NdotL * NdotV;\r\n"
		"        // -- Cook-Torrance (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)\r\n"
		"        //float G1 = 2.0 * NdotH * safediv(NdotV, VdotH, 0.0);\r\n"
		"        //float G2 = 2.0 * NdotH * safediv(NdotL, VdotH, 0.0);\r\n"
		"        //float G_term = min(1.0, min(G1, G2));\r\n"
		"        // -- Kelemen (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)\r\n"
		"        float G_term = safediv(NdotL * NdotV, VdotH * VdotH, 0.0);\r\n"
		"        // -- Neumann (http://graphicrants.blogspot.hu/2013/08/specular-brdf-reference.html)\r\n"
		"        //float G_term = safediv(NdotL * NdotV, max(NdotL, NdotV), 0.0);\r\n"
		"        \r\n"
		"        // ---------------- SUM IT UP ---------------- \r\n"
		"\r\n"
		"        //float Rs_num = F_term * R_term * G_term;\r\n"
		"        //float Rs_den = NdotV * NdotL;\r\n"
		"        //float Rs = safediv(Rs_num, Rs_den, 0.0);\r\n"
		"        float Rs_num = F_term * R_term * G_term;\r\n"
		"        //float Rs_den = 4.0 * NdotV * NdotL;\r\n"
		"        float Rs_den = NdotV * NdotL;\r\n"
		"        float Rs = safediv(Rs_num, Rs_den, 0);\r\n"
		"        \r\n"
		"        float4 diffuseTexColor = float4(1,1,1,1);//gMaterialDiffuseTex.Sample(gMaterialDiffuseTexSampler, IN.uv);\r\n"
		"\r\n"
		"        rcolor += gLights[i].color.rgb * NdotL * (gMatColorSpecular * Rs + gMatColorDiffuse * diffuseTexColor);\r\n"
		"\r\n"
		"        //rcolor = F_term;\r\n"
		"        //rcolor = R_term;\r\n"
		"        //rcolor = G_term;\r\n"
		"        //rcolor = float4(Rs,NdotL*NdotV,0,1);\r\n"
		"        //rcolor = Rs;\r\n"
		"        //if (rcolor.x == 0)\r\n"
		"        //    rcolor = float4(1, 0, 0, 1);\r\n"
		"    }\r\n"
		"    \r\n"
		"    // HDR mapping\r\n"
		"    //rcolor = rcolor / (0.5 + rcolor);\r\n"
		"\r\n"
		"    return float4(rcolor, 1.0);\r\n"
		"}\r\n"
		"\r\n";
}

#include "Render/RenderShader.h"
#include "Render/RenderMaterial.h"
#include "Render/RenderMesh.h"
#include "Render/RenderBuffer.h"
#include "Render/RenderObject.h"  
#include "Render/RenderViewport.h"
#include "Render/RenderCamera.h" 
#include "Render/RenderCommon.h"
#include "Render/RenderScene.h"
#include "Render/RenderLightSource.h"

#include "Mesh.h"
#include "GeometryGenerator.h"

void Application::initializeScene()
{
	LOGINFO("Initializing scene");
	
	CommandManager::createSingletonInstance();

	SynthComponentFactory::createSingletonInstance();

	//mScene = PropertyOwner::create<Scene>();
	mSynth = new SynthScene(Editor::getInstance()->getAudioEditorWindowHandle());


	// TEST ONLY

	RenderViewport* vp = RenderManager::getInstance()->createViewport();
	vp->setRectangle(0,0,526,447);

	RenderShader* shader = RenderManager::getInstance()->createShader();
	shader->initialize(gDebugShaderCodeTest, gDebugShaderCodeTest);
	RenderMaterial* material = RenderManager::getInstance()->createMaterial(shader);
	material->mColorDiffuse = Vector3(0.5f, 0.0f, 0.2f, 1.0f);
	material->mColorSpecular = Vector3(1.0f, 1.0f, 1.0f, 1.0f);
	material->mRoughness = 0.7f;
	material->mReflectance = 0.7f;

	RenderIndexBuffer* iBuf = RenderManager::getInstance()->createIndexBuffer();
	RenderVertexBuffer* vBuf = RenderManager::getInstance()->createVertexBuffer();
	Mesh m;
	GeometryGenerator::generateSphere(32, 64, m.mIndexData, m.mVertexData);
	iBuf->setIndexData(m.getIndexData().data(), m.getIndexCount());
	vBuf->setVertexData((RenderBufferVertexType*)m.getVertexData().data(), m.getVertexCount());
	RenderMesh* mesh = RenderManager::getInstance()->createMesh(iBuf, vBuf);

	RenderScene* scene = RENDER_NEW(RenderScene)();
	RenderObject* obj = scene->createObject(mesh, material);
	obj->setWorldPosition(Vector3(0,0,0));

	RenderCamera* cam = scene->createCamera();
	cam->setWorldPosition(Vector3(0.0f, 0.3f, -3.0f));
	cam->setFovY(Math::Deg2Rad(90.0f));
	cam->setCameraAxes(Vector3::UNIT_Z, Vector3::UNIT_Y);
	vp->setCamera(cam);

	RenderLightSource* light0 = scene->createLightSource();
	light0->setIntensity(Color(1, 1, 1, 1));
	light0->setWorldPosition(Vector3(100, 0, 0, 0));
	light0->lookAt(Vector3::ZERO, Vector3::UNIT_Y);

	// TEST ONLY
}

void Application::initializeRender()
{
	LOGINFO("Initializing graphics subsystems");

	Editor* editor = Editor::getInstance();

	// 3D Render

	RenderManager::createSingletonInstance();
	RenderManager* renderMgr = RenderManager::getInstance();
	renderMgr->initDx(editor->getSceneEditorWindowHandle());

	// 2D Render

	GraphicsManager::createSingletonInstance();
	GraphicsManager* graphicsMgr = GraphicsManager::getInstance();
	graphicsMgr->init();
}

void Application::initializeAudio()
{
	LOGINFO("Initializing Audio subsystem");
// 	AudioManager::createSingletonInstance();
// 	AudioManager* audioMgr = AudioManager::getInstance();
// 	audioMgr->init();
}

int Application::enterMainLoop()
{
	for (;;)
	{
		// TODO process messages, break loop if necessary
		
		CommandManager::getInstance()->processCommands();

		// Render 3D view
		RenderManager::getInstance()->renderOneFrame();

		// Render 2D views
		GraphicsManager::getInstance()->renderOneFrame();

		// Sleep thread for a while...
		ThreadManager::getInstance()->sleepCurrentThread(5);
	}
	return 0;
}
