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
#include "ctButton.h"
#include "ctMover.h"
#include "hanoj/hCircles.h"
#define Input GetWindow()->GetInput()->GetInputHelper()

testScene::testScene() : m_verticalAligneBlock(33.0f), m_horisontalAligneBlock(128.0f)
{
}

testScene::testScene(ctShaderManager * t_shaderManager) : ctScene(t_shaderManager), m_verticalAligneBlock(33.0f), m_horisontalAligneBlock(128.0f)
{}

testScene::testScene(ctShaderManager * t_shaderManager, QGLContext * t_OpenGLContext) : ctScene(t_shaderManager, t_OpenGLContext), m_verticalAligneBlock(33.0f), m_horisontalAligneBlock(128.0f)
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
    //m_selected = 0;
    m_isClicked = "not";

    qDebug()<<"init testScene";
    //GetWindow()->GetOpenGLContext()->makeCurrent();
    SetDefault(GetShaderManager(), 0, GetWindow()->GetOpenGLContext());//GetOpenGLContext());
    //m_plane2 = new ctPlane(GetShaderManager(), 0, GetOpenGLContext(), QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);
    //m_plane = new ctClickablePlane(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,50,0), QVector3D(-50,-50,0), ctPlane::Textured);
    m_back = new ctPlane(GetShaderManager(), this,GetOpenGLContext(), QVector3D(512,384,-10), QVector3D(-512, -384, -10), ctPlane::Colored);
    m_timer = new ctTimer();
    m_back->SetColor(QVector3D(0.61f, 1.0f, 0.85f));
    ctButton* m_resetButton = new ctButton(GetShaderManager(), this,GetOpenGLContext(), QVector3D(512,384,1), QVector3D(-512, -384, 0.5), ctPlane::Textured, GetWindow()->GetInput());
    //m_resetButton->SetColor(QVector3D(0.0f, 1.0f, 0));
    //m_block = new Block(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,10,1), QVector3D(-50,-10,1), ctPlane::Textured, 7,Block::BC_BLUE);
   // ctMover * t_mover = new ctMover();
    //m_resetButton->AddComponnent(t_mover);
   // t_mover->SetUp(QVector3D(400,400, 1), QVector3D(-400, -400, 1),10000, true, m_resetButton->GetTransform());
    //t_mover->Start();
    m_timer->SetTimer(5000, true);
    m_timer->GetDelegat()->AppendConnect(this, &testScene::TimerTest);
    hCircles * t_circles = new hCircles(GetShaderManager(), this, GetOpenGLContext());
    t_circles->Init();
    //m_plane2->InitShader("texturedPlaneShader");
    //m_plane->InitShader("texturedPlaneShader");
    //m_plane2->SetTexture("D:\\OpenGLEperemental\\OpenGLTest\\txture.png");//(":/texture/txture.png");//("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    //m_plane->SetTexture(":/texture/txture.png");//("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    //m_back->SetTexture(":/texture/back.jpg");
    m_resetButton->SetTexture(":/texture/reset.png",true);
    m_resetButton->GetOnPush()->AppendConnect(this, &testScene::ResetBlocks);
    //m_block->SetTexture(":/texture/blue_7.png");

    //m_block->Init();
    //m_plane->Init();
    m_back->Init();
    m_resetButton->Init();



    //rootTransform = new ctObject();
    //rootTransform->GetTransform()->Move(QVector3D(0,0,0));
    //double scale = 1;//GetWindow()->GetDevicePixelRatioCoff();
    //m_plane->GetTransform()->Scale(QVector3D(1,1,1));
    //m_plane->GetTransform()->SetParent(rootTransform->GetTransform());
   // m_back->GetTransform()->SetParent(rootTransform->GetTransform());
    //m_block->GetTransform()->SetParent(rootTransform->GetTransform());
    //rootTransform->GetTransform()->Scale(QVector3D(scale,scale,scale));
    //m_resetButton->GetTransform()->SetParent(rootTransform->GetTransform());
    m_resetButton->GetTransform()->Scale(QVector3D(0.3f, 0.3f, 1.0f));
    m_resetButton->GetTransform()->Move(QVector3D(-400,-320,0));
    //rootTransform->Hide();
    glClearColor(1.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, GetWindow()->width(), GetWindow()->height());
    if(! ctTime::GetTime())//Time)
    {qDebug()<<"Fuck\n";}
    m_frame = 0;


    AddObject(t_circles);
    //AddObject(m_back);
    AddObject(m_resetButton);
    //AddObject(m_block);
    //AddObject(m_plane);

    GenerateBlocks();
    AligneBlocks();

    //AddObject(rootTransform);

    AddComponnent(m_timer);
    //AddObject(m_timer);
    //AddObject(m_plane2);
}

void testScene::TimerTest()
{
    qDebug()<<"TimerTested";
}

void testScene::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QGLContext * t_OpenGLContext)
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

    m_prevColumn = -1;
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


    GetWindow()->DrawText(QPointF(30,30), QString::number(m_lastFPS));
    GetWindow()->DrawText(QPointF(30, 60), m_isClicked);
	
    GetWindow()->DrawText(QPointF(30, 90), QString("X: ") + QString::number(Input.GetMousePos3D().x()));
    GetWindow()->DrawText(QPointF(30, 120), QString("Y: ") + QString::number(Input.GetMousePos3D().y()));
	
    //glViewport(0, 0, GetWindow()->width(), GetWindow()->height());
}
void testScene::Update()
{
    ctScene::Update();

    ManageCollide();
    ctTime::GetTime()->Update();
}

void testScene::GenerateBlocks()
{
    for(int i = 0; i<8; ++i)m_blockSlots.push_back(new QVector<Block*>());
    for(int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {
           // m_blockSlots.last()->push_back();
            m_reservedContainer.push_back(new Block(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,10,-10), QVector3D(-50,-10,-10), ctPlane::Textured, j+1, i));
            m_reservedContainer.last()->SetTexture(QString(":/texture/")+Block::GetColor(i)+QString("_")+QString::number(j+1)+QString(".png"),true);
            m_reservedContainer.last()->Init();
            //m_blockSlots.last()->last()->GetTransform()->SetParent(rootTransform->GetTransform());
            m_reservedContainer.last()->GetTransform()->MoveBy(QVector3D(20*i,10*j,0));

            //if(i==2 && j==2){qDebug()<<m_blockSlots.last()->last()->GetTransform()->GetLocalTransformMatrix().GetMatrix().column(3);}
            m_reservedContainer.last()->GetTransform()->Scale(QVector3D(0.17f, 0.25f, 1));
            AddObject(m_reservedContainer.last());
            AddCollider(m_reservedContainer.last());
            //m_reservedContainer.last()->GetTransform()->SetParent(rootTransform->GetTransform());
        }
    }
    ReinitColumns(m_reservedContainer);
}

void testScene::ReinitColumns(QVector<Block *> t_blocks)
{
	QVector<Block*> tmp;
	for(int i = 0; i<t_blocks.size(); ++i)tmp.push_back(t_blocks[i]);
	//tmp = t_blocks;
    for(int i = 0; i<8; ++i)m_blockSlots[i]->clear();

    int tmpsize = m_reservedContainer.size();
    for(int i = 0; i < tmpsize; ++i)
    {
        int rnd = ctRand::intRandom(0, 7);
        int rnd2 = ctRand::intRandom(0,tmp.size()-1);
        qDebug()<< i << " "<< rnd;
        m_blockSlots[rnd]->push_back(tmp[rnd2]);
        //ON Qt 5.2
        tmp.removeAt(rnd2);
        //ON Qt 5.1
        //tmp.remove(rnd2);
    }
}

ctClickablePlane* testScene::ManageCollide()
{
    if(!dragMode)// return 0;
    {
        if(Input.IsMouseLeftButtonPush())
        {
			bool taked = false;
            for(int i = 0; i < m_coliderObjects.size(); ++i)
            {
                Block* selectedBlock = dynamic_cast<Block*>(m_coliderObjects[i]);
                if(selectedBlock->IsIntersect(Input.GetMousePos3D()))
                {
					taked = true;
                    //m_selected = m_coliderObjects[i];
                    dragMode = true;
                    QPoint point = FindBlock(selectedBlock);
                    TakeBlock(point.x(), 0);
                    return 0;//m_selected;
                }
            }
			if(!taked)
			{
				int colIndex = GetColByPos(Input.GetMousePos2D());
				if(m_blockSlots[colIndex]->size() > 0 && Input.GetMousePos2D().y() > -200)
				{
					dragMode = true;
					TakeBlock(colIndex, 0);
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
            //m_selected = 0;
            DropBlock(GetColByPos(Input.GetMousePos2D()));
            AligneBlocks();
        }
        if(dragMode)// && m_selected)
        {
            for(int i = 0; i < m_movingStash.size(); ++i)
            {
                m_movingStash[i]->GetTransform()->Move(QVector3D(Input.GetMousePos3D().x(),
                                                                 Input.GetMousePos3D().y() - (m_verticalAligneBlock * i),
                                                                 3.0f));
            }
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
            m_blockSlots[i]->at(j)->GetTransform()->Move(QVector3D((64 + (m_horisontalAligneBlock * i)) - 512,
                                                                   300 - (m_verticalAligneBlock * j), 1));
        }
    }

    if(IsWin())
        qDebug()<<"\nGameWin!!!\n\n";
}

QPoint testScene::FindBlock(Block *t_block)
{
    for(int i = 0; i < m_blockSlots.size(); ++i)
    {
        int tt = m_blockSlots[i]->lastIndexOf(t_block);
        if(tt>=0)
        {
            //qDebug()<<"col: "<<i<<"row: "<<tt;
            return QPoint(i, tt);
        }
    }

    qDebug()<<"didntFinde";
    return QPoint(-1, -1);
}

void testScene::TakeBlock(int t_col, int t_row)
{
    if(t_col < 0 || t_row < 0) return;

    m_prevColumn = t_col;
//-----------------------------------------------
   // Block* tmpBlock = m_blockSlots[t_col]->last();
	m_movingStash.push_front(m_blockSlots[t_col]->last());
    int counter = 1;
    for(int i = m_blockSlots[t_col]->size()-1; i >=0 ; i-- )
    {
        if(i < m_blockSlots[t_col]->size()-1)
        {
			//qDebug()<<"condition1: "<<(m_blockSlots[t_col]->at(i)->GetBlockSize())<<"condition2: "<<(m_blockSlots[t_col]->at(i+1)->GetBlockSize());
            if(m_blockSlots[t_col]->at(i)->GetBlockColor() == m_blockSlots[t_col]->at(i+1)->GetBlockColor() &&
                    m_blockSlots[t_col]->at(i)->GetBlockSize() == m_blockSlots[t_col]->at(i+1)->GetBlockSize()+1)
            {
                m_movingStash.push_front(m_blockSlots[t_col]->at(i));
                ++counter;
            }
            else
            {
                break;
            }
        }
    }
    //qDebug()<<"Blocks Count: "<<counter;
//-----------------------------------------------

//    Block* block = m_blockSlots[t_col]->at(t_row);
//    m_blockSlots[t_col]->removeAt(t_row);
//    m_movingStash.push_back(block);
      for(int i = 0; i < counter; ++i)
      {
          m_blockSlots[t_col]->removeLast();
      }
}

void testScene::DropBlock(int t_col)
{
    if(m_movingStash.size()<=0 || t_col < 0) return;

    if((m_blockSlots[t_col]->size() == 0))
	{
		for(int i = 0; i < m_movingStash.size(); ++i)
        {
            m_blockSlots[t_col]->push_back(m_movingStash[i]);
        }
        m_movingStash.clear();
	}
	else if(m_blockSlots[t_col]->last()->GetBlockColor() == m_movingStash.last()->GetBlockColor() &&
            m_blockSlots[t_col]->last()->GetBlockSize() > m_movingStash.first()->GetBlockSize())
    {
        for(int i = 0; i < m_movingStash.size(); ++i)
        {
            m_blockSlots[t_col]->push_back(m_movingStash[i]);
        }
        m_movingStash.clear();
    }
    else
    {
        for(int i = 0; i < m_movingStash.size(); ++i)
        {
            m_blockSlots[m_prevColumn]->push_back(m_movingStash[i]);
        }
        m_movingStash.clear();
    }
    //Block* block = m_movingStash.last();
    //m_movingStash.clear();
    //m_blockSlots[t_col]->push_back(block);
}

int testScene::GetColByPos(QVector2D t_pos)
{
    for(int i = 0; i < 8; ++i)
    {
        if(t_pos.x() >= (128 * i)-512 && t_pos.x() <= (128 * (i + 1))-512)
        {
            //qDebug()<<"col: "<<i;
            return i;
        }
    }
    return -1;
}

void testScene::ResetBlocks()
{
    qDebug()<<"Try Reset!!!";
    ReinitColumns(m_reservedContainer);
	AligneBlocks();
}

bool testScene::IsWin()
{
    for(int i = 0; i < m_blockSlots.size(); i++)
    {
        if(m_blockSlots.at(i)->size() == 0) continue;

        if(m_blockSlots.at(i)->size() != 7){ return false;}
        else
        {
            for(int j = 1; j < m_blockSlots.at(i)->size(); ++j)
            {
                if(m_blockSlots.at(i)->at(j-1)->GetBlockColor() != m_blockSlots.at(i)->at(j)->GetBlockColor() ||
                        m_blockSlots.at(i)->at(j-1)->GetBlockColor() > m_blockSlots.at(i)->at(j)->GetBlockColor())
                    return false;
            }
        }
    }
    return true;
}

