#include "testscene.h"
//#include "ctPlane.h"
#include "ctClickablePlane.h"
#include "ctShaderManager.h"
#include "ctWindow.h"
#include "ctTime.h"
#include "shaders.h"
#include "ctInput.h"
#include "ctInputEvent.h"
#include "hanoj/hBlock.h"
#include <QDesktopWidget>
#include "ctRand.h"

#define Input GetWindow()->GetInput()->GetInputHelper()

testScene::testScene()
{
}

testScene::testScene(ctShaderManager * t_shaderManager) : ctScene(t_shaderManager)
{}

testScene::testScene(ctShaderManager * t_shaderManager, QOpenGLContext * t_OpenGLContext) : ctScene(t_shaderManager, t_OpenGLContext)
{}

testScene::~testScene()
{}

void testScene::Init()
{
//    QDesktopWidget *mydesk;
//    mydesk
    ctScene::Init();
    m_lastFPS = 0;
    dragMode = false;
    m_selected = 0;
    m_isClicked = "not";

    qDebug()<<"init testScene";
    SetDefault(GetShaderManager(), 0, GetOpenGLContext());
    m_plane2 = new ctPlane(GetShaderManager(), 0, GetOpenGLContext(), QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);
    m_plane = new ctClickablePlane(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,50,0), QVector3D(-50,-50,0), ctPlane::Textured);
    m_back = new ctPlane(GetShaderManager(), this,GetOpenGLContext(), QVector3D(512,384,0.5), QVector3D(-512, -384, 0.5), ctPlane::Textured);
    m_timer = new ctTimer();

    m_block = new Block(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,10,1), QVector3D(-50,-10,1), ctPlane::Textured, 7,Block::BC_BLUE);
    m_timer->SetTimer(5000, true);
    m_timer->GetDelegat()->AppendConnect(this, &testScene::TimerTest);
    m_plane2->InitShader("texturedPlaneShader");
    //m_plane->InitShader("texturedPlaneShader");
    m_plane2->SetTexture("D:\\OpenGLEperemental\\OpenGLTest\\txture.png");//(":/texture/txture.png");//("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    m_plane->SetTexture(":/texture/txture.png");//("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    m_back->SetTexture(":/texture/back.jpg");
    m_block->SetTexture(":/texture/blue_7.png");

    m_block->Init();
    m_plane->Init();
    m_back->Init();


    ctObject* rootTransform = new ctObject();
    rootTransform->GetTransform()->Move(QVector3D(0,0,0));
    double scale = 1;//GetWindow()->GetDevicePixelRatioCoff();
	m_plane->GetTransform()->Scale(QVector3D(1,1,1));
    m_plane->GetTransform()->SetParent(rootTransform->GetTransform());
    m_back->GetTransform()->SetParent(rootTransform->GetTransform());
    //m_block->GetTransform()->SetParent(rootTransform->GetTransform());
    rootTransform->GetTransform()->Scale(QVector3D(scale,scale,scale));

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, GetWindow()->width(), GetWindow()->height());
    if(! ctTime::GetTime())//Time)
    {qDebug()<<"Fuck\n";}
    m_frame = 0;


    AddObject(m_back);
    AddObject(m_block);
    AddObject(m_plane);

    GenerateBlocks();
    AligneBlocks();
//    for(int i = 0; i < 7; ++i)
//    {
//        m_blocks.push_back(new Block(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,10,1), QVector3D(-50,-10,1), ctPlane::Textured, 7,Block::BC_BLUE));
//        m_blocks.last()->SetTexture(QString(":/texture/blue_")+QString::number(i+1)+QString(".png"),true);
//        m_blocks.last()->Init();
//        m_blocks.last()->GetTransform()->SetParent(rootTransform->GetTransform());
//        m_blocks.last()->GetTransform()->MoveBy(QVector3D(10*i,10*i,0));
//        m_blocks.last()->GetTransform()->Scale(QVector3D(0.17f, 0.17f, 1));
//        AddObject(m_blocks[i]);
//    }

    AddObject(rootTransform);

    AddComponnent(m_timer);
    //AddObject(m_timer);
    //AddObject(m_plane2);
}

void testScene::TimerTest()
{
    qDebug()<<"TimerTested";
}

void testScene::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext)
{
    ctScene::SetDefault(t_shaderManager, t_scene, t_OpenGLContext);

    GetShaderManager()->AddFragmentShader(fragmentShaderSource, "fragmentShaderSource");
    GetShaderManager()->AddVertexShader(vertexModelShaderSource, "vertexModelShaderSource");
    GetShaderManager()->AddFragmentShader(texturedFragmentShaderSource, "texturedFragmentShaderSource");
    GetShaderManager()->AddVertexShader(texturedVertexShaderSource, "texturedVertexShaderSource");
    GetShaderManager()->AddVertexShader(texturedModelVertexShaderSource, "texturedModelVertexShaderSource");
    GetShaderManager()->AddFragmentShader(lineFragmentShaderSource, "lineFragmentShaderSource");
    GetShaderManager()->AddVertexShader(lineVertexShaderSource, "lineVertexShaderSource");
    GetShaderManager()->SetUpShaderProgram("vertexModelShaderSource", "fragmentShaderSource", "coloredShader");
    GetShaderManager()->SetUpShaderProgram("lineVertexShaderSource", "lineFragmentShaderSource", "lineShader");
    GetShaderManager()->SetUpShaderProgram("texturedModelVertexShaderSource", "texturedFragmentShaderSource", "texturedPlaneShader");
}

void testScene::BeginDraw()
{
    ctScene::BeginDraw();
    //-----------------TEMPORARY-SOLUTION-------------------------
    glViewport(0, 0, GetWindow()->GetWidth(), GetWindow()->GetHeight());
    //------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ++frameCounter;
    if(msecsCounter<1000)msecsCounter += ctTime::GetTime()->GetDeltaTime();
    else {m_lastFPS=frameCounter; msecsCounter = 0;frameCounter=0;}

    //DrawText(QPointF(30,30), QString::number(m_lastFPS));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void testScene::Draw()
{
    ctScene::Draw();

    QMatrix4x4 matrix;
    matrix.ortho((0 - GetWindow()->GetDefaultWidth() /2), (GetWindow()->GetDefaultWidth() /2), (GetWindow()->GetDefaultHeight()/2), (0 - GetWindow()->GetDefaultHeight()/2), 0, 10000.0f);//((0 - GetWindow()->width()/2), (GetWindow()->width()/2), (GetWindow()->height()/2), (0 - GetWindow()->height()/2), 0, 10000.0f);
    //matrix.perspective(60, 4.0/3.0, 0.1, 1000.0);
    matrix.translate(0, 0 , -50);
    //matrix.rotate(m_frame/*100.0f * m_frame / screen()->refreshRate()*/, 0, 1, 0);
    //qDebug()<<m_frame;
    //m_plane->GetTransform()->RotateByY(0.01f);//.GetMatrix().rotate(m_frame, 0, 1, 0);
    //ShowMatrix(m_plane->GetTransform()->GetLocalTransformMatrix().GetMatrix());
//    m_plane->SetProjectionMatrix(matrix);
//    m_plane2->SetProjectionMatrix(matrix);
//    m_back->SetProjectionMatrix(matrix);
//    m_block->SetProjectionMatrix(matrix);
//    for(int i = 0; i < 8; ++i)
//    {
//        m_blocks[i]->SetProjectionMatrix(matrix);
//    }
    QVector<ctObject*>::Iterator itr;
    for( itr = m_objects->begin(); itr != m_objects->end(); ++itr)
    {
        (*itr)->SetProjectionMatrix(matrix);
    }
    //ctWindow::RenderScene();
}

void testScene::EndDraw()
{
    ctScene::EndDraw();
    m_frame+=1.0f;
    if(m_frame > 360) m_frame = m_frame - 360;
    ctTime::GetTime()->Update();

    GetWindow()->DrawText(QPointF(30,30), QString::number(m_lastFPS));
    GetWindow()->DrawText(QPointF(30, 60), m_isClicked);
	
	GetWindow()->DrawText(QPointF(30, 90), QString("X: ") + QString::number(Input.GetMousePos2D().x()));
	GetWindow()->DrawText(QPointF(30, 120), QString("Y: ") + QString::number(Input.GetMousePos2D().y()));
	
    //glViewport(0, 0, GetWindow()->width(), GetWindow()->height());
}
void testScene::Update()
{
    ctScene::Update();
//    if(Input.IsMouseLeftButtonPush())
//    {
//        if(dynamic_cast<ctClickablePlane*>(m_plane)->IsIntersect(Input.GetMousePos3D()))
//        {
//            dragMode = true;
//        }
//    }
//    if(Input.IsMouseLeftButtonRelease())
//    {
//        dragMode = false;
//    }
//    if(dragMode)
//    {
//        //m_plane->GetTransform()->MoveBy(QVector3D(0.5f,0.5f, 0));
//        m_plane->GetTransform()->Move(Input.GetMousePos3D());
//    }
    //ManageRectClick(m_blocks);
    ManageCollide();
}

Block* testScene::ManageRectClick(QVector<Block *> &t_blocks)
{
    return 0;
//    if(!dragMode)// return 0;
//    {
//        if(Input.IsMouseLeftButtonPush())
//        {
//            for(int i = 0; i < t_blocks.size(); ++i)
//            {
//                if(dynamic_cast<ctClickablePlane*>(t_blocks[i])->IsIntersect(Input.GetMousePos3D()))
//                {
//                    m_selected = t_blocks[i];
//                    dragMode = true;
//                    return m_selected;
//                }
//            }
//            return 0;
//        }
//        return 0;
//    }
//    else
//    {
//        if(Input.IsMouseLeftButtonRelease())
//        {
//            dragMode = false;
//            m_selected = 0;
//        }
//        if(dragMode && m_selected)
//        {
//            m_selected->GetTransform()->Move(Input.GetMousePos3D());
//        }
//    }
}

void testScene::GenerateBlocks()
{
    QVector<Block*> m_tmp;
    for(int i = 0; i < 8; ++i)
    {
        m_blockSlots.push_back(new QVector<Block*>());
        for(int j = 0; j < 7; ++j)
        {
           // m_blockSlots.last()->push_back();
            m_tmp.push_back(new Block(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,10,1), QVector3D(-50,-10,1), ctPlane::Textured, 7-j, i));
            m_tmp.last()->SetTexture(QString(":/texture/")+Block::GetColor(i)+QString("_")+QString::number(7-j)+QString(".png"),true);
            m_tmp.last()->Init();
            //m_blockSlots.last()->last()->GetTransform()->SetParent(rootTransform->GetTransform());
            m_tmp.last()->GetTransform()->MoveBy(QVector3D(20*i,10*j,0));

            //if(i==2 && j==2){qDebug()<<m_blockSlots.last()->last()->GetTransform()->GetLocalTransformMatrix().GetMatrix().column(3);}
            m_tmp.last()->GetTransform()->Scale(QVector3D(0.17f, 0.17f, 1));
            AddObject(m_tmp.last());
            AddCollider(m_tmp.last());
        }
    }

    for(int i = 0; i < m_tmp.size(); ++i)
    {
        int rnd = ctRand::intRandom(0, 7);
        qDebug()<< i << " "<< rnd;
        m_blockSlots[rnd]->push_back(m_tmp[i]);
    }
}

ctClickablePlane* testScene::ManageCollide()
{
    if(!dragMode)// return 0;
    {
        if(Input.IsMouseLeftButtonPush())
        {
            for(int i = 0; i < m_coliderObjects.size(); ++i)
            {
                if(dynamic_cast<ctClickablePlane*>(m_coliderObjects[i])->IsIntersect(Input.GetMousePos3D()))
                {
                    m_selected = m_coliderObjects[i];
                    dragMode = true;
                    return m_selected;
                }
            }
            return 0;
        }
        return 0;
    }
    else
    {
        if(Input.IsMouseLeftButtonRelease())
        {
            dragMode = false;
            m_selected = 0;
            AligneBlocks();
        }
        if(dragMode && m_selected)
        {
            m_selected->GetTransform()->Move(Input.GetMousePos3D());
        }
    }
}

void testScene::AddCollider(ctClickablePlane * t_clickPlane)
{
    m_coliderObjects.push_back(t_clickPlane);
}

void testScene::AligneBlocks()
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j=0; j<m_blockSlots[i]->size(); ++j)
        {
            m_blockSlots[i]->at(j)->GetTransform()->Move(QVector3D((64 + (128*i))-512,
                                                                   300 - (25*j), 1));
        }
    }
}
