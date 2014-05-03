#include "hBricks.h"
#include "ctScene.h"
#include "ctMatrix4.h"
#include "ctWindow.h"
#include "ctInput.h"
#include "ctRand.h"
#include "../hanoj/hBlock.h"

#define Input GetScene()->GetWindow()->GetInput()->GetInputHelper()
hBricks::hBricks() : ctObject(), m_verticalAligneBlock(33.0f), m_horisontalAligneBlock(128.0f)
{}
hBricks::hBricks(ctShaderManager * t_shaders) : ctObject(t_shaders), m_verticalAligneBlock(33.0f), m_horisontalAligneBlock(128.0f)
{}
hBricks::hBricks(ctShaderManager * t_shader, ctScene * t_scene, ctInput * t_input) : ctObject(t_shader, t_scene), m_verticalAligneBlock(33.0f), m_horisontalAligneBlock(128.0f)
{
    //SetInput(t_input);
}
hBricks::hBricks(ctShaderManager * t_shader, ctScene * t_scene, QGLContext * t_OpenGLContext, ctInput * t_input) : ctObject(t_shader, t_scene, t_OpenGLContext), m_verticalAligneBlock(33.0f), m_horisontalAligneBlock(128.0f)
{
    //SetInput(t_input);
}

hBricks::~hBricks()
{}

void hBricks::Update()
{
    ctObject::Update();
    ManageCollide();
    for(int i = 0; i < m_blocks.count(); ++i)
    {
        m_blocks.at(i)->Update();
    }
}
void hBricks::Draw()
{
    glDisable(GL_DEPTH_TEST);
    ctObject::Draw();
    for(int i = 0; i < m_blocks.count(); i++)
    {
        //m_blocks.at(i)->SetProjectionMatrix(GetProjectionMatrix());
        m_blocks.at(i)->Draw();
    }
    glEnable(GL_DEPTH_TEST);
}
void hBricks::Init()
{
    ctObject::Init();
    GenerateBlocks();
    AligneBlocks(true);
}

void hBricks::SetInput(ctInput* t_input)
{
    m_input = t_input;
}

void hBricks::AligneBlocks(bool t_fast)
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j=0; j<m_blockSlots[i]->size(); ++j)
        {
            if(t_fast)
            {
                m_blockSlots[i]->at(j)->GetTransform()->Move(QVector3D((64 + (m_horisontalAligneBlock * i)) - 512,
                                                                   300 - (m_verticalAligneBlock * j), 1));
            }
            else
            {
                m_blockSlots[i]->at(j)->AutoMove(m_blockSlots[i]->at(j)->GetTransform()->GetLocalPos(), QVector3D((64 + (m_horisontalAligneBlock * i)) - 512,
                                                                                                              300 - (m_verticalAligneBlock * j), 1));
            }
        }
    }

    if(IsWin())
        qDebug()<<"\nGameWin!!!\n\n";
}

void hBricks::ManageCollide()
{
    if(!m_scene->IsDragMode())// return 0;
    {
        if(Input.IsMouseLeftButtonPush())
        {
            bool taked = false;
            for(int i = 0; i < m_blocks.size(); ++i)
            {
                Block* selectedBlock = (m_blocks.at(i));
                if(selectedBlock->IsIntersect(Input.GetMousePos3D()))
                {
                    taked = true;
                    //m_selected = m_coliderObjects[i];
                    //dragMode = true;
                    m_scene->SetDragMode(true);
                    QPoint point = FindBlock(selectedBlock);
                    TakeBlock(point.x(), 0);
                    return;//m_selected;
                }
            }
            if(!taked)
            {
                int colIndex = GetColByPos(Input.GetMousePos2D());
                if(m_blockSlots[colIndex]->size() > 0 && Input.GetMousePos2D().y() > -200)
                {
                    m_scene->SetDragMode(true);
                    //dragMode = true;
                    TakeBlock(colIndex, 0);
                }
            }
            return;// 0;
        }
        return;// 0;
    }
    else
    {
        if(Input.IsMouseLeftButtonRelease())
        {
            m_scene->SetDragMode(false);
            //dragMode = false;
            //m_selected = 0;
            DropBlock(GetColByPos(Input.GetMousePos2D()));
            AligneBlocks();
        }
        if(m_scene->IsDragMode())//(dragMode)// && m_selected)
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

void hBricks::ResetBlocks()
{
    qDebug()<<"Try Reset!!!";
    ReinitColumns();//(m_blocks);
    AligneBlocks();
}

void hBricks::GenerateBlocks()
{
    for(int i = 0; i<8; ++i)m_blockSlots.push_back(new QVector<Block*>());
    for(int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {
           // m_blockSlots.last()->push_back();
            m_blocks.push_back(new Block(GetShaderManager(), GetScene(), GetOpenGLContext(), QVector3D(50,10,-10), QVector3D(-50,-10,-10), ctPlane::Textured, j+1, i));
            m_blocks.last()->SetTexture(QString(":/texture/")+Block::GetColor(i)+QString("_")+QString::number(j+1)+QString(".png"),true);
            m_blocks.last()->Init();
            //m_reservedContainer.last()->
            //m_blockSlots.last()->last()->GetTransform()->SetParent(rootTransform->GetTransform());
            m_blocks.last()->GetTransform()->MoveBy(QVector3D(20*i,10*j,0));

            //if(i==2 && j==2){qDebug()<<m_blockSlots.last()->last()->GetTransform()->GetLocalTransformMatrix().GetMatrix().column(3);}
            m_blocks.last()->GetTransform()->Scale(QVector3D(0.17f, 0.25f, 1));
            //AddObject(m_reservedContainer.last());
            //AddCollider(m_reservedContainer.last());
            //m_reservedContainer.last()->GetTransform()->SetParent(rootTransform->GetTransform());
        }
    }
    ReinitColumns();
}

void hBricks::ReinitColumns()//(QVector<Block *> t_blocks)
{
    QVector<Block*> tmp;
    for(int i = 0; i<m_blocks.size(); ++i)tmp.push_back(m_blocks[i]);
    //tmp = t_blocks;
    for(int i = 0; i<8; ++i)m_blockSlots[i]->clear();

    int tmpsize = m_blocks.size();
    for(int i = 0; i < tmpsize; ++i)
    {
        int rnd = ctRand::intRandom(0, 7);
        int rnd2 = ctRand::intRandom(0,tmp.size()-1);
        qDebug()<< i << " "<< rnd;
        m_blockSlots[rnd]->push_back(tmp[rnd2]);
        //ON Qt 5.2
        //tmp.removeAt(rnd2);
        //ON Qt 5.1
        tmp.remove(rnd2);
    }
}

bool hBricks::IsWin()
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

int hBricks::GetColByPos(QVector2D t_pos)
{
    for(int i = 0; i < 8; ++i)
    {
        if(t_pos.x() >= (128 * i)-512 && t_pos.x() <= (128 * (i + 1))-512)
        {
            return i;
        }
    }
    return -1;
}

void hBricks::DropBlock(int t_col)
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
}

void hBricks::TakeBlock(int t_col, int t_row)
{
    if(t_col < 0 || t_row < 0) return;

    m_prevColumn = t_col;
//-----------------------------------------------
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
//-----------------------------------------------
      for(int i = 0; i < counter; ++i)
      {
          m_blockSlots[t_col]->removeLast();
      }
}

QPoint hBricks::FindBlock(Block *t_block)
{
    for(int i = 0; i < m_blockSlots.size(); ++i)
    {
        int tt = m_blockSlots[i]->lastIndexOf(t_block);
        if(tt>=0)
        {
            return QPoint(i, tt);
        }
    }
    return QPoint(-1, -1);
}

void hBricks::SetProjectionMatrixtt(ctMatrix4 &t_projMat)
{
    //ctObject::SetProjectionMatrix(t_projMat);
    for(int i = 0; i < m_blocks.count(); ++i)
    {
        m_blocks[i]->SetProjectionMatrix(t_projMat);
    }
}

void hBricks::SetProjectionMatrixtt(QMatrix4x4 & t_projMat)
{
    //ctObject::SetProjectionMatrix(t_projMat);
    for(int i = 0; i < m_blocks.count(); ++i)
    {
        m_blocks[i]->SetProjectionMatrix(t_projMat);
    }
}

int hBricks::MoreThen(Block *t_block1, Block *t_block2)
{
    if(t_block1->GetTransform()->GetGlobalPos().z() < t_block2->GetTransform()->GetGlobalPos().z()) return -1;
    else if(t_block1->GetTransform()->GetGlobalPos().z() == t_block2->GetTransform()->GetGlobalPos().z()) return 0;
    else if(t_block1->GetTransform()->GetGlobalPos().z() > t_block2->GetTransform()->GetGlobalPos().z()) return 1;
}

void Swap(Block* t_block1, Block* t_block2)
{
    Block* tmp = t_block2;
    t_block2 = t_block1;
    t_block1 = tmp;
}
